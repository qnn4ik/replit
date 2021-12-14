#include <string.h>
int lens(char* s) {
    int c = 0;
    while(*(s+c) != '\0') {
        c++;
    }
    return c;
}

char* chr(char* str, char ch) {
    char *p = 0;
    for (int i = 0; i < lens(str); i++) {
        if (str[i] == ch) {
            p = str + i;
            break;
        }
    }
    return p;
}

char* rchr(char* str, char ch) {
    char* p = 0;
    for (int i = 0; i < lens(str); i++) {
        if (str[i] == ch) p = str + i;
    }
    return p;
}

char* get_str() {
    char buf[81] = {0};
    char* res = NULL;
    int len = 0, n = 0;
    do {
        n = sacnf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = lens(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
}