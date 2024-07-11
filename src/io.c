#include <stdlib.h>
#include <stdio.h>
#include "include/io.h"

char* get_file_contents(const char* path){
    char* buffer = 0;
    long len;

    FILE* f = fopen(path, "rb");

    if (f){
        fseek(f, 0, SEEK_END);
        len = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = calloc(len, len);

        if (buffer){
            fread(buffer, 1, len, f);
        }

        fclose(f);
        return buffer;
    }

    printf("Failed to read file %s\n", path);
    exit(2);
}
