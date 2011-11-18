#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "libtcp-portmon.h"

#define START 1
#define END 35555 

static int run = 1;
static tcp_port_monitor_collection_t *p_coll = NULL;

static void signal_handler (int signum) {
    run = 0;
}

static void examine() {
    int i;
    char port[50];
    char ip[50];
    tcp_port_monitor_t *mon;

    mon = find_tcp_port_monitor(p_coll, START, END);
    if (NULL == mon) {
        return;
    }
    for (i = 0; i < 10; ++i) {
        peek_tcp_port_monitor(mon, REMOTEPORT, i, port, 50);
        peek_tcp_port_monitor(mon, REMOTEIP, i, ip, 50);
        printf("Port: %s %s\n", port, ip);
    }
    printf("\n");
}

int
main(int argc, char **argv) {
    tcp_port_monitor_t *mon;
    tcp_port_monitor_args_t args;

    signal(SIGINT, signal_handler);

    args.max_port_monitor_connections = 100;

    p_coll = create_tcp_port_monitor_collection();
    if (NULL == p_coll) {
        fprintf(stderr, "Unable to create monitor\n");
    }

    mon = create_tcp_port_monitor(START, END, &args);
    insert_tcp_port_monitor_into_collection(p_coll, mon);

    while (1) {
        if (run == 0) {
            break;
        }
        sleep(1);
        update_tcp_port_monitor_collection(p_coll);
        examine();
    }
    destroy_tcp_port_monitor_collection(p_coll);
    return 0;
}
