#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>
#include <numbers>

namespace Arcanoid
{
	void Ball::Init()
	{
		assert(this->texture.loadFromFile(RESOURCES_PATH + "spritesheet-breakout.png", BALL_RECT_IN_TEXTURE));

		InitSprite(this->sprite, BALL_SIZE, BALL_SIZE, this->texture);
		this->sprite.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f);
		
		const float angle = 45.f + rand() % 90; // 45 .. 135 degrees
		this->direction.x = std::cos(std::numbers::pi / 180 * angle);
		this->direction.y = -std::sin(std::numbers::pi / 180 * angle);
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + BALL_SPEED * timeDelta * this->direction;
		this->sprite.setPosition(pos);

		if (pos.x <= 0 || pos.x >= SCREEN_WIDTH) {
			direction.x *= -1;
		}

		if (pos.y <= 0 || pos.y >= SCREEN_HEIGHT) {
			direction.y *= -1;
		}
	}

	void Ball::Draw(sf::RenderWindow& window)
	{
		DrawSprite(this->sprite, window);
	}

	void Ball::ReboundFromPlatform()
	{
		direction.y *= -1;
	}
}