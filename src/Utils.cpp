#include "../include/Utils.h"

Texture2D* getEnemyImages(){
    auto* images = new Texture2D[4];

    Image current_image;
    for (int i = 0; i < 4; i++){
        current_image = LoadImage(CONSTANTS::ENEMY_IMAGES_FILE_NAMES[i].c_str());
        images[i] = LoadTextureFromImage(current_image);
        UnloadImage(current_image);
    }

    return images;
}

std::string getRandomMap(const std::string& current_map){
    int seed = (int) time(nullptr);
    std::default_random_engine generator(seed);

    if (current_map.empty()){
        return CONSTANTS::LEVELS[generator() % CONSTANTS::LEVELS.size()];
    }

    int current_map_index;
    for (int i = 0; i < CONSTANTS::LEVELS.size(); i++){
        if (current_map == CONSTANTS::LEVELS[i]){
            current_map_index = i;
        }
    }

    int new_map_index = current_map_index;
    while (current_map_index == new_map_index){
        new_map_index = (int) (generator() % CONSTANTS::LEVELS.size());
    }

    return CONSTANTS::LEVELS[new_map_index];
}

void restartLevel(Player& player, const Map& map, std::vector<Enemy>& enemies, const std::vector<Vector2>& positionsOfEnemies, Texture2D* imagesOfEnemy){
    player.removeOneLive();

    player.update(map.getPlayerPosition(), map.getWhereCameFrom());

    enemies.clear();
    int seed = (int) time(nullptr);
    std::default_random_engine generator(seed);
    for (int i = 0; i < positionsOfEnemies.size(); i++){
        enemies.emplace_back(positionsOfEnemies[i], CONSTANTS::DISTANCE_TO_MOVE_FOR_ENEMY[generator() % CONSTANTS::DISTANCE_TO_MOVE_FOR_ENEMY.size()]);
        enemies[i].setImages(imagesOfEnemy);
        enemies[i].determineMoving(map.getMovingDirectionsForEnemy(positionsOfEnemies[i]));
    }
}

void changeLevel(Player& player, std::vector<Bullet>* playerBullets, Map& map, std::vector<Enemy>& enemies, std::vector<Vector2>& positionsOfEnemies, Texture2D* imagesOfEnemy){
    player.update(map.getPlayerPosition(), map.getWhereCameFrom());
    playerBullets->clear();

    enemies.clear();
    positionsOfEnemies = map.getEnemiesPositions();
    int seed = (int) time(nullptr);
    std::default_random_engine generator(seed);
    for (int i = 0; i < positionsOfEnemies.size(); i++){
        enemies.emplace_back(positionsOfEnemies[i], CONSTANTS::DISTANCE_TO_MOVE_FOR_ENEMY[generator() % CONSTANTS::DISTANCE_TO_MOVE_FOR_ENEMY.size()]);
        enemies[i].setImages(imagesOfEnemy);
        enemies[i].determineMoving(map.getMovingDirectionsForEnemy(positionsOfEnemies[i]));
    }
}
