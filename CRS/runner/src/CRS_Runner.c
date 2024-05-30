//
// Created by anton on 24.05.24.
//


#include <stdio.h>
#include <string.h>
#include "CRS_Domain.h"
#include "CRS_Runner.h"
#include "util.h"
#include "python_runner.h"
#include "cpp_runner.h"

static int validate_test(char *expected, char *actual) {
    return strcmp(expected, actual);
}

void prepare_directory_before_test(const char *temp_dir_path, const char *input) {
    delete_input_file(temp_dir_path);
    delete_output_file(temp_dir_path);
    create_empty_output_file(temp_dir_path);
    write_to_input_file(temp_dir_path, input);
}


enum CRS_run_status CRS_run_code(struct CRS_attempt attempt) {
    printf("running code...\n");
    const enum CRS_lang lang = attempt.lang;

    const char *temp_dir_path = create_temp_directory();

    switch (lang) {
        case CPP:
            write_cpp_src_to_file(temp_dir_path, attempt.code);
            compile_cpp_code(temp_dir_path);
            break;
        case PYTHON:
            write_python_src_to_file(temp_dir_path, attempt.code);
            break;
        case UNKNOWN:
            break;
    }

    for (int i = 0; i < attempt.tests_count; i++) {
        struct CRS_test test = attempt.tests[i];

        prepare_directory_before_test(temp_dir_path, test.input);

        int run_status = 1;

        switch (lang) {
            case CPP:
                run_status = run_cpp_code(temp_dir_path, attempt.timeout_s);
                break;
            case PYTHON:
                run_status = run_python_code(temp_dir_path, attempt.timeout_s);
                break;
            case UNKNOWN:
                break;
        }

        if (run_status != 0) {
            return FAIL;
        }

        char *actual = read_from_output_file(temp_dir_path);

        int result = validate_test(test.expected, actual);

        if (result != 0) {
            return FAIL;
        }
    }
    return PASS;
}






