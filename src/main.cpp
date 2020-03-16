#include <Arduino.h>
#include <Esp.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <AutoConnectUpdate.h>
#include <AutoConnect.h>
#include <FastLED.h>

extern "C" {
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
}

#include <string.h>

#include "Animations.h"
#include "AnimationManager.h"
#include "ESPAsyncWebServer.h"
#include "WebPages.h"


// #define PIN 32
#define NUM_LEDS 64
#define LFT 4
#define RGT 2
#define BTN_DEL 500

long left = 0;
long right = 0;

const uint8_t LED_PIN = 32;

WebServer Server;
AutoConnect Portal(Server);

Luanim* luan = new Luanim("function leds () return 122 end");

Animation *anims[] = {
    luan,
     new Rainbow(),
    new Fading(),
    new SingleLed()};

AnimationManager anime(anims, sizeof(anims) / sizeof(anims[0]));

void handleButtons();

void callLeft()
{
  left = millis();
}

void callRight()
{
  right = millis();
}

void rootPage() {
  char content[] = "\"Hello, world\"";
  Server.send(200, "application/json", content);
}

void handle() {

    *anims = {
    new Color(
      Server.arg(0).toInt(),
      Server.arg(1).toInt(),
      Server.arg(2).toInt()
    )};
    anime.setAnims(anims, 1);
    Server.send(200, "application/json", "\"message received\"");
}

void newAnim() {
  Server.send(200, "text/html", index_html);
}

void anim() {
  String s = Server.arg("anim");
  char luacode[s.length()];
  s.toCharArray(luacode, s.length());

  delete luan;
  luan = new Luanim(luacode);
  *anims = {
    luan
  };
  anime.setAnims(anims, 1);

  Server.send(200, "application/json", "\"message received\"");
}

void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  Server.on("/", rootPage);
  Server.on("/newanim", newAnim);
  Server.on("/set", handle);
  Server.on("/anim", anim);
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
    if (MDNS.begin("electroducky")) {
      Serial.println("mDNS responder started");
      MDNS.addService("http", "tcp", 80);
    }
  }
  pinMode(LFT, INPUT);
  attachInterrupt(digitalPinToInterrupt(LFT), callLeft, RISING);

  pinMode(RGT, INPUT);
  attachInterrupt(digitalPinToInterrupt(RGT), callRight, RISING);

  anime.connect<LED_PIN>(NUM_LEDS);
}

static int l_print (lua_State *L) {
  const char* d = luaL_checkstring(L, 1);
  Serial.println(d);
  return 0;
}

void checkLua() {
  lua_State * L = luaL_newstate();
  lua_pushcfunction(L, l_print);
  lua_setglobal(L, "print");
  luaL_openlibs(L);

  // execute script
  const char lua_script[] = "print('Hello World!')";
  int load_stat = luaL_loadbuffer(L, lua_script, strlen(lua_script), lua_script);
  lua_pcall(L, 0, 0, 0);

  // cleanup
  lua_close(L);
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED) {
    // Some sketch code for the connected scene is here.
  }
  else {
    // Some sketch code for not connected scene is here.
  }
  Portal.handleClient();
  handleButtons();
  anime.draw();
  // checkLua();
}

void handleButtons()
{
  long current = millis();
  if (left != 0 && right != 0)
  {
    if (right > left)
      anime.next();
    if (right < left)
      anime.previous();
    right = 0;
    left = 0;
  }
  if (left != 0 && current - left > BTN_DEL)
  {
    anime.slower();
    right = 0;
    left = 0;
  }
  if (right != 0 && current - right > BTN_DEL)
  {
    anime.faster();
    right = 0;
    left = 0;
  }
}
