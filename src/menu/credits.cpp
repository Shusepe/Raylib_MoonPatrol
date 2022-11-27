#include "credits.h"
#include "button.h"
#include "programManager.h"
#include "utils.h"

#include <iostream>

namespace MoonPatrol {
	namespace Credits {
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

		void resetHovering() {
			for (int i = 0; i < static_cast<int>(Options::COUNT); i++) {
				Buttons::hover(buttons[i], false);
			}
		}

		void updateCursor() {
			if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) cursor--;
			if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) cursor++;
			if (cursor < static_cast<int>(Options::ITCH1)) cursor = static_cast<int>(Options::RETURN);
			if (cursor == static_cast<int>(Options::ITCH1)) cursor = static_cast<int>(Options::ITCH1);
			if (cursor == static_cast<int>(Options::ITCH2)) cursor = static_cast<int>(Options::ITCH2);
			if (cursor == static_cast<int>(Options::ASSETS)) cursor = static_cast<int>(Options::ASSETS);
			if (cursor == static_cast<int>(Options::SOUNDFX)) cursor = static_cast<int>(Options::SOUNDFX);
			if (cursor == static_cast<int>(Options::RETURN)) cursor = static_cast<int>(Options::RETURN);
			if (cursor > static_cast<int>(Options::RETURN)) cursor = static_cast<int>(Options::ITCH1);
			resetHovering();
			Buttons::hover(buttons[cursor], true);
		}

		Color getButtonColor(Options option) {
			switch (option)
			{
			case Credits::Options::ITCH1:
				return RED;
				break;
			case Credits::Options::ITCH2:
				return RED;
				break;
			case Credits::Options::RETURN:
				return RAYWHITE;
				break;
			default:
				return GREEN;
				break;
			}
		}

		float getButtonWidth(Options option) {
			switch (option)
			{
			case Credits::Options::RETURN:
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
			case Credits::Options::ITCH1:
				return "Visit Mau Itch.io!";
				break;
			case Credits::Options::ITCH2:
				return "Visit Jose Itch.io!";
				break;
			case Credits::Options::RAYLIB:
				return "Visit Raylib";
				break;
			case Credits::Options::ASSETS:
				return "View Assets";
				break;
			case Credits::Options::SOUNDFX:
				return "Check Sound FX";
				break;
			case Credits::Options::RETURN:
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
			case Credits::Options::ITCH1:
				OpenURL("https://mauvemau.itch.io");
				break;
			case Credits::Options::ITCH2:
				OpenURL("https://jose-altamirano.itch.io/");
				break;
			case Credits::Options::RAYLIB:
				OpenURL("https://www.raylib.com");
				break;
			case Credits::Options::ASSETS:
				OpenURL("https://www.flaticon.es/icono-gratis/rover-lunar_4698850");
				OpenURL("https://opengameart.org/content/spaceship-2");
				OpenURL("https://opengameart.org/content/space-stuff");
				break;
			case Credits::Options::SOUNDFX:
				OpenURL("https://opengameart.org/content/space-shoot-sounds");
				OpenURL("https://opengameart.org/content/space-fast-synth-epic-themes");
				break;
			case Credits::Options::RETURN:
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
					Vector2{ static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .3) + spacing },
					Vector2{ getButtonWidth((Options)i), static_cast<float>(GetScreenWidth() * .05) },
					getButtonColor((Options)i),
					getButtonName((Options)i));
			}
		}

		void drawText() {
			Utils::DrawCenteredText("Credits", {static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .1)}, 
				static_cast<int>(GetScreenHeight() * .1), RAYWHITE);
			
			Utils::DrawCenteredText("Game made with Raylib, by Mau & Jose", {static_cast<float>(GetScreenWidth() * .5), static_cast<float>(GetScreenHeight() * .2)}, 
				static_cast<int>(GetScreenHeight() * .05), RAYWHITE);
			
			Utils::DrawCenteredText("v0.4", {static_cast<float>(GetScreenWidth() * .1), static_cast<float>(GetScreenHeight() * .05)}, 
				static_cast<int>(GetScreenHeight() * .05), RAYWHITE);
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
			cursor = static_cast<int>(Options::ITCH1);
			cursor = static_cast<int>(Options::ITCH2);
		}
	}
}