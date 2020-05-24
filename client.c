#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 4455

int *split();
void typeOfOperation(char *str);

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    printf("Created \n");
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(PORT);
    serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Connected \n");

    // Подготовка информации для отправки
    int *arr = split();

    char type_of_operation[24];
    typeOfOperation(type_of_operation);

    // Отправка данных на сервер
    send(clientSocket, arr, 40, 0);
    send(clientSocket, type_of_operation, 20, 0);

    // Завершение сеанса
    int true = 1;
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));

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
    printf("Enter the numbers to calculate: ");
    fgets(str, sizeof(str), stdin);

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

/** Выбор типа операции
 * @return add or mult
 */
void typeOfOperation(char *str) {
    while (1) {
        puts("Enter type of operation: ");
        scanf("%s", str);
        if (strcmp(str, "add") == 0 || (strcmp(str, "mult")) == 0) {
            break;
        }
    }
}
