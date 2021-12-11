#ifndef DATA_H
#define DATA_H

#define TARGET_LEN 25
#define DATA_LEN 150

struct msg_data {
    char target[TARGET_LEN];
    char data[DATA_LEN];
};

typedef struct msg_data msg_data;

#endif