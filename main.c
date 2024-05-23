#include "third_party/mongoose.h"
#include <stdlib.h>

static void runCode(char *code) {
  printf("hello world\n");
}

// Connection event handler function
static void fn(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_MSG) { // New HTTP request received
    struct mg_http_message *hm =
        (struct mg_http_message *)ev_data; // Parsed HTTP request
    runCode("hello world");
    mg_http_reply(c, 200, "", "{%m:%s}\n", MG_ESC("message"),
                  "hello world"); // Yes. Respond JSON
  }
}

static void setup_output_buffer() { setvbuf(stdout, NULL, _IONBF, -1); }

static void start_server() {
  struct mg_mgr mgr; // Mongoose event manager. Holds all connections

  mg_mgr_init(&mgr); // Initialise event manager
  mg_http_listen(&mgr, "http://0.0.0.0:8000", fn, NULL); // Setup listener
  for (;;) {
    mg_mgr_poll(&mgr, 999); // Infinite event loop
  }
}

int main() {
  setup_output_buffer();
  start_server();
  return 0;
}
