#ifndef LOGGER_H
#define LOGGER_H

#include "stdio.h"
#include "string.h"

void INFORLOG(char *infor);

void WARNING(char *infor);

int ASSERT(char* input, char* groundtruth);

#endif