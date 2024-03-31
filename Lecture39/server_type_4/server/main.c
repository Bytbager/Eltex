#include "../server_type.h"

/*Программа создаёт 2 сокета: udp и tcp
Далее в бесконечном цикле вызывает select
для проверки готового на чтение сокета*/
int main() {
    int tcp_fd, tcp_cli_fd, udp_fd;
    struct sockaddr_in tcp_serv, udp_serv, udp_client;
    fd_set readfds;
    int retval, nfds;
    socklen_t client_len = sizeof(struct sockaddr_in);
    char message[32];
    memset(message, 0, 32);

    /*Создаём сокет tcp
    Заполняем структуру сервера
    Привязываем структуру к дескриптору
    Задаём размер очереди клиентов*/
    tcp_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_fd == -1)
        errExit("tcp socket error!\n");
    
    memset(&tcp_serv, 0, sizeof(struct sockaddr_in));
    tcp_serv.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &tcp_serv.sin_addr.s_addr);
    tcp_serv.sin_port = htons(TCP_PORT);

    if (bind(tcp_fd, (struct sockaddr *) &tcp_serv, sizeof(struct sockaddr_in)) == -1)
        errExit("bind tcp error!\n");

    if (listen(tcp_fd, 5) == -1)
        errExit("listen error!\n");

    /*Создаём сокет udp
    Заполняем структуру сервера
    Привязываем структуру к дескриптору*/
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_fd == -1)
        errExit("udp socket error!\n");

    memset(&udp_serv, 0, sizeof(struct sockaddr_in));
    udp_serv.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &udp_serv.sin_addr.s_addr);
    udp_serv.sin_port = htons(UDP_PORT);

    if (bind(udp_fd, (struct sockaddr *) &udp_serv, sizeof(struct sockaddr_in)) == -1)
        errExit("bind udp error!\n");

    /*Вычисляем значение nfds для функции select
    Оно должно быть на единицу больше, чем самое большое
    значение дескриптора, из списка дескрипторов в сете*/    
    tcp_fd > udp_fd ? (nfds = tcp_fd + 1) : (nfds = udp_fd + 1);
    
    /*Входим в бесконечный цикл
    Далее заполняем сет дескрипторов для select
    и после возврата этой функции, выполняем операции
    для сокета, который получил заявку от клиента*/
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(tcp_fd, &readfds);
        FD_SET(udp_fd, &readfds);


        retval = select(nfds, &readfds, NULL, NULL, NULL);
        if (retval == -1)
            errExit("select error!\n");
        
        if (FD_ISSET(tcp_fd, &readfds) != 0) {
            tcp_cli_fd = accept(tcp_fd, NULL, NULL);
            if (tcp_cli_fd == -1)
                errExit("accept error!\n");
            
            if (recv(tcp_cli_fd, message, 32, 0) == -1)
                errExit("recv tcp error!\n");
            
            printf("%s", message);
            
            memset(message, 0, 32);
            strncat(message, "Hello, TCP client!\n", strlen("Hello, TCP client!\n") + 1);
            
            if (send(tcp_cli_fd, message, 32, 0) == -1)
                errExit("send tcp error!\n");

            if (close(tcp_cli_fd) == -1)
                errExit("close tcp client error!\n");
        } else {
            if (recvfrom(udp_fd, message, 32, 0, (struct sockaddr *) &udp_client, &client_len) == -1)
                errExit("recvfrom error!\n");

            printf("%s", message);

            memset(message, 0, 32);
            strncat(message, "Hello, UDP client!\n", strlen("Hello, UDP client!\n") + 1);

            if (sendto(udp_fd, message, 32, 0, (struct sockaddr *) &udp_client, client_len) == -1)
                errExit("sendto error!\n");
        }
    }

    return 0;
}