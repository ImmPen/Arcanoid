#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>
#include <numbers>

namespace Arcanoid
{
	Ball::Ball(sf::Vector2f& position)
		: GameObject(
			RESOURCES_PATH + "spritesheet-breakout.png",
			BALL_RECT_IN_TEXTURE,
			position,
			BALL_SIZE, BALL_SIZE)
	{
		const float angle = lastAngle;
		this->direction.x = std::cos(std::numbers::pi / 180 * angle);
		this->direction.y = std::sin(std::numbers::pi / 180 * angle);
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + BALL_SPEED * timeDelta * this->direction;
		this->sprite.setPosition(pos);

		if (pos.x - BALL_SIZE / 2 <= 0 || pos.x + BALL_SIZE / 2 >= SCREEN_WIDTH) {
			direction.x *= -1;
		}

		if (pos.y - BALL_SIZE / 2 <= 0 || pos.y + BALL_SIZE / 2 >= SCREEN_HEIGHT) {
			direction.y *= -1;
		}
	}

	void Ball::InvertDirectionX()
	{
		this->direction.x *= -1;
	}

	void Ball::InvertDirectionY()
	{
		this->direction.y *= -1;
	}

	bool Ball::GetCollision(std::shared_ptr<ICollidable> collidableObject) const
	{
		return GetSpriteRect().intersects(collidableObject->GetRect());
	}

	void Ball::ChangeAngle(float angle)
	{
		lastAngle = angle;
		direction.x = (angle / abs(angle)) * std::cos(std::numbers::pi / 180 * angle);
		direction.y = -1 * abs(std::sin(std::numbers::pi / 180 * angle));
	}

	void Ball::OnHit()
	{
		const float lower = -5.f;
		const float higher = 5.f;
		lastAngle += lower + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (higher - lower));
		ChangeAngle(lastAngle);
	}
}