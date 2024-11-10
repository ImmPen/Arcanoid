#pragma once
namespace Arcanoid
{
	const std::string RESOURCES_PATH = "./Resourses/";
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	const std::string GAME_NAME = "Arcanoid";
	const float PLATFORM_SPEED = 150;
	const float BALL_SPEED = 250;
	const int PAUSE_DELAY = 3; //in seconds
	const int NUM_RECORDS_IN_TABLE = 5;
	const float TIME_PER_FRAME = 1.f / 60.f;

	const int PLATFORM_WIDTH = 48;
	const int PLATFORM_HEIGHT = 14;
	const int BALL_SIZE = 12;

	const sf::IntRect PLATFORM_RECT_IN_TEXTURE = sf::IntRect(32, 64, PLATFORM_WIDTH, PLATFORM_HEIGHT);
	const sf::IntRect BALL_RECT_IN_TEXTURE = sf::IntRect(50, 34, BALL_SIZE, BALL_SIZE);
}