#pragma once

#include <vector>
#include <string>
#include <random>
#include <ctime>
#include "raylib.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"

std::string getRandomMap(const std::string& current_map);

void restartLevel(std::vector<Bullet>* playerBullets, const Map& map, std::vector<Enemy>& enemies, const std::vector<Vector2>& positionsOfEnemies);
void changeLevel(std::vector<Bullet>* playerBullets, Map& map, std::vector<Enemy>& enemies, std::vector<Vector2>& positionsOfEnemies);
