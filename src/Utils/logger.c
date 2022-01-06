#include "logger.h"

#define DEBUG_MODE 1

void INFORLOG(char *infor) {
    printf("\033[1;34mINFOR:\033[0m %s\n", infor);
}

void DEBUG(char *infor) {
    if(DEBUG_MODE) {
        printf("\033[1;32mDEBUG:\033[0m %s\n", infor);
    }
}

void WARNING(char *infor) {
    printf("\033[1;35mWARNING:\033[0m %s\n", infor);
}

int ASSERT(char* input, char* groundtruth) {
    if (strcmp(input, groundtruth) == 0) {
        printf("\033[1;34mASSERT SUCCESS:\033[0m input<%s> vs groundtruth<%s>\n", input, groundtruth);
        return 1;
    } else {
        printf("\033[1;35mASSERT FAIL:\033[0m input<%s> vs groundtruth<%s>\n", input, groundtruth);
        return 0;
    }
}