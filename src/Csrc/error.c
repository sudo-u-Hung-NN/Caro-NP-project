
#include <stdio.h>
#include <stdlib.h>
#include "../Hsrc/error.h"

#define NUM_OF_ERRORS 2

struct ErrorMessage {
  ErrorCode errorCode;
  char *message;
} errors[NUM_OF_ERRORS] = {
  {ERROR_COMMAND_NOT_FOUND, "Command not found!"},
  {ERROR_INVALID_STATUS_COMMAND, "Command can't execute in this status"}
};

void error(ErrorCode err) {
  int i;
  for (i = 0 ; i < NUM_OF_ERRORS; i ++) 
    if (errors[i].errorCode == err) {
      printf("%s\n", errors[i].message);
      break;
    }
}