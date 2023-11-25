#include "gtest/gtest.h"
#include "include/Body.h"
#include "include/Map.h"

class PlayerEnemyFixture : public ::testing::Test {
protected:
    void SetUp() override {
        player = new Body;
        enemy = new Body;
    }

    void TearDown() override {
        delete player;
        delete enemy;
    }

    Body* player;
    Body* enemy;
};

TEST_F(PlayerEnemyFixture, PlayerEnemyCollision){
    player->setPosition({50, 50});
    enemy->setPosition({70, 70});

    bool collided = enemy->touchedPlayer(player->getPosition());

    ASSERT_EQ(collided, true);
}

TEST_F(PlayerEnemyFixture, EnemyShootsPlayerToLeft){
    player->setPosition({50, 50});
    enemy->setPosition({240, 60});

    bool enemy_will_shoot = enemy->shoot(player->getPosition());

    ASSERT_EQ(enemy_will_shoot, true);
}

TEST_F(PlayerEnemyFixture, EnemyShootsPlayerToRight){
    player->setPosition({540, 50});
    enemy->setPosition({100, 65});

    bool enemy_will_shoot = enemy->shoot(player->getPosition());

    ASSERT_EQ(enemy_will_shoot, true);
}

TEST_F(PlayerEnemyFixture, EnemyShootsPlayerToUp){
    player->setPosition({50, 100});
    enemy->setPosition({70, 450});

    bool enemy_will_shoot = enemy->shoot(player->getPosition());

    ASSERT_EQ(enemy_will_shoot, true);
}

TEST_F(PlayerEnemyFixture, EnemyShootsPlayerToDown){
    player->setPosition({100, 840});
    enemy->setPosition({80, 340});

    bool enemy_will_shoot = enemy->shoot(player->getPosition());

    ASSERT_EQ(enemy_will_shoot, true);
}


class PlayerMapFixture : public ::testing::Test {
protected:
    void SetUp() override {
        player = new Body;
        map = new Map;
    }

    void TearDown() override {
        delete player;
        delete map;
    }

    Map* map;
    Body* player;
};

TEST_F(PlayerMapFixture, PlayerIsOutOfMap){
    player->setPosition({2000, 100});

    bool is_out_of_map = map->isOutOfMapPlayer(player->getPosition());

    ASSERT_EQ(is_out_of_map, true);
}
