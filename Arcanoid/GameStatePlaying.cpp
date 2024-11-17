#include "GameStatePlaying.h"
#include <assert.h>
#include "Game.h"
#include "GameSettings.h"
#include "Application.h"

namespace Arcanoid
{
	void GameStatePlayingData::Init()
	{
		assert(this->font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));
		gameObjects.emplace_back(std::make_shared<Platform>(sf::Vector2f({ SCREEN_WIDTH / 2, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2 })));
		gameObjects.emplace_back(std::make_shared<Ball>(sf::Vector2f({ SCREEN_WIDTH / 2, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2 })));
		CreateBlocks();
	}
	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::Pause);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		static auto updateFunc = [timeDelta](auto element) { element->Update(timeDelta); };
		std::for_each(gameObjects.begin(), gameObjects.end(), updateFunc);
		std::for_each(blocks.begin(), blocks.end(), updateFunc);

		std::shared_ptr<Platform> platform = std::static_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::static_pointer_cast<Ball>(gameObjects[1]);

		bool isNeedInverseX = false;
		bool isNeedInverseY = false;
		bool hasBrokeOneBlock = false;
		blocks.erase(
			std::remove_if(blocks.begin(), blocks.end(),
			[ball, &hasBrokeOneBlock, &isNeedInverseX, &isNeedInverseY, this](auto block)
			{
				if (!hasBrokeOneBlock && block->CheckCollision(ball))
				{
					hasBrokeOneBlock = true;
					const auto ballPos = ball->GetPosition();
					const auto blockRect = block->GetRect();

					GetBallInverse(ballPos, blockRect, isNeedInverseX, isNeedInverseY);
				}
				return block->IsBroken();
			}
			)
		);

		if (isNeedInverseX)
		{
			ball->InvertDirectionX();
		}
		if (isNeedInverseY)
		{
			ball->InvertDirectionY();
		}
		auto isCollision = platform->CheckCollision(ball);
		const bool isGameWin = blocks.empty();
		const bool isGameOver = !isCollision && ball->GetPosition().y > platform->GetRect().top;
		Game& game = Application::Instance().GetGame();
		if (isGameWin)
		{

		}
		else if (isGameOver)
		{
			game.PushState(GameStateType::GameOver);
		}

	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		for (auto&& object : gameObjects)
		{
			object->Draw(window);
		}
		static auto drawFunc = [&window](auto element) { element->Draw(window); };
		std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);
		std::for_each(blocks.begin(), blocks.end(), drawFunc);
	}

	void GameStatePlayingData::CreateBlocks()
	{
		for (int row = 0; row < 10; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				blocks.emplace_back(std::make_shared<SmoothDestroyableBlock>(
					sf::Vector2f({ col * BLOCK_WIDTH, 100 + row * BLOCK_HEIGHT }),
					rand() % 6));
			}
		}
	}

	void GameStatePlayingData::GetBallInverse(const sf::Vector2f& ballPosition, const sf::FloatRect& blockRect, bool& isNeedInverseDirectionX, bool& isNeedInverseDirectionY)
	{
		if (ballPosition.y > blockRect.top + blockRect.height)
		{
			isNeedInverseDirectionY = true;
		}
		if (ballPosition.y < blockRect.top)
		{
			isNeedInverseDirectionY = true;
		}
		if (ballPosition.x > blockRect.left + blockRect.width)
		{
			isNeedInverseDirectionX = true;
		}
		if (ballPosition.x < blockRect.left)
		{
			isNeedInverseDirectionX = true;
		}
	}
}
