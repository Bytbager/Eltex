#include "../my_chat.h"

struct User me;

int main() {
    mqd_t read_mqds, write_mqds;
    memset(&me, 0, sizeof(struct User));
    char mqname[17] = "/\0";
    int prio = 0;
    char buff[256];

    pthread_t msg_hist_thread, msg_create_thread, user_thread;
    pthread_attr_t attr;
    int msg_history_pipe[2], user_list_pipe[2]; 

    read_mqds = mq_open(SERVTOCLI, O_RDONLY);       /*Открываем очередь для чтения*/
    if (read_mqds == -1)
        errExit("read open error!\n");
    write_mqds = mq_open(CLITOSERV, O_WRONLY);      /*Открываем очередь для записи*/
    if (write_mqds == -1)
        errExit("write open error!\n");

    /*Инициализируем ncurses и выводим стартовый экран для ввода никнейма*/
    initscr();
    signal(SIGWINCH, sig_winch);
    start_color();
    cbreak();
    curs_set(FALSE);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    attron(COLOR_PAIR(1));
    bkgd(COLOR_PAIR(1));
    refresh();
    start_screen(&me);

    /*Создаём поток для ввода сообщений*/
    if (pthread_create(&msg_create_thread, &attr, (void *) message_create_thread, &write_mqds) != 0)
        errExit("pthread_create message_create_thread error!\n");

    /*Создаём поток, который будет отображать историю сообщений
    Также создаём канал для передачи данных между главным потоком
    и новым потоком*/
    if (pipe(msg_history_pipe) == -1)
        errExit("msg_history_pipe error!\n");
    if (pthread_create(&msg_hist_thread, &attr, (void *) message_history_thread, &msg_history_pipe[0]) != 0)
        errExit("pthread_create message_history_thread error!\n");

    /*Создаём поток, который будет отображать список пользователей
    Также создаём канал для передачи данных между главным потоком
    и новым потоком*/
    if (pipe(user_list_pipe) == -1)
        errExit("user_list_pipe error!\n");
    if (pthread_create(&user_thread, &attr, (void *) user_list_thread, &user_list_pipe[0]) != 0)
        errExit("pthread_create user_thread error!\n");

    /*Отправляем серверу сообщение о том, что появился новый пользователь*/
    if (mq_send(write_mqds, (char *) &me, 256, NEW_USER) != 0) {
        errExit("mq_send error!\n");
    }

    /*Ожидаем подтверждение от сервера
    Когда оно приходит, мы можем открыть
    новую, созданную сервером для этого 
    клиента очередь*/
    mq_receive(read_mqds, buff, 256, &prio);
    if (prio == NEW_USER) {
        strncat(mqname, me.nickname, 16);
        me.mqds = mq_open(mqname, O_RDONLY);
        if (me.mqds == -1)
            errExit("me mq_open o_rdonly error!\n");
        prio = 0;
    }

    /*Входим в бесконечный цикл для получения сообщений из новой очереди*/
    while (1) {
        memset(buff, 0, 256);
        if (mq_receive(me.mqds, buff, 256, &prio) == -1)
            errExit("receive me.mqds error!\n");

        /*Сообщения с приоритетом NEW_USER говорят о том, что появился новый пользователь
        Их мы отправляем поток, который отображает список пользователей*/
        if (prio == NEW_USER) {
            if (write(user_list_pipe[1], (struct User *) buff, sizeof(struct User)) == -1)
                errExit("write user_list_pipe error!\n");
        }
        
        /*Сообщения с приоритетом DELETED_USER сообщают о том, что какой-то пользователь
        завершил программу. Мы в параметр дескриптора пользователя указываем этот приоритет
        и также отправляем сообщение потоку, отвечающему за список пользователей*/
        else if (prio == DELETED_USER) {
            ((struct User *)buff)->mqds = DELETED_USER;
            if (write(user_list_pipe[1], (struct User *) buff, sizeof(struct User)) == -1)
                errExit("write user_list_pipe error!\n");
        }
        
        /*Сообщения с приоритетом MESSAGE являются обычными сообщениями, их отправляем
        потоку, отвечающему за историю сообщений*/
        else if (prio == MESSAGE) {
            if (write(msg_history_pipe[1], buff, strlen(buff)) == -1)
                errExit("write msg_history_pipe error!\n");
        }
        
        /*Сообщение с приоритетом SERVER_RECEIVED_DELETION_REQUEST поступают только в том
        случае, если мы сами хотим выйти из программы. Данное сообщение говорит нам о том,
        что сервер получил от нас уведомление о выходе. В данной ситуации мы присоединяем
        поток, отвечающий за создание сообщений, потом уведомляем оставшиеся 2 потока
        о завершении и присоединяем их, после этого выходим из цикла и завершаем программу*/
        else if (prio == SERVER_RECEIVED_DELETION_REQUEST) {
            if (pthread_join(msg_create_thread, NULL) != 0)
                errExit("pthread_join msg_create_thread error!\n");
            ((struct User *)buff)->mqds = SERVER_RECEIVED_DELETION_REQUEST;
            if (write(user_list_pipe[1], (struct User *) buff, sizeof(struct User)) == -1)
                errExit("write user_list_pipe error!\n");
            if (pthread_join(user_thread, NULL) != 0)
                errExit("pthread_join user_thread error!\n");
            if (write(msg_history_pipe[1], (struct User *) buff, sizeof(struct User)) == -1)
                errExit("write msg_hist_pipe error!\n");
            if (pthread_join(msg_hist_thread, NULL) != 0)
                errExit("pthread_join msg_history_thread error!\n");
            break;
        }
    }

    endwin();    
    return 0;
}