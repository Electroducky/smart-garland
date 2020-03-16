#ifndef GARLAND_WEB_HANDLER
#define GARLAND_WEB_HANDLER

#include <ESPmDNS.h>
#include <WebServer.h>
#include <AutoConnectUpdate.h>
#include <AutoConnect.h>

#include "Log.h"

class WebHandler
{
private:
    WebServer* server;
    AutoConnect* portal;
public:
    WebHandler();
    ~WebHandler();
    void handle();
};


#endif //GARLAND_WEB_HANDLER