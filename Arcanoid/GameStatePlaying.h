#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateData.h"
#include "Platform.h"
#include "Ball.h"
#include "Block.h"

namespace Arcanoid
{
	class GameStatePlayingData : public GameStateData
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
	private:
		void CreateBlocks();
		bool IsWinCondition();
		void GetBallInverse(
			const sf::Vector2f& ballPosition,
			const sf::FloatRect& blockRect,
			bool& isNeedInverseDirectionX,
			bool& isNeedInverseDirectionY);
		//Resources
		sf::Font font;

		//Game data
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Block>> blocks;

		//UI data
		sf::Text scoreText;
	};
}
