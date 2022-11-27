#include "howToPlay.h"
#include "button.h"
#include "programManager.h"
#include "utils.h"

#include <iostream>

namespace MoonPatrol {
	namespace HowToPlay {

		// Private

		const int amountButtons = static_cast<int>(Options::COUNT);
		Buttons::Button buttons[amountButtons];
		int cursor;

		void resetHovering();
		void updateCursor();
		Color getButtonColor(Options option);
		float getButtonWidth(Options option);
		const char* getButtonName(Options option);
		void selectOption(Options option);
		void initButtons();
		void drawText();
		void draw();

		// --

		void resetHovering() {
			for (int i = 0; i < static_cast<int>(Options::COUNT); i++) {
				Buttons::hover(buttons[i], false);
			}
		}

		void updateCursor() {
			if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) cursor--;
			if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) cursor++;
			if (cursor < static_cast<int>(Options::HOWMOVEMENT)) cursor = static_cast<int>(Options::RETURN);
			if (cursor > static_cast<int>(Options::RETURN)) cursor = static_cast<int>(Options::HOWMOVEMENT);
			resetHovering();
			Buttons::hover(buttons[cursor], true);
		}

		Color getButtonColor(Options option) {
			switch (option)
			{
			case HowToPlay::Options::HOWMOVEMENT:
				return RED;
				break;
			case HowToPlay::Options::HOWSHOOT:
				return GREEN;
				break;
			default:
				return RAYWHITE;
				break;
			}
		}

		float getButtonWidth(Options option) {
			switch (option)
			{
			case HowToPlay::Options::RETURN:
				return static_cast<float>(GetScreenWidth() * .3);
				break;
			default:
				return static_cast<float>(GetScreenWidth() * .5);
				break;
			}
		}

		const char* getButtonName(Options option) {
			switch (option)
			{
			case HowToPlay::Options::HOWMOVEMENT:
				return "How i move";
				break;
			case HowToPlay::Options::HOWSHOOT:
				return "How i Shoot (Z)";
				break;
			case HowToPlay::Options::RETURN:
				return "Return to Menu";
				break;
			default:
				std::cout << "Invalid Option! [MainMenu.cpp - GetButtonname()]\n";
				return "Error";
				break;
			}
		}

		void selectOption(Options option) {
			switch (option)
			{
			case HowToPlay::Options::HOWMOVEMENT:
				OpenURL("https://mauvemau.itch.io");
				break;
			case HowToPlay::Options::HOWSHOOT:
				OpenURL("https://www.raylib.com");
				break;
			case HowToPlay::Options::RETURN:
				setProgramStatus(ProgramStatus::MAINMENU);
				break;
			default:
				std::cout << "Invalid Option! [MainMenu.cpp - SelectOption]\n";
				break;
			}
		}

		void initButtons() {
			float spacing = 0;
			for (int i = 0; i < amountButtons; i++) {
				if (i > 0)
					spacing += buttons[0].size.y + GetScreenHeight() * .03f;
				buttons[i] = Buttons::create(i,
					Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .24) + spacing },
					Vector2{ getButtonWidth((Options)i), static_cast<float>(GetScreenWidth() * .05) },
					getButtonColor((Options)i),
					getButtonName((Options)i));
			}
		}

		void drawText() {
			Utils::DrawCenteredText("Credits", { static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .1) },
				static_cast<int>(GetScreenHeight() * .1), RAYWHITE);
		}

		void draw() {
			BeginDrawing();
			ClearBackground(BLACK);

			for (int i = 0; i < amountButtons; i++) {
				Buttons::draw(buttons[i]);
			}

			drawText();

			EndDrawing();
		}

		// Public
		void update() {
			updateCursor();
			for (int i = 0; i < amountButtons; i++) {
				if (Buttons::update(buttons[i])) {
					selectOption((Options)buttons[i].id);
				}
			}

			if (IsKeyPressed(KEY_ESCAPE)) {
				setProgramStatus(ProgramStatus::MAINMENU);
			}

			draw();
		}

		void init() {
			initButtons();
			cursor = static_cast<int>(Options::HOWMOVEMENT);
		}
	}
}