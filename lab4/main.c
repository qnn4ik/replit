#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort.c"
#include <locale.h>
#include <readline/readline.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct Sub {
    char* full_name; 
    char phone[16];
    long long time;
} Sub;

void swapStructs(Sub* a, Sub* b) {
    // cpy a to tmp
    Sub tmp;
    tmp.full_name = malloc(strlen(a->full_name) * sizeof(a->full_name));
    strcpy(tmp.full_name, a->full_name);
    strcpy(tmp.phone, a->phone);
    tmp.time = a->time;

    // cpy b to a
    free(a->full_name);
    a->full_name = malloc(strlen(b->full_name) * sizeof(b->full_name));
    strcpy(a->full_name, b->full_name);
    strcpy(a->phone, b->phone);
    a->time = b->time;

    // cpy tmp to a
    free(b->full_name);
    b->full_name = malloc(strlen(tmp.full_name) * sizeof(tmp.full_name));
    strcpy(b->full_name, tmp.full_name);
    strcpy(b->phone, tmp.phone);
    b->time = tmp.time;

    free(tmp.full_name);
}


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
            printf("\nВведите номер телефона: ");
            scanf("%s", sub[(*size)-1].phone);
            printf("\nВведите время последнего звонка: ");
            scanf("%lld", &sub[(*size)-1].time);
            (*size)++;
            sub = (Sub*) realloc(sub, (*size) * sizeof(Sub));
        } else if (com == 2) {
            /* Чтение данных из текстового файла */
            char* full_name; char* time_s;
            char phone[16], file_name[255];
            long long time_d = 0;
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
                time_s[strlen(time_s)-1] = '\0';
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
                    time_d += cif * pow(10, (strlen(time_s) - i - 1));
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
                time_d = 0;

            }
            fclose(fp);
            //printf("Читаем из файла %s...\n", file_name);

        } else if (com == 3) {
            /* Генерация случайных данных */
            srand(time(NULL));
            int n;
            printf("Сколько сформировать пользователей: ");
            scanf("%d", &n);
            char full_name[255];
            char phone[16];
            long long time_d = 0;
            for (int i = 0; i < n; i++) {
                int full_name_size = 5 + rand() % (10-5+1);
                for (int i = 0; i < full_name_size; i++) {
                    full_name[i] = 99 + rand() % (122-99+1); 
                }
                full_name[full_name_size] = '\0';

                int phone_size = 13;
                phone[0] = '+';
                for (int i = 1; i < phone_size; i++) {
                    phone[i] = (rand() % 10) + '0';
                }
                phone[phone_size] = '\0';

                time_d = 1000 + rand() % 4000;
                sub[*(size) - 1].full_name = malloc(full_name_size*sizeof(full_name));
                strcpy(sub[*(size)-1].full_name, full_name);
                strcpy(sub[*(size)-1].phone, phone);
                sub[*(size)-1].time = time_d;

                printf("full name: %s\n", sub[*(size) - 1].full_name);
                printf("phone: %s\n", sub[*(size) - 1].phone);
                printf("time: %lld\n", sub[*(size) - 1].time);

                *(size)+=1;
                sub = (Sub*) realloc(sub, (*size) * sizeof(Sub));
                memset(full_name, 0, full_name_size);
                memset(phone, 0, phone_size);
                time_d = 0;
                printf("formed\n");
            }
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
                printf("Полное имя: %s\nНомер телефона: %s\nВремя последнего звонка: %lld\n", sub[i].full_name, sub[i].phone, sub[i].time);
                printf("\n");
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

Sub* calc_data(Sub* sub, int* size) {
    setlocale(LC_ALL, "Rus");
    int com = 0;
    printf("Выберите опцию:\n0. Назад\n1. Вставка нового элемента в массив по индексу\n2. Вставка нового элемента в упорядоченный массив без нарушения его упорядоченности\n3. Удаление заданного количества элементов, начиная с некоторого индекса\n4. Сортировка массива\n");
    printf("Ввод: ");
    scanf("%d", &com);
     while (com) {
        if (com == 1) {
            /* Вставка нового элемента в массив по индексу */
            printf("doing 1...\n");

            
        } else if (com == 2) {
            /* Вставка нового элемента в упорядоченный массив без нарушения его упорядоченности */
            printf("doing 2...\n");

        } else if (com == 3) {
            /* Удаление заданного количества элементов, начиная с некоторого индекса */
            int k = 0;
            printf("Удалить начиная с индекса: ");
            scanf("%d", &k);
            printf("\nСколько удалить: ");
            int n = 0;
            scanf("%d", &n);
            int count = 0;
            for (int i = k; i < *(size) && count < n; count++) {
                for (int j = i; j < *(size)-2; j++) {
                    swapStructs(&sub[j], &sub[j + 1]);
                }
                free(sub[*(size)-2].full_name);
                *(size) -= 1;
            }


        } else if (com == 4) {
            /* Сортировка массива */
            printf("doing 4...\n");
        }

        if (!(com >= 1 && com <= 4)) {
            printf("Неверная команда, введите еще раз: ");
            scanf("%d", &com);
        } else {
            printf("Выберите опцию:\n0. Назад\n1. Вставка нового элемента в массив по индексу\n2. Вставка нового элемента в упорядоченный массив без нарушения его упорядоченности\n3. Удаление заданного количества элементов, начиная с некоторого индекса\n4. Сортировка массива\n");
            printf("Ввод: ");
            scanf("%d", &com);
        }
    }
    if (com == 0) {
        printf("Выход...\n");
        return sub;
    }

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
            sub = read_data(sub, &size);
        } else if (com == 2) {
            print_data(sub, &size);
        } else if (com == 3) {
            printf("doing 3...\n");
            calc_data(sub, &size);
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
