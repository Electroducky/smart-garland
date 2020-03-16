#ifndef GARLAND_ANIMATION_MANAGER
#define GARLAND_ANIMATION_MANAGER

#include <Arduino.h>
#include "Animation.h"

class AnimationManager
{
private:
    CRGB *leds;
    size_t size;
    int speed = 100;
    Animation **anims;
    size_t animsSize;
    uint16_t currentAnimation = 0;
    long lastUpdate = 0;

public:
    AnimationManager(Animation *anims[], size_t animsSize);
    ~AnimationManager();

    void previous();
    void next();
    void faster();
    void slower();
    void draw();

    void setAnims(Animation *anims[], size_t animsSize);

    template <uint8_t DATA_PIN>
    void connect(int size)
    {
        this->size = size;
        this->leds = new CRGB[size];
        FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, size).setCorrection(TypicalSMD5050);
        FastLED.setBrightness(50);
    }
};

#endif //GARLAND_ANIMATION_MANAGER