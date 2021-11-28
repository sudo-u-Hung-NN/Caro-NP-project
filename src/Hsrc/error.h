#ifndef __ERROR_H__
#define __ERROR_H__

typedef enum {
  ERROR_COMMAND_NOT_FOUND,
  ERROR_INVALID_STATUS_COMMAND
} ErrorCode;

void error(ErrorCode err);

#endif