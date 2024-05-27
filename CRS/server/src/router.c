#include "mongoose.h"

struct route
{
    struct mg_str pattern;
    struct mg_str method;
    void (*fn)(struct mg_connection*, const struct mg_http_message*);
};

// endpoints

static void get_health(struct mg_connection* c, const struct mg_http_message* m)
{
    const char* json = "{\"message\":\"%m:%m\"}";
    mg_http_reply(c, 200, "", json, MG_ESC("status"), MG_ESC("OK"));
}

static void post_attempt(struct mg_connection* c, const struct mg_http_message* m)
{
    printf("attempt added\n");
    mg_http_reply(c, 200, "", "\n");
}


static struct route routes[2];

#define ROUTES_COUNT (sizeof(routes) / sizeof(routes[0]))

void init_routes()
{
    // GET health
    routes[0].pattern = mg_str("/api/v1/health");
    routes[0].method = mg_str("GET");
    routes[0].fn = get_health;

    // POST attempt
    routes[1].pattern = mg_str("/api/v1/attempt");
    routes[1].method = mg_str("POST");
    routes[1].fn = post_attempt;
}

void route_request(struct mg_connection* c, const struct mg_http_message* m)
{
    const struct mg_str uri = m->uri;
    const struct mg_str method = m->method;

    for (int i = 0; i < ROUTES_COUNT; i++)
    {
        if (mg_match(uri, routes[i].pattern, NULL) && mg_strcmp(method, routes[i].method) == 0)
        {
            routes[i].fn(c, m);
        }
    }
}
