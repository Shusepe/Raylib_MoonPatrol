#pragma once

#include "vehicle.h"
#include "raylib.h"

namespace MoonPatrol {
	namespace Obstacles {
		
		struct Obstacle {
			Vector2 position;
			Vector2 size;
			float speed;
			Color color;
			Texture2D sprite;
		};

		Obstacle create();

		void draw(Obstacle obstacle);
		void update(Obstacle& obstacle);
		void init(Obstacle& obstacle, Vector2 position, Vector2 size, float speed);
	}
}