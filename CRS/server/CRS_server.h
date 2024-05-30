//
// Created by anton on 25.05.24.
//

#ifndef CRS_SRS_SERVER_H
#define CRS_SRS_SERVER_H

#include <CRS/common/CRS_common.h>

typedef int CRS_PORT;

typedef struct CRS_server_config {
    CRS_PORT port;
    CRS_TEXT addr;
} CRS_server_config;

_Noreturn void CRS_server_start(struct CRS_server_config config);

#endif //CRS_SRS_SERVER_H
