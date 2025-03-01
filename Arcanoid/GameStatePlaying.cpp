#include "GameStatePlaying.h"
#include <assert.h>
#include "Game.h"
#include "GameSettings.h"
#include "Application.h"
#include "VariousBlock.h"


namespace Arcanoid
{
	void GameStatePlayingData::Init()
	{
		currentLevel = 0;
		assert(this->font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/arial.ttf"));
		gameObjects.emplace_back(std::make_shared<Platform>(
			sf::Vector2f({
				static_cast<float>(SETTINGS.SCREEN_WIDTH / 2),
				static_cast<float>(SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT / 2) })));
		auto ball = std::make_shared<Ball>(sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT - SETTINGS.BALL_SIZE / 2.f }));
		ball->AddObserver(weak_from_this());
		gameObjects.emplace_back(ball);
		this->factories.emplace(BlockType::Animated, std::make_unique<AnimatedBlockFactory>());
		this->factories.emplace(BlockType::Unbreakable, std::make_unique<UnbreakableBlockFactory>());
		this->factories.emplace(BlockType::MultipleHit, std::make_unique<MultipleHitBlockFactory>());
		this->factories.emplace(BlockType::Glass, std::make_unique<GlassBlockFactory>());
		CreateBlocks();
	}
	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PauseGame();
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
				auto collisionType = block->GetCollision(ball);
				if (!hasBrokeOneBlock && block->CheckCollision(ball))
				{
					hasBrokeOneBlock = true;
					if (collisionType == CollisionType::Hit)
					{
						const auto ballPos = ball->GetPosition();
						const auto blockRect = block->GetRect();
						GetBallInverse(ballPos, blockRect, isNeedInverseX, isNeedInverseY);
					}
				}
				return block->IsBroken();
			}
			), blocks.end()
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
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		static auto drawFunc = [&window](auto element) { element->Draw(window); };
		std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);
		std::for_each(blocks.begin(), blocks.end(), drawFunc);
	}

	void GameStatePlayingData::LoadNextLevel()
	{
		if (currentLevel >= levelLoader.GetLevelCount() - 1) {
			Game& game = Application::Instance().GetGame();
			game.WinGame();
		}
		else
		{
			std::shared_ptr <Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
			std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
			platform->Restart();
			ball->Restart();

			blocks.clear();
			++currentLevel;
			CreateBlocks();
		}
	}

	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
		Game& game = Application::Instance().GetGame();
		if (auto block = std::dynamic_pointer_cast<Block>(observable); block) {			
			if (IsWinCondition()) {
				game.LoadNextLevel();
			}
		}
		else if (auto ball = std::dynamic_pointer_cast<Ball>(observable); ball)
		{
			if (ball->GetPosition().y > gameObjects.front()->GetSpriteRect().top) {
				game.GetSoundManager().PlaySound(Sounds::gameOverSound);
				game.LoseGame();
			}
		}
	}

	void GameStatePlayingData::CreateBlocks()
	{
		auto self = weak_from_this();

		/*for (const auto& pair : factories)
		{
			pair.second->ClearCounter();
		}*/
		auto& level = levelLoader.GetLevel(currentLevel);
		for (auto block : level.blocks)
		{
			auto blockType = block.second;
			auto blockPostion = block.first;

			sf::Vector2f position{
				(float)(SETTINGS.BLOCK_WIDTH / 2 + blockPostion.x * SETTINGS.BLOCK_WIDTH),
				(float)(blockPostion.y * SETTINGS.BLOCK_HEIGHT)
			};
			blocks.emplace_back(factories.at(blockType)->CreateBlock(position));
			blocks.back()->AddObserver(self);
		}
	}

	bool GameStatePlayingData::IsWinCondition()
	{
		for (auto element : blocks)
		{
			auto isUnbreakable = std::dynamic_pointer_cast<UnbreakableBlock>(element);
			auto isBroken = element->IsBroken();
			if (!isUnbreakable && !isBroken)
			{
				return false;
			}
		}
		return true;
	}

	void GameStatePlayingData::GetBallInverse(
		const sf::Vector2f& ballPosition,
		const sf::FloatRect& blockRect,
		bool& isNeedInverseDirectionX,
		bool& isNeedInverseDirectionY)
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
