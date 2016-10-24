#include "SoundManager.h"

SoundManager::SoundManager() {}

void SoundManager::playSound(string file)
{
    // Load a sound buffer from a wav file
    buffer = new sf::SoundBuffer();
    if (!buffer->loadFromFile(file))
         return;
    // Create a sound instance and play it
    sound = new sf::Sound(*buffer);
    sound->play();
}

void SoundManager::playMusic(string file)
{
    // Load an ogg music file
    music = new sf::Music();
    if (!music->openFromFile(file))
        return;
    // Play it
    music->setLoop(true);
    music->play();
}
