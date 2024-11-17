#include "Platform.h"
#include "assert.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <algorithm>

namespace Arcanoid
{
	Platform::Platform(sf::Vector2f& position)
		: GameObject(
			RESOURCES_PATH + "spritesheet-breakout.png",
			PLATFORM_RECT_IN_TEXTURE,
			position,
			PLATFORM_WIDTH, PLATFORM_HEIGHT)
	{

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

	bool Platform::CheckCollision(std::shared_ptr<ICollidable> collidable)
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball)
		{
			return false;
		}
		if (GetCollision(ball))
		{
			auto rect = this->GetRect();
			auto ballPosOnPlatform = (ball->GetPosition().x - (rect.left + rect.width / 2)) / (rect.width / 2);
			ball->ChangeAngle(90 - 20 * ballPosOnPlatform);
			return true;
		}
		return	false;
	}

	bool Platform::GetCollision(std::shared_ptr<ICollidable> collidable) const
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball)
		{
			return false;
		}
		auto sqr = [](float x) {
			return x * x;
			};

		const auto rect = this->GetSpriteRect();
		const auto ballPos = ball->GetPosition();

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