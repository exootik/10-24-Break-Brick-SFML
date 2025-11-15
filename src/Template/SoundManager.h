#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

class SoundManager
{
public:
	SoundManager();

    void playInGameSound();
    void playEndGameSound();
    void stopInGameSound();
    void stopEndGameSound();
    void playBufferInGame();

private:
    sf::Sound briqueSound, inGameSound, endGameSound;
    sf::SoundBuffer briqueBuffer, inGameBuffer, endGameBuffer;

};

#endif



