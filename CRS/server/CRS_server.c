//
// Created by anton on 25.05.24.
//

#include <stdlib.h>
#include <mongoose.h>
#include <CRS/server/CRS_router.h>
#include <CRS/server/CRS_server.h>
#include <CRS/common/CRS_common.h>


char *get_url_from_config(const struct CRS_server_config *config);

static void request_handler(struct mg_connection *c, int ev, void *ev_data) {
    if (ev != MG_EV_HTTP_MSG) {
        return;
    }

    struct mg_http_message *hm = (struct mg_http_message *) ev_data;

    route_request(c, hm);
}

static bool validate_addr(CRS_server_config config) {
    return true; //todo implement it
}

static bool validate_port_by_max_value(CRS_server_config config) {
    return config.port < 100000;
}

static bool validate_port_by_min_value(CRS_server_config config) {
    return config.port >= 0;
}

static bool validate_port(CRS_server_config config) {
    return validate_port_by_min_value(config)
           && validate_port_by_max_value(config);
}

static bool validate_config(CRS_server_config config) {
    return validate_port(config)
           && validate_addr(config);
}

_Noreturn void CRS_server_start(const CRS_server_config config) {
    if (!validate_config(config)) {
        perror("Invalid server config");
        exit(1);
    }

    struct mg_mgr mgr; // Mongoose event manager. Holds all connections
    mg_mgr_init(&mgr); // Initialise event manager
    init_routes();


    const char *url = get_url_from_config(&config);

    mg_http_listen(&mgr, url, request_handler, NULL); // Setup listener

    for (;;) {
        mg_mgr_poll(&mgr, 999);
    }
}

static char *get_port_as_string(const int port) {
    char *port_as_string = calloc(10, sizeof(char));
    itoa(port, port_as_string, 10);
    return port_as_string;
}

char *get_url_from_config(const struct CRS_server_config *config) {
    char *port = get_port_as_string(config->port);
    return concat("http://0.0.0.0:", port);
}
