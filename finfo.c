/***********
* Program Name: finfo.c
* Author: Gabriel Limberg
* Date: 29 Oct 2025
* gcc -o finfo finfo.c
* Version: 1.0
* Copyright (c) 2025
*
***********/
#define _POSIX_C_SOURCE 199309L
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    if (argc != 2) { // if no argument present
        printf("finfo takes no arguments\n");
        return 1;
    }
    char *file = argv[1];
    struct stat fileStat;

    if (stat(file, &fileStat) < 0) { // if stat fails (returns -1)
        printf("Error getting file information\n");
        return 1; 
    }

    printf("File: %s\n", file);
    printf("Type: ");
    switch (fileStat.st_mode & S_IFMT) { // mask to get file type
        case S_IFBLK:
            printf("Block device\n");
            break;
        case S_IFCHR:
            printf("Character device\n");
            break;
        case S_IFIFO:
            printf("FIFO special\n");
            break;
        case S_IFREG:
            printf("Regular file\n");
            break;
        case S_IFDIR:
            printf("Directory\n");
            break;
        case S_IFLNK:
            printf("Symbolic link\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }
    mode_t mode = fileStat.st_mode;
    printf("Permissions on file: ");
    switch (mode & (S_IRUSR | S_IWUSR | S_IXUSR)) { // using | to check combinations 
        case S_IRUSR | S_IWUSR | S_IXUSR:
            printf("read, write, execute\n");
            break;
        case S_IRUSR | S_IWUSR:
            printf("read, write\n");
            break;
        case S_IRUSR | S_IXUSR:
            printf("read, execute\n");
            break;
        case S_IWUSR | S_IXUSR:
            printf("write, execute\n");
            break;
        case S_IRUSR:
            printf("read only\n");
            break;
        case S_IWUSR:
            printf("write only\n");
            break;
        case S_IXUSR:
            printf("execute only\n");
            break;
        default:
            printf("none\n");
            break;
    }

    printf("Owner of the file: %d\n", fileStat.st_uid); // owner user ID
    printf("Size of file: %ld bytes\n", (long)fileStat.st_size); // size in bytes
    printf("Last modified: %s", ctime(&fileStat.st_mtime)); // return in human format

    return 0;
}