#pragma once

#include "vehicle.h"

namespace MoonPatrol {
	namespace Game {
		
		void setPaused(bool value);
		void setScore(int value);

		float getFloorElevation(float xPos);
		float getTime();
		int getScore();
		void addScore(int value);

		void update();
		void drawHowToPlay();
		void init(bool enableTwoPlayers);
	}
}