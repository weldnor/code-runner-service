//
// Created by anton on 5/27/24.
//

#ifndef ROUTER_H
#define ROUTER_H

struct route;
void route_request(struct mg_connection* c, const struct mg_http_message* m);
void init_routes();
#endif //ROUTER_H
