#include "../include/Body.h"

void Body::draw() const {
    DrawTexture(getTexture(), (int) position.x, (int) position.y, tint);
    for (const Bullet& bullet : bullets){
        bullet.draw();
    }
}

Texture2D Body::getTexture() const {
    if (last_move == 'W'){
        return images[0];
    } else if (last_move == 'D'){
        return images[1];
    } else if (last_move == 'S'){
        return images[2];
    }
    return images[3];
}

void Body::loadImages(const std::vector<std::string>& image_paths) {
    Image current_image;
    for (int i = 0; i < 4; i++){
        current_image = LoadImage(image_paths[i].c_str());
        images[i] = LoadTextureFromImage(current_image);
        UnloadImage(current_image);
    }
}

bool Body::gotHit(Vector2 bullet_end_pos) const {
    return (position.x < bullet_end_pos.x && bullet_end_pos.x < position.x + 50) && (position.y < bullet_end_pos.y && bullet_end_pos.y < position.y + 50);
}

void Body::updateBullets(){
    std::vector<int> indexes;
    for (int i = 0; i < bullets.size(); i++){
        if (bullets[i].getDestruction()){
            indexes.push_back(i);
        } else {
            bullets[i].update();
        }
    }

    for (int index : indexes){
        bullets.erase(bullets.begin() + index);
    }
}

std::vector<Bullet>* Body::getBullets() {
    return &bullets;
}
