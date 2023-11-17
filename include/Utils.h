#include <vector>
#include <string>
#include <random>
#include <ctime>
#include "raylib.h"
#include "HighScoresWindow.h"
#include "Map.h"
#include "Player.h"
#include "Constants.h"

Texture2D* getEnemyImages();
std::string getRandomMap(const std::string& current_map);

void restartLevel(Player& player, const Map& map, std::vector<Enemy>& enemies, const std::vector<Vector2>& positionsOfEnemies, Texture2D* imagesOfEnemy);
void changeLevel(Player& player, std::vector<Bullet>* playerBullets, Map& map, std::vector<Enemy>& enemies, std::vector<Vector2>& positionsOfEnemies, Texture2D* imagesOfEnemy);