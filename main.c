#include <stdio.h>
#include <CRS/server/CRS_server.h>

static void setup_output_buffer() { setvbuf(stdout, NULL, _IONBF, -1); }

static void init_components() {
    setup_output_buffer();
}

static CRS_server_config create_server_config() {
    CRS_server_config config;
    config.port = 8000;
    config.addr = "0.0.0.0";
    return config;
}

static void start_server() {
    CRS_log_info("staring server...");
    CRS_server_config config = create_server_config();
    CRS_server_start(config);
}

int main() {
    init_components();
    start_server();
}
