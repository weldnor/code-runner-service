//
// Created by anton on 25.05.24.
//

#ifndef CRS_SRS_SERVER_H
#define CRS_SRS_SERVER_H

struct CRS_server_config {
    int port;
};

_Noreturn void CRS_server_start(struct CRS_server_config config);

#endif //CRS_SRS_SERVER_H
