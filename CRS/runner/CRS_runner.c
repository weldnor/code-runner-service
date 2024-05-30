//
// Created by anton on 24.05.24.
//


#include <string.h>
#include <CRS/runner/CRS_runner_util.h>
#include <CRS/domain/CRS_domain.h>
#include <CRS/runner/CRS_runner_cpp.h>
#include <CRS/runner/CRS_runner_python.h>
#include <CRS/common/CRS_common.h>
#include <CRS/runner/CRS_runner.h>

static int validate_test(char *expected, char *actual) {
    return strcmp(expected, actual);
}

void prepare_directory_before_test(const char *temp_dir_path, const char *input) {
    delete_input_file(temp_dir_path);
    delete_output_file(temp_dir_path);
    create_empty_output_file(temp_dir_path);
    write_to_input_file(temp_dir_path, input);
}


void prepare_test_environment(struct CRS_attempt *attempt, const enum CRS_lang *lang, const char *temp_dir_path) {
    switch ((*lang)) {
        case CPP:
            write_cpp_src_to_file(temp_dir_path, (*attempt).code);
            compile_cpp_code(temp_dir_path);
            break;
        case PYTHON:
            write_python_src_to_file(temp_dir_path, (*attempt).code);
            break;
        case UNKNOWN:
            break;
    }
}

int run_code(struct CRS_attempt *attempt, const enum CRS_lang *lang, const char *temp_dir_path) {
    switch ((*lang)) {
        case CPP:
            return run_cpp_code(temp_dir_path, (*attempt).timeout_s);
        case PYTHON:
            return run_python_code(temp_dir_path, (*attempt).timeout_s);
        case UNKNOWN:
            return 1;
    }
}

enum CRS_run_status CRS_run_code(struct CRS_attempt attempt) {
    CRS_log_info("start running code...");

    const CRS_lang lang = attempt.lang;

    const char *temp_dir_path = create_temp_directory();

    prepare_test_environment(&attempt, &lang, temp_dir_path);

    for (int i = 0; i < attempt.tests_count; i++) {
        CRS_log_info("running test");


        struct CRS_test test = attempt.tests[i];

        prepare_directory_before_test(temp_dir_path, test.input);

        int run_status = run_code(&attempt, &lang, temp_dir_path);

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





