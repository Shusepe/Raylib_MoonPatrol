#pragma once

namespace MoonPatrol {
	namespace MainMenu {
		enum class Options {
			ONEPLAYER,
			TWOPLAYERS,
			HOWTOPLAY,
			CREDITS,
			EXIT,
			COUNT
		};

		void update();
		void init();
	}
}