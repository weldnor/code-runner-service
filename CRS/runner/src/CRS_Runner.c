//
// Created by anton on 24.05.24.
//


#include <stdio.h>
#include <stdlib.h>
#include "CRS_Domain.h"
#include "CRS_Common.h"

static char *create_temp_directory() {
    char template[] = "/tmp/tmpdir.XXXXXX";
    char *dir_name = mkdtemp(template);

    if (dir_name == NULL) {
        perror("mkdtemp failed: ");
        return NULL;
    }
    return dir_name;
}


static void write_code_to_file(char *filepath, char *code) {
    FILE *fptr;
    fptr = fopen(filepath, "w");
    fprintf(fptr, "%s", code);
    fclose(fptr);
}

static void run_code(char *filepath) {
    char *command = concat("python3 ", filepath);
    system(command);
}


void CRS_run_code(struct CRS_attempt attempt) {
    printf("running code...\n");

    char *temp_dir_path = create_temp_directory();

    if (temp_dir_path == NULL) {
        //todo
    }


    char *filepath = concat(temp_dir_path, "/main.py");
    write_code_to_file(filepath, attempt.code);

    run_code(filepath);
}


