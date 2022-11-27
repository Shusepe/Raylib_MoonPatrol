#pragma once

#include "vehicle.h"
#include "raylib.h"

namespace MoonPatrol {
	namespace Obstacles {
		
		struct Obstacle {
			Vector2 position;
			Vector2 size;
			float speed;
		};

		Obstacle create();

		void draw(Obstacle obstacle);
		void update(Obstacle& obstacle);
		bool wasAvoided(Obstacle obstacle, Vehicles::Vehicle player);
		void init(Obstacle& obstacle, Vector2 position, Vector2 size, float speed);
	}
}