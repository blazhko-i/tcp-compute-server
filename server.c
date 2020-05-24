#include <netinet/in.h>
#include <sys/socket.h>
//#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORT 4455

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in new_Addr;

    socklen_t addr_size;
    char type_of_operation[24];
    int resv_buffer_int[20];

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    listen(sockfd, 5);
    addr_size = sizeof(new_Addr);

    newSocket = accept(sockfd, (struct sockaddr *) &new_Addr, &addr_size);

    // Прием данных клиента
    recv(newSocket, resv_buffer_int, 40, 0); // Прием массива чисел
    int k = 0;
    while (resv_buffer_int[k]) {
        printf("%s%d\n", "arr: ", resv_buffer_int[k]);
        k++;
    }
    recv(newSocket, type_of_operation, 20, 0); // Тип операции
    printf("%s\n", type_of_operation);

    // Завершение сеанса
    int true = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));

    return 0;
}
