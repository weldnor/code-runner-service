//
// Created by anton on 30.05.24.
//

#include <stdlib.h>
#include "CRS_Common.h"
#include "util.h"


static char *get_timeout_as_string(int timeout_s);

static char *get_python_src_path(const char *temp_dir_path) {
    return concat(temp_dir_path, "/main.py");
}

static char *make_run_command_for_python(const char *temp_dir_path, const int timeout_s) {
    char *timeout_s_as_string = get_timeout_as_string(timeout_s);

    char *code_file_path = concat(temp_dir_path, "/main.py");

    char *command;
    command = concat("cd  ", temp_dir_path);
    command = concat(command, " ; timeout ");
    command = concat(command, timeout_s_as_string);
    command = concat(command, " python3 ");
    command = concat(command, code_file_path);
    return command;
}

static char *get_timeout_as_string(int timeout_s) {
    char result[10];
    return itoa(timeout_s, result, 10);
}

 int run_python_code(const char *temp_dir_path, const int timeout_s) {
    char *command = make_run_command_for_python(temp_dir_path, timeout_s);
    return system(command);
}

void write_python_src_to_file(const char *temp_dir_path, const char *code) {
    write_to_file(get_python_src_path(temp_dir_path), code);
}

