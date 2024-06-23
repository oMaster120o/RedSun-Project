#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char* GET_USER_PATH(void);

static char user_path_addr;
static char *user_path = &user_path_addr;

static char* GET_USER_PATH(void) {
  user_path = (char*)calloc( ( strlen("/home//") + strlen(getenv("USER")) ), sizeof(char));
  strcpy(user_path, "/home/");
  strcat(user_path, getenv("USER"));
  strcat(user_path, "/");
  return user_path;
}




static char final_string;
static char *ptr_final_string = &final_string;

static char copy_target_string;
static char *ptr_copy_target_string;

//this is a custom function to inject strings in other strings: strInsert("This %s a string", "is"); should return "This is a string".
static char* strInsert(char* __target_string, char* string) {

  ptr_final_string = (char*)calloc( ( strlen(__target_string) + strlen(string) + 50), sizeof(char));
  ptr_copy_target_string = (char*)calloc( ( strlen(__target_string) ), sizeof(char));

  strcpy(ptr_final_string, __target_string);
  strcpy(ptr_copy_target_string, __target_string);
 

  const size_t len_string = strlen(string);
  size_t format_index = -1;

  for (size_t indx = 0; indx < ( strlen(ptr_final_string) ); indx++) {
    if (ptr_final_string[indx] == '%' && ptr_final_string[( indx+1 )] == 's') 
    {
       format_index = indx;
       break;
    }
  };


  if (format_index == -1)
  {
    return NULL;
  }

  for (size_t indx = 0; indx < ( strlen(__target_string) ); indx++) {


      if (indx == format_index) {
          for (size_t num = 0; num <= ( len_string ); num++) {
              ptr_final_string[( format_index + num )] = string[num];
          };
      }

      if (indx > format_index) {
          ptr_final_string[( indx + (len_string-1) )] = ptr_copy_target_string[( indx+1 )];
      }

  };

  return ptr_final_string;
}
