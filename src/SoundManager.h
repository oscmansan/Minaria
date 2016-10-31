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
    void setSoundLoop(bool loop);
    void setMusicLoop(bool loop);

private:
    sf::SoundBuffer* buffer = NULL;
    sf::Sound* sound = NULL;
    sf::Music* music = NULL;

    float volume = 80.f;
};

#endif // SOUNDMANAGER_H
