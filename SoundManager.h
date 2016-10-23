#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
using namespace std;

class SoundManager
{
public:
    SoundManager();

    void playSound(string file);
    void playMusic(string file);

private:
    sf::SoundBuffer* buffer;
    sf::Sound* sound;
    sf::Music* music;
};

#endif // SOUNDMANAGER_H
