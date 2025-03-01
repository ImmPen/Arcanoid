#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameStateData.h"
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include "BlockFactory.h"
#include "Level.h"
#include "IObserver.h"
#include <memory>

namespace Arcanoid
{
	class GameStatePlayingData : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlayingData>
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;
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
		std::unordered_map<BlockType, std::unique_ptr<BlockFactory>> factories;
		LevelLoader levelLoader;
		int currentLevel;

		//UI data
		sf::Text scoreText;
	};
}
