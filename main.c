#include "third_party/mongoose.h"
#include <stdlib.h>
#include "CRS_Server.h"


static void setup_output_buffer() { setvbuf(stdout, NULL, _IONBF, -1); }

int main() {
    setup_output_buffer();

    struct CRS_server_config config;
    config.port = 8000;

    CRS_server_start(config);
}
