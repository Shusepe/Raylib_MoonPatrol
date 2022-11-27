#pragma once

namespace MoonPatrol {
	namespace Credits {
		enum class Options {
			ITCH1,
			ITCH2,
			RAYLIB,
			ASSETS,
			SOUNDFX,
			RETURN,
			COUNT
		};

		void update();
		void init();
	}
}