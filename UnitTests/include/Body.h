#pragma once

#include "Utils.h"

class Body {
public:
    [[nodiscard]] bool touchedPlayer(V2 player) const;
    [[nodiscard]] bool shoot(V2 player) const;

    void setPosition(V2 pos);
    [[nodiscard]] V2 getPosition() const;
private:
    V2 position;
};
