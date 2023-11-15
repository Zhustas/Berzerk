#include "../include/Utils.h"

std::string AStar(char **labirintas, int n, int m, V2 A, V2 B){
    std::multimap<std::pair<int, int>, Node> toSearch;

    toSearch.insert({{0, 0}, {0, 0, 0, A, 0}});

    int dirs[4][2] = {
            {1, 0},
            {0, 1},
            {-1, 0},
            {0, -1}
    };

    V3* temp = new V3;
    temp->parent = NULL;
    temp->pos = A;
    std::vector<V3*> paths {temp};

    V3* parent;

    int number = 1;
    while (toSearch.size() != 0){
        Node current = toSearch.begin()->second;

        int i = current.pos.i, j = current.pos.j;

        toSearch.erase(toSearch.begin());
        parent = paths[current.number];
        labirintas[i][j] = 'W';

        if (i == B.i && j == B.j){
            std::string path = "";
            V3* now = parent;

            while (now->parent != NULL){
                int changed_i = now->pos.i - now->parent->pos.i;
                int changed_j = now->pos.j - now->parent->pos.j;

                if (changed_i != 0){
                    if (changed_i == 1){
                        path += 'D';
                    } else {
                        path += 'U';
                    }
                }
                if (changed_j != 0){
                    if (changed_j == 1){
                        path += 'R';
                    } else {
                        path += 'L';
                    }
                }

                now = now->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int k = 0; k < 4; k++){
            if ((0 <= i + dirs[k][0] && i + dirs[k][0] < n) && (0 <= j + dirs[k][1] && j + dirs[k][1] < m)){
                if (labirintas[i + dirs[k][0]][j + dirs[k][1]] != 'W' && labirintas[i + dirs[k][0]][j + dirs[k][1]] != '#'){
                    int G = current.G + 1;
                    int H = abs((i + dirs[k][0]) - B.i) + abs((j + dirs[k][1]) - B.j);

                    toSearch.insert({{G + H, H}, {G, H, G + H, {i + dirs[k][0], j + dirs[k][1]}, number}});

                    V3* t = new V3;
                    t->pos.i = i + dirs[k][0];
                    t->pos.j = j + dirs[k][1];
                    t->parent = parent;
                    paths.push_back(t);

                    number++;
                }
            }
        }
    }
    return "";
}

char** VecStr2CharDP(std::vector<std::string> maze){
    char** new_maze = new char*[maze.size()];
    for (int i = 0; i < maze.size(); i++){
        new_maze[i] = new char[maze[i].size()];
    }

    for (int i = 0; i < maze.size(); i++){
        for (int j = 0; j < maze[i].size(); j++){
            if (maze[i][j] == 'E'){
                maze[i][j] = 'A';
            } else if (maze[i][j] == 'P'){
                maze[i][j] = 'B';
            } else if (maze[i][j] == ' '){
                maze[i][j] = '.';
            }
            new_maze[i][j] = maze[i][j];
        }
    }

    return new_maze;
}

Texture2D* getEnemyImages(){
    const char* image_names[] = {"enemy-up.png", "enemy-right.png", "enemy-down.png", "enemy-left.png"};
    auto* images = new Texture2D[4];

    Image current_image;
    for (int i = 0; i < 4; i++){
        current_image = LoadImage(image_names[i]);
        images[i] = LoadTextureFromImage(current_image);
        UnloadImage(current_image);
    }

    return images;
}

V2 Vector2ToV2(Vector2 position){
    return {(int) position.y / 50, (int) position.x / 50};
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
