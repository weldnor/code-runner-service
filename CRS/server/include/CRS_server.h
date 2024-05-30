//
// Created by anton on 25.05.24.
//

#ifndef CRS_SRS_SERVER_H
#define CRS_SRS_SERVER_H

typedef struct CRS_server_config {
    int port;
    char *addr;
} CRS_server_config;

_Noreturn void CRS_server_start(struct CRS_server_config config);

#endif //CRS_SRS_SERVER_H
