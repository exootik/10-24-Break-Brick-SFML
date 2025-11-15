#include "pch.h"
#include "LevelConfig.h"

static sf::Texture powerUpTexture;

const std::vector<LevelConfig> levelConfigs = {
    {1, 1, 5, 5, 180, 60, 150, 45}, // Niveau 1 
    {1, 1, 6, 8, 120, 40, 100, 30}, // Niveau 2 
    {6, 15, 15, 8, 70, 30, 70, 25}  // Niveau 3 
};

void initializeLevel(int level, std::vector<Brick>& bricks, std::vector<PowerUp>& powerUps) {
    if (level < levelConfigs.size()) {
        bricks.clear();
        const LevelConfig& config = levelConfigs[level];
        Brick::createBrickGrid(bricks, config.rows, config.cols, config.offsetX, config.offsetY, config.brickWidth, config.brickHeight, config.brickSizeX, config.brickSizeY);
        // Debug : Afficher confirmation
        std::cout << "Niveau " << level << " initialisé avec " << bricks.size() << " briques." << std::endl;
    }
    if (!powerUpTexture.loadFromFile("../../../src/Template/Asset/imagePower.png")) {
        std::cerr << "Erreur de chargement de l'image du Power-Up !" << std::endl;
    }
    if (level == 2) {
        createLevel3PowerUps(powerUps);

        std::cout << "power up";
    }

  
    if (level == 1) {
        if (!powerUpTexture.loadFromFile("../../../src/Template/Asset/Giant.png")) {
            std::cerr << "Erreur de chargement de l'image du Power-Up !" << std::endl;
        }
        createLevel2PowerUps(powerUps);
    }
}


void createLevel3PowerUps(std::vector<PowerUp>& powerUps) {
    
    PowerUp powerUpX2(PowerUp::Type::x2, { 100, 550 }, powerUpTexture);
    powerUpX2.setSize(50.0f, 50.0f);
    powerUps.push_back(powerUpX2);
}

void createLevel2PowerUps(std::vector<PowerUp>& powerUps) {
    PowerUp powerUpGiant(PowerUp::Type::giant, { 900, 550 }, powerUpTexture); 
    powerUpGiant.setSize(50.0f, 50.0f);
    powerUps.push_back(powerUpGiant);
}