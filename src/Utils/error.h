#ifndef __ERROR_H__
#define __ERROR_H__

typedef enum {
  ERROR_COMMAND_NOT_FOUND,
  ERROR_INVALID_STATUS_COMMAND,
  ERROR_USER_DATABASE_NOTFOUND
} ErrorCode;

void error(ErrorCode err);

#endif