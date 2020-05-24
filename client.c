#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define PORT 4455

int *split(char *str);
char *split_str(const char *str);
void typeOfOperation(char *str);
bool isDigit(char *str);

int main() {
    int clientSocket;
    int calculation_result;
    struct sockaddr_in serverAddr;

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    printf("Created \n");
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    printf("Connected \n");

    // Подготовка информации для отправки
    // Проверка, содержит ли строка только числа
    bool t = true;
    char str_s[50];
    // Проверка на ввод пустой строки
    do {
        printf("Enter the numbers or text: ");
        fgets(str_s, 30, stdin);
    } while (str_s[0] == '\n' && str_s[1] == '\0');

    t = isDigit(str_s);
    // Если только числа, то ...
    if (t == true) {
        int *arr = split(str_s);
        char type_of_operation[24];
        typeOfOperation(type_of_operation);

        // Отправка данных на сервер
        send(clientSocket, arr, 40, 0);
        send(clientSocket, type_of_operation, 20, 0);

        // Прием данных от сервера
        recv(clientSocket, &calculation_result, sizeof(calculation_result), 0);
        printf("%s%d%s", "Result of calculating: ", calculation_result, "\n");
    } else {
        char *new_str = split_str(str_s);
        printf("%s\n", new_str);
    }

    // Завершение сеанса
    int tr = true;
    setsockopt(clientSocket, SOL_SOCKET, SO_REUSEADDR, &tr, sizeof(int));

    return 0;
}

/**
 * Разбиение строки на элементы по пррблелу. Запись элементов в массив
 * @return Указатель на массив
 */
int *split(char *str) {
    // Набор символов, которые должны входить в искомый сегмент
    char sep[10] = " ";
    // Переменная, в которую будут заноситься начальные адреса частей
    char *istr;
    int *arr_of_numbers;
    arr_of_numbers = malloc(sizeof(int));

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
/** Конкатенация слов в строке
 * @return str
 */
char *split_str(const char *str) {
    char *new_str = malloc(sizeof(char ));
    unsigned long len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != ' ') {
            new_str[j] = str[i];
            j++;
        }
    }
    return new_str;
}

/** Выбор типа операции
 * @return add or mult
 */
void typeOfOperation(char *str) {
    while (1) {
        printf("%s", "Enter type of operation: ");
        scanf("%s", str);
        if (strcmp(str, "add") == 0 || (strcmp(str, "mult")) == 0) {
            break;
        }
    }
}
/**
 * @return bool. If true, therefore str consist only of numbers, else str -> string
 */
bool isDigit(char *str) {
    int k = 0;
    const char *c = "-";
    bool t = true;

    while (str[k]) {
        if (!(isdigit(str[k]) || isspace(str[k]) || strcspn(&str[k], c) == 0)) {
            t = false;
        }
        k++;
    }
    return t;
}
