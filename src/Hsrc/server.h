#ifndef SERVER_H
#define SERVER_H

#include "string.h"
#include "ctype.h"
#include "stdlib.h"

char *uppercase(char* input) {
    char* output = (char*) malloc(strlen(input) * sizeof(char));
    for (int i = 0; i < strlen(input); i++) {
        output[i] = toupper(input[i]);
    }
    return output;
}


#endif