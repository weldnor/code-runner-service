//
// Created by anton on 28.05.24.
//

#ifndef CRS_CRS_DOMAIN_H
#define CRS_CRS_DOMAIN_H


#include <stdbool.h>

struct CRS_test {
    char *input;
    char *expected;
};

enum CRS_lang {
    CPP,
    PYTHON,
    UNKNOWN,
};

struct CRS_attempt {
    char *attempt_id;
    char *code;
    enum CRS_lang lang;
    int timeout_s;
    size_t tests_count;
    struct CRS_test *tests;
};

enum CRS_lang CRS_lang_by_name(char *name);

bool CRS_validate_attempt(struct CRS_attempt *attempt);

#endif //CRS_CRS_DOMAIN_H
