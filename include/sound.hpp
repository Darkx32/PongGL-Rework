#pragma once
#include <AudioEngine/AudioEngine.hpp>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include "global.hpp"

class Sound{
private:
    // Sound players
    AudioEngine::AudioPlayer sfx;
    AudioEngine::AudioPlayer music;
    
    // Sounds streams
    AudioEngine::AudioStream* background;
    AudioEngine::AudioStream* ballCollision;
    AudioEngine::AudioStream* win;
public:
    SDL_AppResult init(const char*, const char*, const char*);

    // Sound music
    void playMusicSound();
    
    // Sound sfx
    void playCollisionBall(glm::vec2);
    void playWin();

    void updateSwaps();
    void close();

    void updateVolumes(int musicVolume, int sfxVolume);
};