// mynamespace.h
#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Bullet { 
    public:
        float velocityX = 0;
        float velocityY = 0;
        sf::Sprite sprite;
        int id = 0;
        bool operator == (const Bullet& other) const;
};


#endif // BULLET_H