#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 4455

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];
    char resv_buffer[1024];
    int resv_buffer_int[20];

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    printf("Created \n");
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Connected \n");

//    strcpy(buffer, "Hello");
//    send(clientSocket, buffer, strlen(buffer), 0);

    recv(clientSocket, resv_buffer_int, 20, 0);
    int k = 0;
    while (resv_buffer_int[k]) {
        printf("%s%d\n", "arr", resv_buffer_int[k]);
        k++;
    }

    // Завершение сеанса
    int true = 1;
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));

    return 0;
}
