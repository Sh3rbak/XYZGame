#pragma once
#include <string>

namespace ArkanoidGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	// Game settings constants
	const float SPEED_PLATFORM = 200.f;
	const unsigned int PLATFORM_WIDTH = 50;
	const unsigned int PLATFORM_HEGHT = 8;
	const unsigned int BALL_SIZE = 20;
	const unsigned int BALL_SPEED = 200;
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEGHT = 600;
	const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME; // We need to define this constant in some CPP

	const std::string GAME_NAME = "ArkanoidGame";
}
