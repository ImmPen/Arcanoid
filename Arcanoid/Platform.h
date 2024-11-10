#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

namespace Arcanoid
{
	class Platform
	{
	public:
		void Init();
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

		bool CheckCollisionWithBall(const Ball& ball);

		sf::FloatRect GetRect() const { return sprite.getGlobalBounds(); }
	private:
		void Move(float speed);

		sf::Sprite sprite;
		sf::Texture texture;
	};
}
