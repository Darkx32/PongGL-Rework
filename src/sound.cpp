#include "sound.hpp"

SDL_AppResult Sound::init(const char *backgroundFile, const char *collisionFile, const char *winFile)
{
    AudioEngine::setLogLevel(AudioEngine::LOG_QUIET);

    this->sfx = AudioEngine::AudioPlayer();
    this->music = AudioEngine::AudioPlayer();

    AudioEngine::AudioBuffer backgroundBuffer(backgroundFile);
    AudioEngine::AudioBuffer collisionBuffer(collisionFile);
    AudioEngine::AudioBuffer winBuffer(winFile);

    this->background = new AudioEngine::AudioStream(backgroundBuffer);
    this->ballCollision = new AudioEngine::AudioStream(collisionBuffer);
    this->win = new AudioEngine::AudioStream(winBuffer);

    this->music.addStream(this->background->getStream());
    this->sfx.addStream(this->ballCollision->getStream());
    this->sfx.addStream(this->win->getStream());

    return SDL_APP_CONTINUE;
}

void Sound::playMusicSound()
{
    //if (!this->music.isRunningAudio())
    this->music.playStream(this->background->getStream());
}

void Sound::playCollisionBall()
{
    this->sfx.playStream(this->ballCollision->getStream());
}

void Sound::playWin()
{
    this->sfx.playStream(this->win->getStream());
}

void Sound::updateSwaps()
{
    this->music.updateSwaps();
    this->sfx.updateSwaps();
}

void Sound::close()
{
    delete this->background;
    delete this->ballCollision;
    delete this->win;
}
