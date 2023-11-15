#include <iostream>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <random>
#include "raylib.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Constants.h"

struct V2 {
    int i, j;
};

struct V3 {
    V2 pos;
    V3* parent;
};

struct Node {
    int G, H, F;
    V2 pos;
    int number;
};

std::string AStar(char **labirintas, int n, int m, V2 A, V2 B);
char** VecStr2CharDP(std::vector<std::string> maze);
V2 Vector2ToV2(Vector2 position);

Texture2D* getEnemyImages();

std::string getRandomMap(const std::string& current_map);
