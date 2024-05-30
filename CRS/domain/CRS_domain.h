//
// Created by anton on 28.05.24.
//

#ifndef CRS_CRS_DOMAIN_H
#define CRS_CRS_DOMAIN_H

#include <stdbool.h>
#include <CRS/common/CRS_common.h>

typedef char *CRS_ATTEMPT_ID;

typedef struct CRS_test {
    CRS_TEXT input;
    CRS_TEXT expected;
} CRS_test;

typedef enum CRS_lang {
    CPP,
    PYTHON,
    UNKNOWN,
} CRS_lang;

typedef struct CRS_attempt {
    CRS_ATTEMPT_ID *attempt_id;
    CRS_TEXT code;
    CRS_lang lang;
    int timeout_s;
    size_t tests_count;
    CRS_test *tests;
} CRS_attempt;

CRS_lang CRS_lang_by_name(char *name);

bool CRS_validate_attempt(CRS_attempt *attempt);

#endif //CRS_CRS_DOMAIN_H
