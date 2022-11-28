#include "vehicle.h"

#include "game.h"
#include "collisionManager.h"
#include "utils.h"

#include <iostream>

using namespace std;

namespace MoonPatrol {
	namespace Vehicles {

		// Private

		bool floored;

		void InitVehicleWeapons(Weapons::Weapon weapons[]);

		// --

		void InitVehicleWeapons(Weapons::Weapon weapons[]) {
			for (int i = 0; i < amountWeapons; i++) {
				weapons[i] = Weapons::create();
			}
		}

		// Public

		Vehicle create() {
			Vehicle vehicle;
			vehicle.position = { 0, 0 };
			vehicle.size = { 0, 0 };
			vehicle.verticalAcceleration = 0;
			vehicle.speed = 0;
			vehicle.gravity = 0;
			vehicle.jumpForce = 0;
			vehicle.heigth = 0;
			vehicle.color = RAYWHITE;
			InitVehicleWeapons(vehicle.weapons);
			return vehicle;
		}

		void setColor(Vehicle& vehicle, Color color) {
			vehicle.color = color;
		}

		void shoot(Vehicle& vehicle) {
			for (int i = 0; i < amountWeapons; i++) {
				Weapons::shoot(vehicle.weapons[i], { vehicle.position.x + (vehicle.size.x * .5f) , vehicle.position.y + (vehicle.size.y * .5f) }, Utils::DegreesToRadians(-90.0f));
			}
		}

		void jump(Vehicle& vehicle) {
			if (floored) {
				floored = false;
				vehicle.verticalAcceleration = -vehicle.jumpForce;
			}
		}

		void move(Vehicle& vehicle, int direction) {
			vehicle.position.x += direction * (vehicle.speed * GetFrameTime());
			if(Collisions::vehicleWall(vehicle)) {
				if (vehicle.position.x < (GetScreenWidth() * .5f)) {
					vehicle.position.x = 0;
				}
				else {
					vehicle.position.x = static_cast<float>(GetScreenWidth() - vehicle.size.x);
				}
			}
		}

		void draw(Vehicle vehicle) {
			DrawTexture(vehicle.sprite, static_cast<int>(vehicle.position.x), static_cast<int>(vehicle.position.y), vehicle.color);
		}

		void update(Vehicle& vehicle) {
			float floorElevation = Game::getFloorElevation(vehicle.position.x + (vehicle.size.x * .001f));

			if (vehicle.position.y + vehicle.size.y + vehicle.heigth < floorElevation) {
				vehicle.verticalAcceleration += vehicle.gravity * GetFrameTime();
			}
			if (vehicle.position.y + vehicle.size.y >= floorElevation) {
				if (vehicle.verticalAcceleration > 0) { 
					vehicle.verticalAcceleration = 0;
					floored = true;
				}
				vehicle.position.y = floorElevation - vehicle.size.y - vehicle.heigth;
			}

			vehicle.position.y += vehicle.verticalAcceleration * GetFrameTime();
		}

		void init(Vehicle& player, Vector2 position, Vector2 size, float speed, float gravity, float jumpForce, float height, char* texture) {
			player = create();
			player.position = position;
			player.size = size;
			player.position.y -= size.y;
			player.speed = speed;
			player.gravity = gravity;
			player.jumpForce = jumpForce;
			player.heigth = height;
			player.sprite = LoadTexture(texture);
			player.color = WHITE;
			player.weapons[0] = Weapons::createWeaponFromTemplate(Weapons::Types::GUN);

			floored = false;
		}
	}
}