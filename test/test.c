#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct Sub {
    char* full_name; // name, 
    char phone[16];
    int time;
} Sub;


int main() {
    Sub s = {"Ser Lut And", "+79168322328", 2374282};
    char buf[255] = "Lutsenko S.A +79782754242 23424\0";
    char* full_name;
    char phone[16]; int time;

    char* plus = strchr(buf, '+');
    strncpy(full_name, buf, (plus-buf));
    //strncpy(buf,) скопировать после + до первого пробела
    char* space = strrchr(plus, ' ');
    //strncpy(phone, plus, (space-plus));
    printf("%s\n%s\n", full_name, phone);








    /*
    FILE *fp;
    fp = fopen("data.txt", "a+b");
    char buf[255];
    while (fgets(buf, 255, fp) != NULL) {
        
        printf("%s", buf);
    }


    fclose(fp);

    */

    /*
        // printing
        fp = fopen("data.txt", "a+b");
        fprintf(fp, "Some text here...\n");
        fclose(fp);
    */
    /* 
    // reading 
        fp = fopen("data.txt", "a+b");
        char buff[255];
        // scanf stops reading after encountering the first space character.
        fscanf(fp, "%s", buff);
        printf("%s", buff);
        fclose(fp);
    */
    
    return 0;
}