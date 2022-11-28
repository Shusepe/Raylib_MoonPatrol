#include "enemy.h"

#include "collisionManager.h"
#include "utils.h"

#include <iostream>

namespace MoonPatrol {
	namespace Enemies {

		// Private

		static char enemyImg[] = "res/enemy.png";
		const int amplitude = 50;

		// --

		// Public

		Enemy create() {
			Enemy enemy;
			enemy.position = { 0, 0 };
			enemy.yCenter = 0;
			enemy.lives = 0;
			enemy.hitRadius = 0;
			enemy.speed = 0;
			enemy.direction = 0;
			enemy.color = RAYWHITE;
			enemy.weapon = Weapons::create();
			return enemy;
		}

		void draw(Enemy enemy) {
			DrawTexture(enemy.sprite, static_cast<int>(enemy.position.x - enemy.hitRadius), static_cast<int>(enemy.position.y - enemy.hitRadius), enemy.color);
		}

		void update(Enemy& enemy) {
			enemy.position.x += (enemy.speed * GetFrameTime()) * enemy.direction;
			// position.y = (amplitude * sin(position.x * speed.y * PI)) + center;
			enemy.position.y = (amplitude * sinf(enemy.position.x * .01f * static_cast<float>(Utils::m_pi))) + enemy.yCenter;
			if (Collisions::enemyWall(enemy)) {
				if (enemy.position.x < GetScreenWidth() * .5f) {
					enemy.position.x = static_cast<float>(GetScreenWidth());
				}
				else {
					enemy.position.x = 0;
				}
			}
		}

		void init(Enemy& enemy, float yCenter, int lives, float hitRadius, float speed, int direction, Weapons::Weapon weapon) {
			enemy = create();
			enemy.yCenter = yCenter;
			enemy.lives = lives;
			enemy.hitRadius = hitRadius;
			enemy.speed = speed;
			enemy.direction = direction;
			enemy.weapon = weapon;
			enemy.sprite = LoadTexture(enemyImg);
		}
	}
}