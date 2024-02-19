#include "my_chat.h"

/*
Программа удаляет posix очереди сообщений.
Нужна, если сервер завершился с ошибкой и
не удалил очереди самостоятельно.
*/
int main() {
    mq_unlink(STOC);
    mq_unlink(CTOS);
    mq_unlink(USERS_MQ);
    return 0;
}