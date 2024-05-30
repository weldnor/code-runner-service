//
// Created by anton on 24.05.24.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CRS_Domain.h"
#include "CRS_Common.h"
#include "CRS_Runner.h"

static char *create_temp_directory() {
    char temp_dir_name[] = "/tmp/temp_XXXXXX";
    mkdtemp(temp_dir_name);

    char *dir_path = malloc(strlen(temp_dir_name) + 1); // +1 для нулевого символа конца строки
    if (dir_path == NULL) {
        perror("Ошибка выделения памяти");
        return NULL;
    }

    strcpy(dir_path, temp_dir_name);

    return dir_path;
}


static void write_to_file(char *filepath, char *code) {
    FILE *fptr;
    fptr = fopen(filepath, "w");
    fprintf(fptr, "%s", code);
    fclose(fptr);
}

static char *read_from_file(char *filepath) {
    FILE *file;
    char *buffer = malloc(sizeof(char) * 10000); // initialize buffer to NULL

    //Open file for reading
    file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Error: Failed to open file '%s'.\n", filepath);
        return NULL;
    }

    fgets(buffer, 10000, file);
    return buffer;
}

static void delete_file(char *filepath) {
    remove(filepath);
}

static void write_code_to_file(const char *temp_dir_path, char *code) {
    char *path = concat(temp_dir_path, "/main.py");
    write_to_file(path, code);
}

static int validate_test(char *expected, char *actual) {
    return strcmp(expected, actual);
}


static int run_code(char *temp_dir_path, int timeout_s) {
    char timeout_s_as_string[10];
    itoa(timeout_s, timeout_s_as_string, 10);

    char *code_file_path = concat(temp_dir_path, "/main.py");

    // create command
    char *command;
    command = concat("cd  ", temp_dir_path);
    command = concat(command, " ; timeout ");
    command = concat(command, timeout_s_as_string);
    command = concat(command, " python3 ");
    command = concat(command, code_file_path);

    return system(command);
}


enum CRS_run_status CRS_run_code(struct CRS_attempt attempt) {
    printf("running code...\n");
    const char *temp_dir_path = create_temp_directory();

    write_to_file(concat(temp_dir_path, "/main.py"), attempt.code);

    for (int i = 0; i < attempt.tests_count; i++) {
        struct CRS_test test = attempt.tests[i];

        delete_file(concat(temp_dir_path, "/input.txt"));
        delete_file(concat(temp_dir_path, "/output.txt"));

        write_to_file(concat(temp_dir_path, "/input.txt"), test.input);
        int run_status = run_code(temp_dir_path, attempt.timeout_s);

        if (run_status != 0) {
            return FAIL;
        }

        char *actual = read_from_file(concat(temp_dir_path, "/output.txt"));

        int result = validate_test(test.expected, actual);

        if (result != 0) {
            return FAIL;
        }
    }
    return PASS;
}


