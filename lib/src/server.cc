
#include "server.h"



int logol::Server::is_websocket(const struct mg_connection *nc) {
  return nc->flags & MG_F_IS_WEBSOCKET;
}

void logol::Server::ev_handler(struct mg_connection *nc, int ev, void *ev_data, void *user_data)
{
    logol::Server* server = (logol::Server*)ev_data;

    switch (ev) {
    case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
        /* New websocket connection. Tell everybody. */
        // broadcast(nc, mg_mk_str("++ joined"));
        break;
    }
    case MG_EV_WEBSOCKET_FRAME: {
        struct websocket_message *wm = (struct websocket_message *) ev_data;
        /* New websocket message. Tell everybody. */
        struct mg_str d = {(char *) wm->data, wm->size};
        // broadcast(nc, d);
        break;
    }
    case MG_EV_HTTP_REQUEST: {
        server->s_http_server_opts.document_root = ".";  // Serve current directory
        server->s_http_server_opts.enable_directory_listing = "yes";
        mg_serve_http(nc, (struct http_message *) ev_data, server->s_http_server_opts);
        break;
    }
    case MG_EV_CLOSE: {
        /* Disconnect. Tell everybody. */
        if (is_websocket(nc)) {
            // broadcast(nc, mg_mk_str("-- left"));
        }
        break;
    }
    }
}

void logol::Server::run()
{
    struct mg_mgr mgr;
    struct mg_connection *nc;

    /*
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
    setvbuf(stdout, NULL, _IOLBF, 0);
    setvbuf(stderr, NULL, _IOLBF, 0);
    */

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "8000", ev_handler, this);
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.document_root = ".";  // Serve current directory
    s_http_server_opts.enable_directory_listing = "yes";

    printf("Started on port %s\n", "8000");
    while (true) {
        mg_mgr_poll(&mgr, 200);
    }

    mg_mgr_free(&mgr);
}
