#define _POSIX_C_SOURCE 200809L

#include <dirent.h>

#include <string.h>

#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <string.h>

#include <time.h>

#include <errno.h>


#include "pss.h"

Queue *fileQueue;
char *objExtension = ".o";


int compareFileNames(const void *a, const void *b) {
    const char *filenameA = *(const char **)a;
    const char *filenameB = *(const char **)b;
    return strcmp(filenameA, filenameB);
}

char *duplicateString(const char *str) {
    size_t len = strlen(str) + 1;
    char *copy = malloc(len * sizeof(char));
    if (copy != NULL) {
        memcpy(copy, str, len * sizeof(char));
    }
    return copy;
}

void freeFileQueue() {
    while (!emptyQueue(fileQueue)) {
        char *fileName = (char *)get(fileQueue);
        if (fileName != NULL) {
            free(fileName);
        }
    }
    destroyQueue(fileQueue);
}


void traverseDirectory(const char *path) {
    struct stat pathStat;
    struct stat objStat;
    int rc;

    rc = stat(path, &pathStat);

    if (rc != 0) {
        fprintf(stderr, "El directorio %s no existe\n", path);
        exit(0);
    }

    if (S_ISREG(pathStat.st_mode)) {
        if (strstr(path, ".c")) {
            char *objName = malloc(strlen(path) + strlen(objExtension) + 1);
            strcpy(objName, path);
            char *extPtr = strstr(objName, ".c");

            if (extPtr) {
                strcpy(extPtr, objExtension);
                if (stat(objName, &objStat) != 0 || pathStat.st_mtime > objStat.st_mtime) {
                    char *fileName = duplicateString(path);
                    if (!fileName) {
                        perror("Error al duplicar el nombre de archivo");
                        exit(1);
                    }
                    put(fileQueue, fileName);
                }
            }
            free(objName);
        }
    } else if (S_ISDIR(pathStat.st_mode)) {
        DIR *dir = opendir(path);
        if (!dir) {
            perror(path);
            exit(1);
        }
        struct dirent *entry;
        while ((entry = readdir(dir))) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            size_t newPathLength = strlen(path) + strlen(entry->d_name) + 2;
            char *newPath = malloc(newPathLength);
            if (!newPath) {
                perror("Error al asignar memoria para el nombre de archivo");
                exit(1);
            }
            snprintf(newPath, newPathLength, "%s/%s", path, entry->d_name);
            traverseDirectory(newPath);
            free(newPath);
        }
        closedir(dir);
    } else {
        fprintf(stderr, "El archivo %s tiene un tipo desconocido\n", path);
        exit(1);
    }
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo|directorio>\n", argv[0]);
        exit(1);
    }
    fileQueue = makeQueue();
    traverseDirectory(argv[1]);

    int numFiles = queueLength(fileQueue);

    char **fileNames = malloc(numFiles * sizeof(char *));
    for (int i = 0; i < numFiles; i++) {
        fileNames[i] = get(fileQueue);
    }

    qsort(fileNames, numFiles, sizeof(char *), compareFileNames);
    for (int i = 0; i < numFiles; i++) {
        printf("%s\n", fileNames[i]);
        free(fileNames[i]);
    }
    free(fileNames);
    freeFileQueue();

    return 0;
}
