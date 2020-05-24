#include <netinet/in.h>
#include <sys/socket.h>
//#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORT 4455

int *split();

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in new_Addr;

    socklen_t addr_size;
    char buffer[1024];
    char send_buffer[1024];

    sockfd = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, '\0', sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    listen(sockfd, 5);
    addr_size = sizeof(new_Addr);

    newSocket = accept(sockfd, (struct sockaddr *) &new_Addr, &addr_size);

    // Получение данных от клиента
//    recv(newSocket, buffer, 1024, 0);
//    printf("Received: %s\n", buffer);

    // Отправка данных клиенту
//    strcpy(send_buffer, buffer);
//    send(newSocket, send_buffer, strlen(buffer), 0);

    // Массив значений подлежащих обработке
    int *arr = split();
    send(newSocket, arr, 20, 0);

    // Ip адрес
//    char str[100];
//    inet_ntop(AF_INET, &(new_Addr.sin_addr), str, INET_ADDRSTRLEN);
//    printf("%s\n", str);

//    int k = 0;
//    while (arr[k]) {
//        printf("%d\n", arr[k]);
//        k++;
//    }

    // Завершение сеанса
    int true = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));

    return 0;
}

/**
 * Разбиение строки на элементы по пррблелу. Запись элементов в массив
 * @return Указатель на массив
 */
int *split() {
    // Набор символов, которые должны входить в искомый сегмент
    char sep[10] = " ";
    // Переменная, в которую будут заноситься начальные адреса частей
    char *istr;
    int *arr_of_numbers;
    arr_of_numbers = malloc(sizeof(int));

    char str[24];
    fgets(str, sizeof(str), stdin);

    printf("Исходная строка: %s\n", str);
    printf("Результат разбиения:\n");
    // Выделение первой части строки
    istr = strtok(str, sep);

    // Выделение последующих частей
    int count = 0;
    while (istr != NULL) {
        // str->int
        arr_of_numbers[count] = atoi(istr);
        arr_of_numbers = realloc(arr_of_numbers, (count + 2) * sizeof(int));

        // Выделение очередной части строки
        istr = strtok(NULL, sep);
        count++;
    }

    int *p = arr_of_numbers;
    return p;
}