//
// Created by anton on 30.05.24.
//

#ifndef CRS_UTIL_H
#define CRS_UTIL_H


char *create_temp_directory();

void create_input_file(const char *temp_dir_path);

void create_empty_output_file(const char *temp_dir_path);

char *read_from_file(const char *filepath);

char *read_from_output_file(const char *filepath);

void write_to_file(const char *filepath, const char *code);

void write_to_input_file(const char *temp_dir_path, const char *code);

void delete_file(const char *filepath);

void delete_input_file(const char *temp_dir_path);

void delete_output_file(const char *temp_dir_path);

#endif //CRS_UTIL_H
