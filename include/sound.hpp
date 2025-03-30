#pragma once
#include <AudioEngine/AudioEngine.hpp>
#include <SDL3/SDL.h>

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
    void playCollisionBall();
    void playWin();

    void updateSwaps();

    void close();
};