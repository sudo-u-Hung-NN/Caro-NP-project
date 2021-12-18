#include "logger.h"

void INFORLOG(char *infor) {
    printf("INFOR: %s\n", infor);
}

void WARNING(char *infor) {
    printf("WARNING: %s\n", infor);
}

int ASSERT(char* input, char* groundtruth) {
    if (strcmp(input, groundtruth) == 0) {
        printf("ASSERT SUCCESS: input<%s> vs groundtruth<%s>\n", input, groundtruth);
        return 1;
    } else {
        printf("ASSERT FAILED: input<%s> vs groundtruth<%s>\n", input, groundtruth);
        return 0;
    }
}