//
// Created by anton on 30.05.24.
//

#ifndef CRS_CRS_RUNNER_CPP_H
#define CRS_CRS_RUNNER_CPP_H

void write_cpp_src_to_file(const char *temp_dir_path, const char *code);

int compile_cpp_code(const char *temp_dir_path);

int run_cpp_code(const char *temp_dir_path, int timeout_s);

#endif //CRS_CRS_RUNNER_CPP_H
