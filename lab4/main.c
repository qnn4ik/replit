#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort.c"
#include <locale.h>
#include <readline/readline.h>
#include <string.h>
#include <math.h>

typedef struct Sub {
    char* full_name; 
    char phone[16];
    int time;
} Sub;

Sub* read_data(Sub* sub, int* size) {
    setlocale(LC_ALL, "Rus");
    int com = 0;
    printf("Выберите опцию:\n0. Назад\n1. Чтение из стандартного потока\n2. Чтение из текстового файла\n3. Генерация случайных данных\n");
    printf("Ввод: ");
    scanf("%d", &com);
    while (com) {
        if (com == 1) {
            /* Чтение из стандратного потока ввода */
            sub[*(size)-1].full_name = readline("Введите полное имя: ");
            //printf("%s\n", sub[(*size)-1].full_name);
            printf("\nВведите номер телефона: ");
            scanf("%s", sub[(*size)-1].phone);
            //printf("%s\n", sub[(*size)-1].phone);
            printf("\nВведите время последнего звонка: ");
            scanf("%d", &sub[(*size)-1].time);
            //printf("%d\n", sub[(*size)-1].time);
            (*size)++;
            sub = (Sub*) realloc(sub, (*size) * sizeof(Sub));
        } else if (com == 2) {
            /* Чтение данных из текстового файла */
            char* full_name; char* time_s;
            char phone[16], file_name[255];
            int time_d = 0;
            printf("Читать из файла: ");
            scanf("%s", file_name);
            FILE* fp;
            fp = fopen(file_name, "a+b");
            char buf[255];

            while (fgets(buf, 255, fp) != NULL) {
                char* plus = strchr(buf, '+');
                full_name = (char*)malloc(((plus - buf) + 1) * sizeof(char));
                strncpy(full_name, buf, plus - buf);
                full_name[plus-buf-1] = '\0';
                char* space = strrchr(buf, ' ');
                strncpy(phone, plus, space - plus);
                phone[space - plus] = '\0';
                space++;
                time_s = space;
                time_s[strlen(time_s)-1] = '0';
                printf("We found out these data: %s, %s, %s;\n", full_name, phone, time_s);

                // validate time_s
                int check = 1;
                for (int i = 0; i < strlen(time_s); i++) {
                    char c = time_s[i];
                    int cif = c - '0';
                    if (cif > 10 || cif < 0) {
                        check = 0;
                        break;
                    }
                    time_d += cif * pow(10, strlen(time_s) - i);
                    //time_d ++;
                }

                if (!check) {
                    printf("%s\n", "Не успешно");
                    free(full_name);
                    continue;
                }

                printf("%s\n", "Успешно");
                sub[*(size)-1].full_name = malloc(strlen(full_name)*sizeof(full_name));
                strcpy(sub[*(size)-1].full_name, full_name);
                strcpy(sub[*(size)-1].phone, phone);
                sub[*(size)-1].time = time_d;
                (*size)++;
                sub = (Sub*) realloc(sub, (*size) * sizeof(Sub));
                free(full_name);

            }
            fclose(fp);
            //printf("Читаем из файла %s...\n", file_name);

        } else if (com == 3) {
            /* Генерация случайных данных */
            printf("doing 3...\n");
        } 

        if (!(com >= 1 && com <= 3)) {
            printf("Неверная команда, введите еще раз: ");
            scanf("%d", &com);
        } else {
            printf("Выберите опцию:\n0. Назад\n1. Чтение из стандартного потока\n2. Чтение из текстового файла\n3. Генерация случайных данных\n");
            printf("Ввод: ");
            scanf("%d", &com);
        }
    }
    if (com == 0) {
        printf("Выход...\n");
        return sub;
    }
}

void print_data(Sub* sub, int* size) {
    setlocale(LC_ALL, "Rus");
    int com = 0;
    printf("Выберите опцию:\n0. Назад\n1. Запись в стандартный поток вывода\n2. Запись в текстовый файл\n");
    printf("Ввод: ");
    scanf("%d", &com);
    while (com) {
        if (com == 1) {
            /* Запись в стандартный поток вывода */
            for (int i = 0; i < (*size)-1; i++) {
                printf("Пользователь №%d:\n", i+1);
                printf("Полное имя: %s\nНомер телефона: %s\nВремя последнего звонка: %d\n", sub[i].full_name, sub[i].phone, sub[i].time);
            }
            
        } else if (com == 2) {
            printf("doing 2...\n");
            /* Запись в текстовый файл */
        }

        if (!(com >= 1 && com <= 2)) {
            printf("Неверная команда, введите еще раз: ");
            scanf("%d", &com);
        } else {
            printf("Выберите опцию:\n0. Назад\n1. Запись в стандартный поток вывода\n2. Запись в текстовый файл\n");
            printf("Ввод: ");
            scanf("%d", &com);
        }
    }
    if (com == 0) {
        printf("Выход...\n");
        return;
    }

}

void calc_data() {
    setlocale(LC_ALL, "Rus");
}

void calc_time() {
    setlocale(LC_ALL, "Rus");
}

int main() {
    setlocale(LC_ALL, "Rus");
    int size = 1;
    Sub* sub = (Sub*) malloc(size*(sizeof(Sub)));
    int com = 0;

    printf("Выберите опцию:\n0. Завершить выполнение программы\n1. Ввод данных\n2. Вывод данных\n3. Обработка данных\n4. Таймирование\n");
    printf("Ввод: ");
    scanf("%d", &com);

    while (com) {
        if (com == 1) {
            printf("doing 1...\n");
            sub = read_data(sub, &size);
        } else if (com == 2) {
            printf("doing 2...\n");
            print_data(sub, &size);
        } else if (com == 3) {
            printf("doing 3...\n");
            calc_data();
        } else if (com == 4) {
            printf("doing 4...\n");
            calc_time();
        } 
        
        if (!(com >= 1 && com <= 4)) {
            printf("Неверная команда, введите еще раз: ");
            scanf("%d", &com);
        } else {
            printf("Выберите опцию:\n0. Завершить выполнение программы\n1. Ввод данных\n2. Вывод данных\n3. Обработка данных\n4. Таймирование\n");
            printf("Ввод: ");
            scanf("%d", &com);
        }
    }

    if (com == 0) {
        for (int i = 0; i < size-1; i++) {
            free(sub[i].full_name);
        }
        free(sub);
        printf("Выход...\n");
    }
    return 0;
}
