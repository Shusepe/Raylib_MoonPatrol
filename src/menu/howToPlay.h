#pragma once

namespace MoonPatrol {
	namespace HowToPlay {
		enum class Options {
			HOWMOVEMENT,
			HOWSHOOT,
			RETURN,
			COUNT
		};

		void update();
		void init();
	}
}