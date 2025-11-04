/***********
* Program Name: pmod.c
* Author: Gabriel Limberg
* Section : 121
* Date: 29 Oct 2025
* Version: 1.0
* To Compile: gcc -o pmod pmod.c
* Copyright (c) 2025
*
***********/
#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE // need to include to remove implicit declaration warning
#define _DEFAULT_SOURCE
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sched.h>
#define DEC 10
#define sleep_time 837272638

int main(int argc, char* argv[])
{
    struct timespec ts;
    ts = (struct timespec){ .tv_sec = 0, .tv_nsec = sleep_time };

    errno = 0;
    int before = getpriority(PRIO_PROCESS, 0);
    if (before == -1 && errno != 0) {
        printf("error with getting priority\n");
        return 1;
    }

    int priority = nice(DEC); // decrease priority by 10
    if (priority == -1 && errno != 0) {
        printf("error changing priority\n");
        return 1;
    }

    printf("Priority (nice) before: %d\n", before);
    printf("Priority (nice) after : %d\n", priority);

    printf("New Priority: %d\n", priority);
    nanosleep(&ts, NULL); // sleep for a long time
    printf("Goodbye!\n");
    return 0;
}