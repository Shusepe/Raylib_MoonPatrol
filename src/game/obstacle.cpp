#include "obstacle.h"
#include "game.h"

namespace MoonPatrol {
	namespace Obstacles {

		// Private

		static char obstacleImg[] = "res/obstacle.png";

		void move(Obstacle& obstacle, int direction);

		// --

		void move(Obstacle& obstacle, int direction) {
			obstacle.position.x += direction * (obstacle.speed * GetFrameTime());
		}

		// Public

		Obstacle create() {
			Obstacle obstacle;
			obstacle.position = { 0, 0 };
			obstacle.size = { 0, 0 };
			obstacle.speed = 0;
			obstacle.color = RAYWHITE;
			return obstacle;
		}

		void draw(Obstacle obstacle) {
			DrawTexture(obstacle.sprite, static_cast<int>(obstacle.position.x), static_cast<int>(obstacle.position.y), obstacle.color);
		}

		void update(Obstacle& obstacle) {
			move(obstacle, -1);
			if (obstacle.position.x < (-obstacle.size.x)) {
				obstacle.position.x = static_cast<float>((GetScreenWidth() * 1) + obstacle.size.x);
				Game::addScore(5);
			}
			if (obstacle.position.y + obstacle.size.y < Game::getFloorElevation(obstacle.position.x + (obstacle.size.x * .5f)) ||
				obstacle.position.y + obstacle.size.y > Game::getFloorElevation(obstacle.position.x + (obstacle.size.x * .5f))) {
				obstacle.position.y = Game::getFloorElevation(obstacle.position.x + (obstacle.size.x * .5f)) - obstacle.size.y;
			}
		}

		void init(Obstacle& obstacle, Vector2 position, Vector2 size, float speed) {
			obstacle = create();
			obstacle.size = size;
			obstacle.position = position;
			obstacle.position.y -= size.y;
			obstacle.speed = speed;
			obstacle.sprite = LoadTexture(obstacleImg);
		}
	}
}