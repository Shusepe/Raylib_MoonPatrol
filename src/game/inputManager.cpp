#include "inputManager.h"
#include "programManager.h"

#include <iostream>

using namespace std;

namespace MoonPatrol {
	namespace Input {
		void update(Vehicles::Vehicle& vehicle1, Vehicles::Vehicle& vehicle2, bool twoPlayers) {
			//Player 1
			if ((IsKeyDown(KEY_LEFT))) {
				Vehicles::move(vehicle1, -1);
			}
			else if ((IsKeyDown(KEY_RIGHT))) {
				Vehicles::move(vehicle1, +1);
			}
			if ((IsKeyPressed(KEY_UP))) {
				Vehicles::jump(vehicle1);
			}
			if ((IsKeyDown(KEY_SPACE))) {
				Vehicles::shoot(vehicle1);
			}
			// Player 2
			if (IsKeyDown(KEY_A) && twoPlayers) {
				Vehicles::move(vehicle2, -1);
			}
			else if (IsKeyDown(KEY_D) && twoPlayers) {
				Vehicles::move(vehicle2, +1);
			}
			if (IsKeyPressed(KEY_W) && twoPlayers) {
				Vehicles::jump(vehicle2);
			}
			if (IsKeyDown(KEY_ENTER) && twoPlayers) {
				Vehicles::shoot(vehicle2);
			}
			//
			if (IsKeyPressed(KEY_ESCAPE)) {
				setProgramStatus(ProgramStatus::MAINMENU);
			}
		}
	}
}