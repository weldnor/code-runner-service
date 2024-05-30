//
// Created by anton on 30.05.24.
//

#include <stdlib.h>
#include "CRS_common.h"
#include "CRS_runner_util.h"

static char *get_timeout_as_string(int timeout_s);

static char *get_cpp_src_path(const char *temp_dir_path) {
    return concat(temp_dir_path, "/main.cpp");
}


static char *make_run_command_for_cpp(const char *temp_dir_path, const int timeout_s) {
    char *timeout_s_as_string = get_timeout_as_string(timeout_s);

    char *command;
    command = concat("cd  ", temp_dir_path);
    command = concat(command, " ; timeout ");
    command = concat(command, timeout_s_as_string);
    command = concat(command, " ./a.out ");
    return command;
}

int run_cpp_code(const char *temp_dir_path, const int timeout_s) {
    char *command = make_run_command_for_cpp(temp_dir_path, timeout_s);
    return system(command);
}


static char *make_compile_command_for_cpp(const char *temp_dir_path) {
    char *command;
    command = concat("cd  ", temp_dir_path);
    command = concat(command, " ; c++ ");
    command = concat(command, "./main.cpp");
    return command;
}

int compile_cpp_code(const char *temp_dir_path) {
    char *command = make_compile_command_for_cpp(temp_dir_path);
    return system(command);
}

char *get_timeout_as_string(int timeout_s) {
    char *timeout_as_string = calloc(10, sizeof(char));
    itoa(timeout_s, timeout_as_string, 10);
    return timeout_as_string;
}


void write_cpp_src_to_file(const char *temp_dir_path, const char *code) {
    write_to_file(get_cpp_src_path(temp_dir_path), code);
}