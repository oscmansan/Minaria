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
    void playSound(string file, float v);
    void playMusic(string file);
    void playMusic(string file, float v);
    void stopSound();
    void stopMusic();
    void setVolume(float v);

private:
    sf::SoundBuffer* buffer;
    sf::Sound* sound;
    sf::Music* music;

    float volume;
};

#endif // SOUNDMANAGER_H
