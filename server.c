#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdbool.h>
#include "client.c"

#define PORT 4455

int calculator(const int arr_of_numbers[], char *type_of_operation);

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
    recv(newSocket, type_of_operation, 20, 0); // Тип операции

    // Обработка данных клиента
    int res = calculator(resv_buffer_int, type_of_operation);
    // Отправка результата клиенту
    send(newSocket, &res, 40, 0);

    // Завершение сеанса
    int tr = true;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &tr, sizeof(int));

    return 0;
}

int calculator(const int arr_of_numbers[], char *type_of_operation) {
    int k = 0;
    int sum = 0;
    int mult = 1;
    if (strcmp(type_of_operation, "add") == 0) {
        while (arr_of_numbers[k]) {
            sum += arr_of_numbers[k];
            k++;
        }
        return sum;
    } else {
        while (arr_of_numbers[k]) {
            mult *= arr_of_numbers[k];
            k++;
        }
        return mult;
    }
}
