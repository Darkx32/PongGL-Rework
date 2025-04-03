#pragma once
#include <SDL3/SDL.h>
#include <AudioEngine/AudioEngine.hpp>
#include <imgui.h>
#include "global.hpp"
#include "sound.hpp"

class SoundControllerUI{
private:
    Sound* sound;

public:
    void init(Sound*);
    void render();

    bool showController = false;
    int musicVolume = 100;
    int sfxVolume = 100;
};