#include <stdio.h>
#include <time.h>
//#include <string.h>

typedef struct Sub {
    char* full_name; // name, 
    char phone[16];
    int time;
} Sub;

int main() {
    Sub s = {"Ser Lut And", "+79168322328", 2374282};

    printf("%s %s %d\n", s->full_name, s.phone, s.time);
    return 0;
}