#include "mongoose.h"
#include "CRS_Domain.h"
#include "CRS_Runner.h"


struct route {
    struct mg_str pattern;
    struct mg_str method;

    void (*fn)(struct mg_connection *, const struct mg_http_message *);
};

// endpoints
static void ok_get_health_reply(struct mg_connection *c) {
    const char *json = "{%m : %m}";
    mg_http_reply(c, 200, "", json, MG_ESC("status"), MG_ESC("OK"));
}

static void get_health(struct mg_connection *c, const struct mg_http_message *m) {
    ok_get_health_reply(c);
}

static void parse_attempt_tests(struct mg_str tests_json, struct CRS_test **tests, size_t *count_of_tests) {
    *count_of_tests = 0;

    size_t ofs = 0;
    struct mg_str key, val;

    while ((ofs = mg_json_next(tests_json, ofs, &key, &val)) > 0) {
        (*count_of_tests)++;
    }

    struct CRS_test *tests_arr = malloc(sizeof(struct CRS_test) * *count_of_tests);

    int i = 0;
    while ((ofs = mg_json_next(tests_json, ofs, &key, &val)) > 0) {
        tests_arr[i].input = mg_json_get_str(val, "$.input");
        tests_arr[i].expected = mg_json_get_str(val, "$.expected");
        i++;
    }

    *tests = tests_arr;
}

static struct CRS_attempt parse_attempt(struct mg_str json) {
    struct CRS_attempt attempt;

    char *code = mg_json_get_str(json, "$.code");
    if (code == NULL) {
        //todo
    }
    attempt.code = code;

    char *lang = mg_json_get_str(json, "$.lang");
    if (lang == NULL) {
        //todo
    }
    //todo lang not exists
    attempt.lang = CRS_lang_by_name(lang);


    long timeout_s = mg_json_get_long(json, "$.timeout_s", -1);
    if (timeout_s == -1) {
        //todo
    }
    attempt.timeout_s = (int) timeout_s;

    struct mg_str tests_json = mg_json_get_tok(json, "$.tests");

    attempt.tests = NULL;
    parse_attempt_tests(tests_json, &attempt.tests, &attempt.tests_count);
    return attempt;
}

static void fail_post_attempt_reply(struct mg_connection *c) {
    const char *json = "{\"status\": %m}";
    mg_http_reply(c, 200, "", json, MG_ESC("FAIL"));
}

static void pass_post_attempt_reply(struct mg_connection *c) {
    const char *json = "{\"status\": %m}";
    mg_http_reply(c, 200, "", json, MG_ESC("PASS"));
}

static void unknown_post_attempt_reply(struct mg_connection *c) {
    const char *json = "{\"status\": %m}";
    mg_http_reply(c, 200, "", json, MG_ESC("UNKNOWN"));
}

static void post_attempt(struct mg_connection *c, const struct mg_http_message *m) {
    struct CRS_attempt attempt = parse_attempt(m->body);

    enum CRS_run_status status = CRS_run_code(attempt);

    if (status == FAIL) {
        fail_post_attempt_reply(c);
    }

    if (status == PASS) {
        pass_post_attempt_reply(c);
    }

    unknown_post_attempt_reply(c);
}

#define ROUTES_COUNT 2

static struct route routes[ROUTES_COUNT];

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
