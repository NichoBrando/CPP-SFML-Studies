#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <list>
#include "bullet.hpp"
#include "enemy.hpp"

using namespace sf;

int main()
{
	VideoMode vm(512, 256);
	RenderWindow window(vm, "Cpp Game Test", Style::Resize);
	window.setMouseCursorVisible(false);

	Texture bulletBackground;
	bulletBackground.loadFromFile("graphics/bullet.png");
	Sprite bulletSprite(bulletBackground, sf::IntRect(14, 0, 8, 8));

	Texture textureBackground;
	textureBackground.loadFromFile("graphics/map.png");
	Sprite spriteBackground(textureBackground);

	Texture playerTexture;
	playerTexture.loadFromFile("graphics/SquadLeader.png");
	Sprite playerSprite(playerTexture, sf::IntRect(0, 0, 16, 16));

	Texture mouseTexture;
	mouseTexture.loadFromFile("graphics/mouse-pointer.png");
	Sprite mouseSprite(mouseTexture);

	Player playerProps;

	Clock movementClock;
	
	sf::View view1(window.getDefaultView());

	std::list<Bullet> bullets;

	Texture enemyTexture;
	enemyTexture.loadFromFile("graphics/Hornet.png");

	std::list<Enemy> enemies;

	Clock spawnEnemiesClock;

	Clock shootCDClock;

	while (window.isOpen()) {
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if (spawnEnemiesClock.getElapsedTime().asSeconds() >= 1.f)
		{
			Enemy enemy;
			enemy.id = (int)enemies.size() + 1;
			enemy.sprite.setPosition(sf::Vector2f(0.f, 0.f));
			enemy.sprite.setTexture(enemyTexture);
			enemy.sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
			enemies.push_front(enemy);
			spawnEnemiesClock.restart();
		}

		sf::FloatRect playerRect = playerSprite.getGlobalBounds();

		for (auto bulletsIterable = bullets.begin(); bulletsIterable != bullets.end(); )
		{
			Bullet& bullet = *bulletsIterable;
			sf::FloatRect bulletRect = bullet.sprite.getGlobalBounds();
			bool hitEnemy = false;

			for (auto it = enemies.begin(); it != enemies.end(); ) {
				Enemy& enemy = *it;
				sf::FloatRect enemyRect = enemy.sprite.getGlobalBounds();

				if (bulletRect.intersects(enemyRect))
				{
					it = enemies.erase(it);
					hitEnemy = true;
				}
				else {
					++it;
				}
			}

			if (hitEnemy)
			{
				bulletsIterable = bullets.erase(bulletsIterable);
			}
			else 
			{
				++bulletsIterable;
			}
		}

		for (Enemy& enemy : enemies)
		{
			sf::FloatRect enemyRect = enemy.sprite.getGlobalBounds();

			if (playerRect.intersects(enemyRect))
			{
				window.close();
			}
		}

		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

		mouseSprite.setPosition(sf::Vector2f((float) mousePosition.x, (float) mousePosition.y));

		if (shootCDClock.getElapsedTime().asSeconds() >= 0.25f)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Bullet bullet;

				bullet.id = (int)bullets.size() + 1;
				sf::Vector2f playerPos = playerSprite.getPosition();

				float mouseY = (float)mousePosition.y;
				float mouseX = (float)mousePosition.x;

				bullet.velocityX = (mouseX - playerPos.x) / 5;
				bullet.velocityY = (mouseY - playerPos.y) / 5;

				if (bullet.velocityX != 0.f)
				{
					bullet.velocityX = bullet.velocityX * 3;
				}

				if (bullet.velocityY != 0.f)
				{
					bullet.velocityY = bullet.velocityY * 3;
				}

				std::cout << bullet.velocityX << " " << bullet.velocityY << "\n";

				bullet.sprite.setTexture(bulletBackground);
				bullet.sprite.setTextureRect(sf::IntRect(14, 0, 8, 8));
				bullet.sprite.setPosition(playerSprite.getPosition());
				bullets.push_front(bullet);
			}

			shootCDClock.restart();
		}

		if (movementClock.getElapsedTime().asMilliseconds() > 10.f)
		{
			sf::Vector2f playerMovement;
			if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::W))
			{
				playerMovement.y = (Keyboard::isKeyPressed(Keyboard::W) ? -1.f : 1.f) * 5 / 10;
			}

			if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D))
			{
				playerMovement.x = (Keyboard::isKeyPressed(Keyboard::A) ? -1.f : 1.f) * 5 / 10;
			}

			playerSprite.move(playerMovement);

			for (Bullet& bullet : bullets)
			{
				bullet.sprite.move(
					sf::Vector2f(
						bullet.velocityX / 10,
						bullet.velocityY / 10
					)
				);
			}

			sf::Vector2f playerPos = playerSprite.getPosition();
			for (Enemy& enemy : enemies)
			{
				enemy.move(playerPos);
			}

			movementClock.restart();
		}
		
		window.clear();

		window.setView(view1);
		window.draw(spriteBackground);
		window.draw(playerSprite);
		window.draw(mouseSprite);

		for (Bullet& bullet : bullets)
		{
			window.draw(bullet.sprite);
		}

		for (Enemy& enemy : enemies)
		{
			window.draw(enemy.sprite);
		}

		window.display();
		fflush(stdin);
	}

	return 0;
}