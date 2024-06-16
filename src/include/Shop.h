#pragma once

class Player;

enum Upgrade {
    HEALTH,
    SPEED,
    DAMAGE,
    GOLDMULTIPLIER,
    PROJECTILEDUPLICATION
};

class Shop {
    public:
        Shop();
    private:
        void upgrade(Upgrade upgrade);

        // Player reference
        Player* player;
};