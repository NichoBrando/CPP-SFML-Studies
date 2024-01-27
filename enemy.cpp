// mynamespace.cpp
#include <iostream>
#include "enemy.hpp"
#include <SFML/Graphics.hpp>

bool Enemy::operator == (const Enemy& other) const 
{
    return other.id == id;
}

void Enemy::move (sf::Vector2f& playerPos)
{
	sf::Vector2f enemyPos = sprite.getPosition();
	sf::Vector2f distance = sf::Vector2f(
		playerPos.x - enemyPos.x,
		playerPos.y - enemyPos.y
	);

	if (distance.x > 5 || distance.x < -5.f)
	{
		int factor = abs(distance.x) / distance.x;
		distance.x = 5.f * factor;
	}

	if (distance.y > 5 || distance.y < -5.f)
	{
		int factor = abs(distance.y) / distance.y;
		distance.y = 5.f * factor;
		distance.y = 5.f;
	}

	distance.x /= 10;
	distance.y /= 10;

	sprite.move(distance);
}