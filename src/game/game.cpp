#include "game.h"

#include "programManager.h"
#include "inputManager.h"
#include "collisionManager.h"
#include "objectManager.h"
#include "utils.h"

// Objects
#include "terrain.h"
#include "vehicle.h"
#include "obstacle.h"
#include "enemy.h"

#include <iostream>
#include <chrono>

using namespace std;

static char vehicleImg[] = "res/roverLunarP1.png";
static char vehicleImg2[] = "res/roverLunarP2.png";

namespace MoonPatrol {
	namespace Game {

		// Private

		Vehicles::Vehicle player;
		Vehicles::Vehicle player2;
		Obstacles::Obstacle obstacle;

		Terrains::Terrain floor;
		Terrains::Terrain mountainsNear;
		Terrains::Terrain mountainsBack;

		chrono::steady_clock::time_point startTime;

		int score;

		bool paused;
		bool twoPlayers = false;

		chrono::steady_clock::time_point pauseStartTime; // En caso del juego estar pausado por determinado tiempo, se lo sumamos al startTime.

		int enemySoftCap;

		void handleGameLogic();
		void draw();

		// --

		void handleGameLogic() {
			if (ObjectManager::getActiveEnemies() < enemySoftCap) {
				int direction = -1;
				int aux = GetRandomValue(0, 1);
				if (aux) {
					direction = abs(direction);
				}
				float altitude;
				int altitudeMultiplier = GetRandomValue(20, 40);
				altitude = altitudeMultiplier * .01f;
				float speed = static_cast<float>(GetRandomValue(100, 200));

				ObjectManager::addEnemy(GetScreenHeight() * altitude, GetScreenHeight() * .045f, speed, direction);
			}
		}

		void draw() {
			BeginDrawing();
			ClearBackground({ 30, 15, 55, 255 });

			Terrains::draw(mountainsBack);
			Terrains::draw(mountainsNear);
			Terrains::draw(floor);

			Vehicles::draw(player);

			if (twoPlayers)
			{
				Vehicles::draw(player2);
			}

			Obstacles::draw(obstacle);

			ObjectManager::draw();

			DrawText(TextFormat("Version: %s", getProgramVersion()),
				static_cast<int>(GetScreenHeight() * .01f), 
				static_cast<int>(GetScreenHeight() * .01f), 
				static_cast<int>(GetScreenHeight() * .04f), 
				RAYWHITE);

			DrawText(TextFormat("Score: %i", score),
				static_cast<int>(GetScreenHeight() * .01f),
				static_cast<int>(GetScreenHeight() * .045f),
				static_cast<int>(GetScreenHeight() * .05f),
				RAYWHITE);

			DrawText("Press [ESC] key to return to the menu",
				static_cast<int>(GetScreenHeight() * .01f),
				static_cast<int>(GetScreenHeight() * .96f),
				static_cast<int>(GetScreenHeight() * .035f),
				RAYWHITE);

			if (paused) {
				DrawText("Game Over",
					static_cast<int>(GetScreenWidth() * .05f),
					static_cast<int>(GetScreenHeight() * .4f),
					static_cast<int>(GetScreenHeight() * .08f),
					RED);
				DrawText("Press [R] key to restart",
					static_cast<int>(GetScreenWidth() * .05f),
					static_cast<int>(GetScreenHeight() * .5f),
					static_cast<int>(GetScreenHeight() * .035f),
					RAYWHITE);
				DrawText(TextFormat("Your Score: %i", score),
						static_cast<int>(GetScreenWidth() * .05f),
						static_cast<int>(GetScreenHeight() * .55f),
						static_cast<int>(GetScreenHeight() * .04f),
						RAYWHITE);
			}

			EndDrawing();
		}

		// Public

		void setPaused(bool value) {
			paused = value;
		}

		void setScore(int value) {
			score = value;
		}

		float getFloorElevation(float xPos) {
			return Terrains::elevation(floor, xPos);
		}

		float getTime() {
			float curTime = (static_cast<int>(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTime).count())) * .001f;
			return curTime;
		}

		int getScore() {
			return score;
		}

		void addScore(int value) {
			score += value;
		}

		void update() {
			if (!paused) {
				Input::update(player, player2, twoPlayers);

				Vehicles::update(player);

				if(twoPlayers){
					Vehicles::update(player2);
				}

				ObjectManager::update(twoPlayers);

				Obstacles::update(obstacle);

				handleGameLogic();

				Terrains::update(floor);
				Terrains::update(mountainsNear);
				Terrains::update(mountainsBack);

				if (Collisions::vehicleObstacle(player, obstacle) || ObjectManager::hasEnemyCollisioned(player))
				{
					Vehicles::setColor(player, ORANGE);
					setPaused(true);
				}
				else if ((Collisions::vehicleObstacle(player2, obstacle) || ObjectManager::hasEnemyCollisioned(player2)) && twoPlayers) 
				{
					Vehicles::setColor(player2, ORANGE);
					setPaused(true);
				}
				else
				{
					Vehicles::setColor(player, WHITE);
					Vehicles::setColor(player2, WHITE);
				}
			}

			if (paused) {
				if (IsKeyPressed(KEY_R)) {
					ProgramStatus resetStatus = ProgramStatus::ONEPLAYERGAME;
					
					if(twoPlayers) {
						resetStatus = ProgramStatus::TWOPLAYERGAME;
					}

					setProgramStatus(resetStatus);
				}
			}

			draw();
		}

		void init(bool enableTwoPlayers) {
			startTime = chrono::steady_clock::now();
			twoPlayers = enableTwoPlayers;

			Terrains::init(floor, GetScreenWidth() * .1f, GetScreenHeight() * .85f, GetScreenHeight() * .75f, 300.0f, { 230, 180, 80, 255 });
			Terrains::init(mountainsNear, GetScreenWidth() * .2f, GetScreenHeight() * .7f, GetScreenHeight() * .5f, 100.0f, { 145, 120, 50, 255 });
			Terrains::init(mountainsBack, GetScreenWidth() * .3f, GetScreenHeight() * .7f, GetScreenHeight() * .4f, 50.0f, { 40, 30, 15, 255 });

			Vehicles::init(player,
						  { static_cast<float>(GetScreenWidth() * .5f), getFloorElevation(static_cast<float>(GetScreenWidth() * .2f)) },
						  { static_cast<float>(GetScreenHeight() * .2f), static_cast<float>(GetScreenHeight() * .18f) },
						   400.0f, 400.0f, 400.0f, 0, vehicleImg);

			if (twoPlayers)
			{
				Vehicles::init(player2,
					{ static_cast<float>(GetScreenWidth() * .2f), getFloorElevation(static_cast<float>(GetScreenWidth() * .2f)) },
					{ static_cast<float>(GetScreenHeight() * .2f), static_cast<float>(GetScreenHeight() * .18f) },
					400.0f, 400.0f, 400.0f, 0, vehicleImg2);
			}

			Obstacles::init(obstacle, 
				{ static_cast<float>((GetScreenWidth() * 1) + obstacle.size.x) , getFloorElevation(static_cast<float>((GetScreenWidth() * 1) + (obstacle.size.x * 1.5f))) },
				{ static_cast<float>(GetScreenHeight() * .08f), static_cast<float>(GetScreenHeight() * .1f) },
				300.0f);

			ObjectManager::init();

			paused = false;
			pauseStartTime = chrono::steady_clock::now();

			enemySoftCap = 2;

			score = 0;
		}
	}
}