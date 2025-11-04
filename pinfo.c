/***********
* Program Name: pinfo.c
* Author: Gabriel Limberg
* Date: 29 Oct 2025
* Version: 1.0
* To Compile: gcc -o pinfo pinfo.c
* Copyright (c) 2025
*
***********/
#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE // need to include to remove implicit declaration warning
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sched.h>


int main(int argc, char *argv[]) {
    pid_t pid;
    char scheduler_str[99];

    if (argc == 2) {
        pid = atoi(argv[1]); // pid from user 
    } else {
        pid = getpid();  // no argument defaults here
    }

    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) { // if errno is 0, then priority is -1
        printf("error getting priority");
        return 1;
    }

    int scheduler = sched_getscheduler(pid);
    if (scheduler == -1) {
        printf("error getting scheduler"); // fails is scheduler == -1 
        return 1;
    }

    switch (scheduler) { // 
        case SCHED_FIFO: // 1
            strcpy(scheduler_str, "FIFO"); 
            break;
        case SCHED_OTHER: // 0
            strcpy(scheduler_str, "OTHER");
            break;
        case SCHED_BATCH: // 3
            strcpy(scheduler_str, "BATCH");
            break;
        case SCHED_IDLE: // 5
            strcpy(scheduler_str, "IDLE");
            break;
        case SCHED_RR: // 2
            strcpy(scheduler_str, "RR");
            break;
        default:
            strcpy(scheduler_str, "UNKNOWN");
            break;
    }


    printf("Process ID: %d\n", pid);
    printf("Priority: %d\n", priority);
    printf("Scheduling Policy: %s\n", scheduler_str);

    return 0;
}