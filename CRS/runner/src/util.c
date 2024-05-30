//
// Created by anton on 30.05.24.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <CRS_Common.h>

static char *get_input_file_path(const char *temp_dir_path) {
    return concat(temp_dir_path, "/input.txt");
}

static char *get_output_file_path(const char *temp_dir_path) {
    return concat(temp_dir_path, "/output.txt");
}

char *create_temp_directory() {
    char temp_dir_name[] = "/tmp/temp_XXXXXX";
    if (mkdtemp(temp_dir_name) == NULL) {
        perror("can't create temp dir");
        exit(1);
    }

    char *dir_path = malloc(strlen(temp_dir_name) + 1);
    if (dir_path == NULL) {
        perror("Ошибка выделения памяти");
        return NULL;
    }

    strcpy(dir_path, temp_dir_name);

    return dir_path;
}

void write_to_file(const char *filepath, const char *code) {
    FILE *fptr;
    fptr = fopen(filepath, "w");
    fprintf(fptr, "%s", code);
    fclose(fptr);
}

char *read_from_file(const char *filepath) {
    FILE *file;
    char *buffer = malloc(sizeof(char) * 10000);

    //Open file for reading
    file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Error: Failed to open file '%s'.\n", filepath);
        return NULL;
    }

    if (fgets(buffer, 10000, file) == NULL) {
        perror("can`t read from file");
        exit(1);
    }
    return buffer;
}

void delete_file(const char *filepath) {
    remove(filepath);
}

void delete_input_file(const char *temp_dir_path) {
    delete_file(get_input_file_path(temp_dir_path));
}

void delete_output_file(const char *temp_dir_path) {
    delete_file(get_output_file_path(temp_dir_path));
}

static void create_empty_file(const char *path) {
    FILE *file;

    file = fopen(path, "w");

    if (file == NULL) {
        perror("Failed to create empty file");
        return;
    }

    fclose(file);
}

void create_empty_output_file(const char *temp_dir_path) {
    create_empty_file(concat(temp_dir_path, "/input.txt"));
}


void write_to_input_file(const char *temp_dir_path, const char *code) {
    write_to_file(get_input_file_path(temp_dir_path), code);
}

char *read_from_output_file(const char *temp_dir_path) {
    return read_from_file(get_output_file_path(temp_dir_path));
}