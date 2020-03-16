#include "WebHandler.h"

WebHandler::WebHandler()
{
    server = new WebServer();
    portal = new AutoConnect(*server);

    server->on("/", nullptr);
    server->on("/set", nullptr);
    
    if (portal->begin()) {
        Serial.println("WiFi connected: " + WiFi.localIP().toString());
        if (MDNS.begin("electroducky")) {
            Serial.println("mDNS responder started");
            MDNS.addService("http", "tcp", 80);
        }
    }
}

WebHandler::~WebHandler()
{
    delete server;
    delete portal;
}

void WebHandler::handle() {

}