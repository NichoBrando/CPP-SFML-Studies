// mynamespace.cpp
#include <iostream>
#include "bullet.hpp"

bool Bullet::operator == (const Bullet& other) const {
    return other.id == id;
}