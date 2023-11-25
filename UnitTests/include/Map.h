#pragma once

#include "Constants.h"
#include "Utils.h"

class Map {
public:
    Map();

    [[nodiscard]] bool isOutOfMapPlayer(V2 player) const;
private:
    int width, height;
    int block_size;
};
