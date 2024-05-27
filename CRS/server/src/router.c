#include "mongoose.h"
#include "CRS_Domain.h"
#include "CRS_Runner.h"


struct route {
    struct mg_str pattern;
    struct mg_str method;

    void (*fn)(struct mg_connection *, const struct mg_http_message *);
};

// endpoints

static void get_health(struct mg_connection *c, const struct mg_http_message *m) {
    const char *json = "{\"message\":\"%m:%m\"}";
    mg_http_reply(c, 200, "", json, MG_ESC("status"), MG_ESC("OK"));
}

static void post_attempt(struct mg_connection *c, const struct mg_http_message *m) {
    printf("attempt added\n");

    struct CRS_attempt attempt;

    char *code = mg_json_get_str(m->body, "$.code");
    if (code == NULL) {
        //todo
    }
    attempt.code = code;

    char *lang = mg_json_get_str(m->body, "$.lang");
    if (lang == NULL) {
        //todo
    }
    //todo lang not exists
    attempt.lang = CRS_lang_by_name(lang);

    //todo add logger
    printf("%s\n", code);
    printf("%s\n", lang);

    CRS_run_code(attempt);

    const char *json = "{\"message\":\"%m:%m\"}";
    mg_http_reply(c, 200, "", json, MG_ESC("status"), MG_ESC("OK"));
}

static struct route routes[2];

#define ROUTES_COUNT (sizeof(routes) / sizeof(routes[0]))

void init_routes() {
    // GET health
    routes[0].pattern = mg_str("/api/v1/health");
    routes[0].method = mg_str("GET");
    routes[0].fn = get_health;

    // POST attempt
    routes[1].pattern = mg_str("/api/v1/attempt");
    routes[1].method = mg_str("POST");
    routes[1].fn = post_attempt;
}

void route_request(struct mg_connection *c, const struct mg_http_message *m) {
    const struct mg_str uri = m->uri;
    const struct mg_str method = m->method;

    for (int i = 0; i < ROUTES_COUNT; i++) {
        if (mg_match(uri, routes[i].pattern, NULL) && mg_strcmp(method, routes[i].method) == 0) {
            routes[i].fn(c, m);
        }
    }
}
