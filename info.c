/***********
* Program Name: info.c
* Author: Gabriel Limberg
* Date: 29 Oct 2025
* Version: 1.0
* To compile: gcc -o info info.c
* Copyright (c) 2025
*
***********/
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#define HOST_NAME_MAX 64



int main(int argc, char* argv[])
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    long time = ts.tv_nsec;
    printf("Current time in nanoseconds: %ld\n", time);

    struct utsname ut;
    uname(&ut);
    char *net_name = ut.nodename;
    char *operating_system = ut.sysname;
    char *os_release = ut.release;
    char *os_version = ut.version;
    char *machine = ut.machine;
    char host_name[HOST_NAME_MAX + 1];
    //int temp = gethostname(host_name, sizeof(host_name));
    int page_size = 0;
    page_size = getpagesize(); // size of each page

    printf("System network name: %s\n", net_name);
    printf("OS: %s\n", operating_system);
    printf("Release: %s\nVersion: %s\n", os_release, os_version);
    printf("Machine: %s\n", machine);
    printf("Number of Processors: %d\n", get_nprocs());
    //printf("%s\n", host_name); // testing host name, not needed

    long am_pagesize = sysconf(_SC_PHYS_PAGES) * (long)page_size; // how much memory on the system 
    long av_pagesize = sysconf(_SC_AVPHYS_PAGES) * (long)page_size; // memory available
    printf("Memory on System: %ld\n", am_pagesize);
    printf("Available Memory: %ld\n", av_pagesize);




}