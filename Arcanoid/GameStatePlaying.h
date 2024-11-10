#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Platform.h"
#include "Ball.h"

namespace Arcanoid
{
	class GameStatePlayingData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
	private:
		//Resources
		sf::Font font;

		//Game data
		Platform platform;
		Ball ball;

		//UI data
		sf::Text scoreText;
	};
}
