#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"

namespace Arcanoid
{
	class GameStatePauseData
	{
	public:
		void Init();
		void HandleWindowEvent(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
	private:
		sf::Font font;

		sf::RectangleShape background;

		Menu menu;

		bool isGameResume = false;
		int timer = 0;
	};
}
