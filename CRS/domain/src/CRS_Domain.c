//
// Created by anton on 28.05.24.
//

#include <string.h>
#include "CRS_Domain.h"


enum CRS_lang CRS_lang_by_name(char *name) {
    if (strcmp(name, "cpp") == 0) {
        return CPP;
    }

    if (strcmp(name, "python") == 0) {
        return PYTHON;
    }

    return UNKNOWN;
}

