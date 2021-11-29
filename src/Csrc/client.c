#include "../Hsrc/client.h"


void apply_transaction(msg_type recv_command, msg_type send_command) {
    for (int i = 0; i < NUM_TRANSITION; i++) {
        if (transitions[i].prev_status == prev_status && 
            transitions[i].recv_command == recv_command &&
            transitions[i].send_command == send_command) {
            prev_status = transitions[i].next_status;
        }
    }
}