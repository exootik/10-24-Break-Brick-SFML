#ifndef LEVELCONFIG_H
#define LEVELCONFIG_H
#include "pch.h"
#include <vector>
#include "Brique.h"
#include "PowerUp.h"



struct LevelConfig {
    int rows;
    int cols;
    float offsetX;
    float offsetY;
    int brickWidth;
    int brickHeight;
    int brickSizeX;
    int brickSizeY;
};

// Déclaration de la constante avec les configurations de chaque niveau
extern const std::vector<LevelConfig> levelConfigs;


// Déclaration de la fonction pour initialiser le niveau
void initializeLevel(int level, std::vector<Brick>& bricks, std::vector<PowerUp>& powerUps);

void createLevel3PowerUps(std::vector<PowerUp>& powerUps);

void createLevel2PowerUps(std::vector<PowerUp>& powerUps);

#endif
