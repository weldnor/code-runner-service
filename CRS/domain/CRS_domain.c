//
// Created by anton on 28.05.24.
//

#include <string.h>
#include <stdbool.h>
#include <CRS/domain/CRS_domain.h>

enum CRS_lang CRS_lang_by_name(char *name) {
    if (strcmp(name, "cpp") == 0) {
        return CPP;
    }

    if (strcmp(name, "python") == 0) {
        return PYTHON;
    }

    return UNKNOWN;
}

static bool validate_code_by_max_length(struct CRS_attempt *attempt) {
    if (attempt->code == NULL) {
        return false;
    }
    return true;
}

static bool validate_code(struct CRS_attempt *attempt) {
    if (attempt->code == NULL) {
        return false;
    }
    return true;
}

static bool validate_lang(struct CRS_attempt *attempt) {
    if (attempt->lang == UNKNOWN) {
        return false;
    }
    return true;
}

static bool validate_timeout_s_by_min_value(struct CRS_attempt *attempt) {
    return attempt->timeout_s > 0; //todo check it?
}

static bool validate_timeout_s_by_max_value(struct CRS_attempt *attempt) {
    return attempt->timeout_s < 10; //todo check it?
}

static bool validate_timeout_s(struct CRS_attempt *attempt) {
    return validate_timeout_s_by_min_value(attempt)
           && validate_timeout_s_by_max_value(attempt);
}


static bool validate_tests_count_by_min_value(struct CRS_attempt *attempt) {
    return attempt->timeout_s > 0; //todo check it?
}

static bool validate_tests_count_by_max_value(struct CRS_attempt *attempt) {
    return attempt->timeout_s < 10; //todo check it?
}


static bool validate_tests_count(struct CRS_attempt *attempt) {
    return validate_tests_count_by_min_value(attempt)
           && validate_tests_count_by_max_value(attempt);
}


bool CRS_validate_attempt(CRS_attempt *attempt) {
    return validate_code(attempt)
           && validate_lang(attempt)
           && validate_timeout_s(attempt)
           && validate_tests_count(attempt);
}
