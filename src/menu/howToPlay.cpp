#include "howToPlay.h"
#include "button.h"
#include "programManager.h"
#include "utils.h"

#include <iostream>

namespace MoonPatrol {
	namespace HowToPlay {

		// Private
		Buttons::Button button;

		void drawText();
		void draw();

		void drawText() {
			
			Utils::DrawCenteredText(
				"Player 1", 
				{ static_cast<float>(GetScreenWidth() * .35), static_cast<float>(GetScreenHeight() * .2) },
				static_cast<int>(GetScreenHeight() * .075), 
				RAYWHITE);
			Utils::DrawCenteredText(
				"Player 2", 
				{ static_cast<float>(GetScreenWidth() * .7), static_cast<float>(GetScreenHeight() * .2) },
				static_cast<int>(GetScreenHeight() * .075), 
				RAYWHITE);
			

			Utils::DrawCenteredText(
				"move left", 
				{ static_cast<float>(GetScreenWidth() * .15), static_cast<float>(GetScreenHeight() * .4) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);

			Utils::DrawCenteredText(
				"move right", 
				{ static_cast<float>(GetScreenWidth() * .15), static_cast<float>(GetScreenHeight() * .5) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);

			Utils::DrawCenteredText(
				"jump", 
				{ static_cast<float>(GetScreenWidth() * .15), static_cast<float>(GetScreenHeight() * .6) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);
					
			Utils::DrawCenteredText(
				"shoot", 
				{ static_cast<float>(GetScreenWidth() * .15), static_cast<float>(GetScreenHeight() * .7) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);


			Utils::DrawCenteredText(
				"A", 
				{ static_cast<float>(GetScreenWidth() * .35), static_cast<float>(GetScreenHeight() * .4) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);
			Utils::DrawCenteredText(
				"LEFT", 
				{ static_cast<float>(GetScreenWidth() * .7), static_cast<float>(GetScreenHeight() * .4) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);

			Utils::DrawCenteredText(
				"D", 
				{ static_cast<float>(GetScreenWidth() * .35), static_cast<float>(GetScreenHeight() * .5) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);
			Utils::DrawCenteredText(
				"RIGHT", 
				{ static_cast<float>(GetScreenWidth() * .7), static_cast<float>(GetScreenHeight() * .5) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);

			Utils::DrawCenteredText(
				"W", 
				{ static_cast<float>(GetScreenWidth() * .35), static_cast<float>(GetScreenHeight() * .6) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);
			Utils::DrawCenteredText(
				"UP", 
				{ static_cast<float>(GetScreenWidth() * .7), static_cast<float>(GetScreenHeight() * .6) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);

			Utils::DrawCenteredText(
				"SPACE", 
				{ static_cast<float>(GetScreenWidth() * .35), static_cast<float>(GetScreenHeight() * .7) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);
			Utils::DrawCenteredText(
				"ENTER", 
				{ static_cast<float>(GetScreenWidth() * .7), static_cast<float>(GetScreenHeight() * .7) },
				static_cast<int>(GetScreenHeight() * .05), 
				RAYWHITE);
		}

		void draw() {
			BeginDrawing();
			ClearBackground(BLACK);

			Buttons::draw(button);
			
			drawText();

			EndDrawing();
		}

		// Public
		void update() {
			if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) {
				setProgramStatus(ProgramStatus::MAINMENU);
			}
			draw();
		}

		void init() {
			button = Buttons::create(1,
				Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .85) },
				Vector2{ static_cast<float>(GetScreenWidth() * .3), static_cast<float>(GetScreenWidth() * .05) },
				RAYWHITE,
				"Press ENTER to return");
		}
	}
}