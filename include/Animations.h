#ifndef GARLAND_ANIMATIONS
#define GARLAND_ANIMATIONS

#include <Arduino.h>
#include "Animation.h"
#include <math.h>

extern "C" {
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
}

class Rainbow : public Animation
{
private:
    byte counter;

public:
    void apply(CRGB *leds, size_t size)
    {
        for (int i = 0; i < size; i++)
        {
            leds[i] = CHSV(counter + i*2, 255, 255);
        }
        counter++;
    }
};

class Color : public Animation
{
    private:
    byte h;
    byte s;
    byte v;
    public:
    Color(byte h, byte s, byte v) 
    {
        this->h = h;
        this->s = s;
        this->v = v;
    }

    void apply(CRGB *leds, size_t size)
    {
        for (int i = 0; i < size; i++)
            leds[i] = CHSV(h, s, v);
    }
};

class SingleLed : public Animation
{
public:
    void apply(CRGB *leds, size_t size)
    {
        for (int i = 0; i < size; i++)
            leds[i] = CRGB(102, 255, 204);
    }
};

class Fading : public Animation
{
private:
    byte counter;
public:
    void apply(CRGB *leds, size_t size)
    {
        byte value = 127 * (cos(counter * 4 * PI / 255.0) + 3);
        for (int i = 0; i < size; i++)
            leds[i] = CHSV(150, 255, value);
        counter++;
    }
};

class Luanim : public Animation
{
    private:
        lua_State * L;
    public:
    Luanim(const char code[]) {
        L = luaL_newstate();
        luaL_openlibs(L);
        luaL_loadbuffer(L, code, strlen(code), code);
        lua_pcall(L, 0, 0, 0);
    }

    ~Luanim() {
        lua_close(L);
    }

    void apply(CRGB *leds, size_t size)
    {
            lua_getglobal(L, "leds");
            lua_pcall(L, 0, 1, 0);
            lua_isinteger(L, -1);
            int z = lua_tointeger(L, -1);
            lua_pop(L, 1);
            for (int i = 0; i < size; i++)
                leds[i] = CHSV(z, 255, 255);
    }
};

#endif //GARLAND_ANIMATIONS