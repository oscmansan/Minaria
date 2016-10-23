#include "SoundManager.h"

#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;

SoundManager::SoundManager()
{
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sound.wav"))
         cout << "Could not load file" << endl;
}
