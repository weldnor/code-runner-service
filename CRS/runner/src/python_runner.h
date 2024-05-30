//
// Created by anton on 30.05.24.
//

#ifndef CRS_PYTHON_RUNNER_H
#define CRS_PYTHON_RUNNER_H

void write_python_src_to_file(const char *temp_dir_path, const char *code);

int run_python_code(const char *temp_dir_path, const int timeout_s);

#endif //CRS_PYTHON_RUNNER_H
