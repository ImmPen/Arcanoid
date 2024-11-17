#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Block.h"

namespace Arcanoid
{
	class Ball : public GameObject, public ICollidable
	{
	public:
		Ball(sf::Vector2f& position);
		~Ball() override = default;

		void Update(float timeDelta) override;

		void InvertDirectionX();
		void InvertDirectionY();

		bool GetCollision(std::shared_ptr<ICollidable> collidableObject) const override;
		void ChangeAngle(float angle);

		sf::FloatRect GetRect() override { return GetSpriteRect(); }
	private:
		void OnHit() override;
		sf::Vector2f direction;
		float lastAngle = 90;
	};
}
