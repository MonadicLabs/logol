#pragma once

#include "runnable.h"

#define MG_ENABLE_CALLBACK_USERDATA 1
#include <mongoose.h>

namespace logol
{
class Server : public Runnable
{
public:
    Server( uint16_t port );
    virtual ~Server();

    virtual void run();
    struct mg_serve_http_opts s_http_server_opts;

private:
    static void ev_handler(struct mg_connection *nc, int ev, void *ev_data, void* user_data );
    static int is_websocket(const struct mg_connection *nc);

protected:

};
}
