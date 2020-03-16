#include "AnimationManager.h"

AnimationManager::AnimationManager(Animation *anims[], size_t animsSize)
{
    this->anims = anims;
    this->animsSize = animsSize;
}

AnimationManager::~AnimationManager()
{
    delete leds;
    delete anims;
}

void AnimationManager::setAnims(Animation *anims[], size_t animsSize) {
    this->anims = anims;
    this->animsSize = animsSize;
    currentAnimation = 0;
}

void AnimationManager::previous()
{
    if (currentAnimation == 0)
        currentAnimation = animsSize - 1;
    else
        currentAnimation--;
}

void AnimationManager::next()
{
    if (currentAnimation == animsSize - 1)
        currentAnimation = 0;
    else
        currentAnimation++;
}

void AnimationManager::faster()
{
    if (speed <= 90)
        speed += 10;
}

void AnimationManager::slower()
{
    if (speed >= 10)
        speed -= 10;
}

void AnimationManager::draw()
{
    if (leds != NULL && millis() - lastUpdate >= 200 - 2 * speed)
    {
        anims[currentAnimation]->apply(leds, size);
        FastLED.show();
        lastUpdate = millis();
    }
}
