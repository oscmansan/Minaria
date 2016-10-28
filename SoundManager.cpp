#include "SoundManager.h"

SoundManager::SoundManager() {}

void SoundManager::playSound(string file) {
    playSound(file,volume);
}

void SoundManager::playSound(string file, float v)
{
    // Load a sound buffer from a wav file
    buffer = new sf::SoundBuffer();
    if (!buffer->loadFromFile(file))
         return;
    // Create a sound instance and play it
    sound = new sf::Sound(*buffer);
    sound->setVolume(v);
    sound->play();
}

void SoundManager::playMusic(string file) {
    playMusic(file,volume);
}

void SoundManager::playMusic(string file, float v)
{
    // Load an ogg music file
    music = new sf::Music();
    if (!music->openFromFile(file))
        return;
    // Play it
    music->setLoop(true);
    music->setVolume(v);
    music->play();
}

void SoundManager::stopSound()
{
    if (sound)
    {
        sound->stop();
        delete sound;
        sound = NULL;
    }
    if (buffer)delete buffer;
}

void SoundManager::stopMusic()
{
    if (music)
    {
        music->stop();
        delete music;
        music = NULL;
    }
}

void SoundManager::setVolume(float v)
{
    volume = v;
}

void SoundManager::setSoundLoop(bool loop)
{
    sound->setLoop(loop);
}

void SoundManager::setMusicLoop(bool loop)
{
    music->setLoop(loop);
}
