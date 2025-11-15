#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager() {
    // Charger le son une seule fois
    if (!briqueBuffer.loadFromFile("../../../src/Template/Asset/bubblepop.wav")) {
        std::cerr << "Erreur : impossible de charger le fichier audio in game !" << std::endl;
    }
    briqueSound.setBuffer(briqueBuffer); // Associer le buffer au son

    if (!endGameBuffer.loadFromFile("../../../src/Template/Asset/CHOUCHOUCHOUCHOU.wav")) {
        std::cerr << "Erreur : impossible de charger le fichier audio de fin de partie !" << std::endl;
    }
    endGameSound.setBuffer(endGameBuffer);

    if (!inGameBuffer.loadFromFile("../../../src/Template/Asset/ingamesound.wav")) {
        std::cerr << "Erreur : impossible de charger le fichier audio in-game !" << std::endl;
    }
    inGameSound.setBuffer(inGameBuffer);
}

void SoundManager::playInGameSound() {
    if (inGameSound.getStatus() != sf::Sound::Playing) {
        inGameSound.play();
    }
}
void SoundManager::playEndGameSound() {
    endGameSound.setVolume(70);
    endGameSound.play();
}
void SoundManager::stopInGameSound() {
    inGameSound.stop();
}
void SoundManager::stopEndGameSound() {
    endGameSound.stop();
}
void SoundManager::playBufferInGame() {
    briqueSound.play();
}