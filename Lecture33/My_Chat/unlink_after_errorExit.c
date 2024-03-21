#include "my_chat.h"

/*
Программа удаляет posix очереди сообщений.
Нужна, если сервер завершился с ошибкой и
не удалил очереди самостоятельно.
*/
int main() {
    mq_unlink(SERVTOCLI);
    mq_unlink(CLITOSERV);
    mq_unlink(SERVTOUSERTHREAD);
    mq_unlink(SERVTOMSGTHREAD);
    return 0;
}