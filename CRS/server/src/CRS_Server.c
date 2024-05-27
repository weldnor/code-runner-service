//
// Created by anton on 25.05.24.
//

#include <stdlib.h>
#include "mongoose.h"
#include "CRS_Common.h"
#include "router.h"

struct CRS_server_config
{
    int port;
    char* addr;
};

char* get_url_from_config(const struct CRS_server_config* config);

static void request_handler(struct mg_connection* c, int ev, void* ev_data)
{
    if (ev != MG_EV_HTTP_MSG)
    {
        return;
    }

    struct mg_http_message* hm = (struct mg_http_message*)ev_data;

    route_request(c, hm);
}

_Noreturn void CRS_server_start(const struct CRS_server_config config)
{
    struct mg_mgr mgr; // Mongoose event manager. Holds all connections
    mg_mgr_init(&mgr); // Initialise event manager
    init_routes();
    const char* url = get_url_from_config(&config);

    mg_http_listen(&mgr, url, request_handler, NULL); // Setup listener

    for (;;)
    {
        mg_mgr_poll(&mgr, 999); // Infinite event loop
    }
}

char* get_url_from_config(const struct CRS_server_config* config)
{
    char s_port[33];
    itoa(config->port, s_port, 10);

    return concat("http://0.0.0.0:", s_port);
}
