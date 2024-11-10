#include "Platform.h"
#include "assert.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <algorithm>

namespace Arcanoid
{
	void Platform::Init()
	{
		assert(this->texture.loadFromFile(RESOURCES_PATH + "spritesheet-breakout.png", PLATFORM_RECT_IN_TEXTURE));
		
		InitSprite(this->sprite, PLATFORM_WIDTH, PLATFORM_HEIGHT, this->texture);
		this->sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.f);
	}

	void Platform::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->Move(-timeDelta * PLATFORM_SPEED);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->Move(timeDelta * PLATFORM_SPEED);
		}
	}

	void Platform::Draw(sf::RenderWindow& window)
	{
		DrawSprite(this->sprite, window);
	}

	bool Platform::CheckCollisionWithBall(const Ball& ball)
	{
		auto sqr = [](float x) {
			return x * x;
			};

		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball.GetPosition();

		if (ballPos.x < rect.left) {
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}

		if (ballPos.x > rect.left + rect.width) {
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.0);
		}
		return std::fabs(ballPos.y - rect.top) <= BALL_SIZE / 2.0;
	}

	void Platform::Move(float speed)
	{
		auto positon = this->sprite.getPosition();
		positon.x = std::clamp(positon.x + speed, PLATFORM_WIDTH / 2.f, SCREEN_WIDTH - PLATFORM_WIDTH / 2.f);
		sprite.setPosition(positon);
	}
}