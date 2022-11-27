#pragma once
/*
Maneja los loops y distintas pantallas del juego.
*/

namespace MoonPatrol {
	enum class ProgramStatus {
		ONEPLAYERGAME,
		TWOPLAYERGAME,
		HOWIPLAY,
		MAINMENU,
		CREDITS
	};

	const char* getProgramVersion();

	void setGameShouldClose(bool value);
	void setProgramStatus(ProgramStatus status);
	void startProgram();
}