#pragma once
#include <SFML/Graphics.hpp>

namespace Arcanoid
{
	class GameWorld
	{
	private:
		GameWorld() = default;
	public:
		static GameWorld& Instance()
		{
			static GameWorld instance;
			return instance;
		}

		const std::string RESOURCES_PATH = "./Resourses/";
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 600;
		const std::string GAME_NAME = "Arcanoid";
		const float PLATFORM_SPEED = 150;
		const float BALL_SPEED = 250;
		const int PAUSE_DELAY = 3; //in seconds
		const int NUM_RECORDS_IN_TABLE = 5;
		const float TIME_PER_FRAME = 1.f / 60.f;

		const int BLOCK_WIDTH_ON_TILESET = 32;
		const int BLOCK_HEIGHT_ON_TILESET = 16;
		const int NUM_BLOCK_IN_ROW = 10;
		const int NUM_COLORS = 6;

		const int BLOCK_WIDTH = SCREEN_WIDTH / NUM_BLOCK_IN_ROW;
		const int SCALE = BLOCK_WIDTH / BLOCK_WIDTH_ON_TILESET;
		const int BLOCK_HEIGHT = BLOCK_HEIGHT_ON_TILESET * SCALE;
		const int PLATFORM_WIDTH = 48 * SCALE;
		const int PLATFORM_HEIGHT = 14 * SCALE;
		const int BALL_SIZE = 12 * SCALE;

		const float BREAK_TIME = 1.f;
		const int BREAK_FRAMES_COUNT = 12;
		const float TIME_ON_FRAME = BREAK_TIME / (float)BREAK_FRAMES_COUNT;

		const int MAX_DURABILITY = 3;

		const sf::IntRect PLATFORM_RECT_IN_TEXTURE = sf::IntRect(32, 64, 48, 14);
		const sf::IntRect BALL_RECT_IN_TEXTURE = sf::IntRect(50, 34, 12, 12);
		const sf::IntRect BLOCK_RECT_IN_TEXTURE = sf::IntRect(32, 176, 32, 16);
	};
}

#define SETTINGS GameWorld::Instance()