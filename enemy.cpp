// mynamespace.cpp
#include <iostream>
#include "enemy.hpp"

bool Enemy::operator == (const Enemy& other) const {
    return other.id == id;
}