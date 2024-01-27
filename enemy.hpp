// mynamespace.h
#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>

class Enemy {
    public:
        sf::Sprite sprite;
        int id = 0;
        bool operator == (const Enemy& other) const;
        void move(sf::Vector2f& playerPos);
};

#endif // ENEMY_H