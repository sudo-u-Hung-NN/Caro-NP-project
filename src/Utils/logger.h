#ifndef LOGGER_H
#define LOGGER_H

#include "stdio.h"
#include <stdarg.h>

void INFORLOG(char *infor) {
    printf("INFOR: %s\n", infor);
}

void WARNING(char *infor) {
    printf("WARNING: %s\n", infor);
}


#endif