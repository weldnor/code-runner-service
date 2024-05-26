//
// Created by anton on 25.05.24.
//

#include <stdlib.h>
#include "../../../third_party/mongoose.h"
#include "CRS_Runner.h"
#include "CRS_Common.h"

struct CRS_server_config {
    int port;
    char *addr;
};

char *get_url_from_config(const struct CRS_server_config *config);

static void request_handler(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) { // New HTTP request received
        struct mg_http_message *hm =
                (struct mg_http_message *) ev_data; // Parsed HTTP request

        CRS_run_code("code", NULL, 1000);

        mg_http_reply(c, 200, "", "{%m:%s}\n", MG_ESC("message"),
                      "hello world"); // Yes. Respond JSON
    }
}

_Noreturn void CRS_server_start(const struct CRS_server_config config) {
    struct mg_mgr mgr; // Mongoose event manager. Holds all connections
    mg_mgr_init(&mgr); // Initialise event manager

    char *url = get_url_from_config(&config);

    mg_http_listen(&mgr, url, request_handler, NULL); // Setup listener

    for (;;) {
        mg_mgr_poll(&mgr, 999); // Infinite event loop
    }
}

char *get_url_from_config(const struct CRS_server_config *config) {
    char s_port[33];
    itoa((*config).port, s_port, 10);

    return concat("http://0.0.0.0:", s_port);
}
