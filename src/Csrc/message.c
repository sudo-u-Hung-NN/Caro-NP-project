#include "../Hsrc/message.h"
#include "../Hsrc/types.h"
#include "../Hsrc/data.h"

#include "stdlib.h"
#include "string.h"


msg_data *create_data(char *input) {
    msg_data *newdata = (msg_data*) malloc(sizeof(msg_data));

    bzero(&newdata->target, sizeof(newdata->target));
    bzero(&newdata->data, sizeof(newdata->data));

    int i = 0;
    for (; (i < TARGET_LEN) && (input[i] != ' '); i++) {
        newdata->target[i] = input[i];
    }

    for (int j = i + 1; (j < DATA_LEN) && (input[j] != '\0'); j++) {
        newdata->data[j - (i+1)] = input[j];
    }

    return newdata;
}
