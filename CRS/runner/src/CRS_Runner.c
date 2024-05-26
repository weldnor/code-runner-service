//
// Created by anton on 24.05.24.
//


#include <string.h>

struct CRS_test {
    char *input;
    char *expected;
};

enum CRS_lang {
    CPP,
    PYTHON,
};

enum CRS_lang CRS_lang_by_name(char *name) {
    if (strcmp(name, "cpp") == 0) {
        return CPP;
    }

    if (strcmp(name, "python") == 0) {
        return PYTHON;
    }
}

void CRS_run_code(char *code, enum CRS_lang lang, struct CRS_test tests[], int timeout) {

}