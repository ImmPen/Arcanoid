#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "GameObject.h"
#include "Collidable.h"

namespace Arcanoid
{
	class Platform : public GameObject, public ICollidable
	{
	public:
		Platform(sf::Vector2f& position);
		~Platform() override = default;
		void Update(float timeDelta) override;

		void OnHit() override {}
		bool CheckCollision(std::shared_ptr<ICollidable> collidable) override;
		
		bool GetCollision(std::shared_ptr<ICollidable> collidable) const override;

		sf::FloatRect GetRect() override { return GetSpriteRect(); }
	private:
		void Move(float speed);
	};
}
