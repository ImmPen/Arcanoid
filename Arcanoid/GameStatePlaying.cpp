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
		platform.Init();
		ball.Init();
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
		platform.Update(timeDelta);
		ball.Update(timeDelta);

		const bool isCollision = platform.CheckCollisionWithBall(ball);
		if (isCollision)
		{
			Application::Instance().GetGame().soundManager.PlaySound(Sounds::reboundSound);
			ball.ReboundFromPlatform();
		}
		const bool isGameOver = !isCollision && (ball.GetPosition().y > platform.GetRect().top);

		if (isGameOver)
		{
			auto& game = Application::Instance().GetGame();
			game.soundManager.PlaySound(Sounds::gameOverSound);
			game.PushState(GameStateType::GameOver);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		platform.Draw(window);
		ball.Draw(window);
	}
}
