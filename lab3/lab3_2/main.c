#include <stdio.h>
#include <stdlib.h>
#include "func.c"
#include <readline/readline.h>
#include <time.h>

char* calc(char* s) {
  if (strchr(s, '.') != NULL && strrchr(s, ';') != NULL) {
      char* p = strchr(s, '.');
      s = p;
      p = strrchr(s, ';') + 1;
      *p = '\0';
      return s;
  }
  return "Incorrect string";
}

int main() {
	char* str = NULL;
    do {
        str = get_str();
        if (str) {
            clock_t begin = clock();
            printf("modified string: %s\n", calc(str));
            free(str);
            clock_t end = clock();
            printf("total time: %lf\n", (double)(end-begin)/CLOCKS_PER_SEC);
        }
    } while (str);
	return 0;
}