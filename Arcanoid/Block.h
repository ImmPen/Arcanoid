#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "DelayedAction.h"

namespace Arcanoid
{
	class Block : public GameObject, public ICollidable
	{
	protected:
		void OnHit(CollisionType type) override;
		int hitCount = 1;
		int hitDecrease = 1;
		int color;
	public:
		Block(const sf::Vector2f& position, const int color);
		virtual ~Block() override = default;
		void Update(float timeDelta) override;
		CollisionType GetCollision(std::shared_ptr<ICollidable> collidableObject) const override;
		sf::FloatRect GetRect() override { return GetSpriteRect(); }
		virtual bool IsBroken() const;
	};

	class SmoothDestroyableBlock : public Block, public IDelayedAction
	{
		using Super = Block;
	protected:
		void OnHit(CollisionType type) override;
	public:
		SmoothDestroyableBlock(const sf::Vector2f& position, const int color);
		~SmoothDestroyableBlock() override = default;

		void Update(float deltaTime) override;
		CollisionType GetCollision(std::shared_ptr<ICollidable> collidableObject) const override;
		bool IsBroken() const override;

		void EachTickAction(float deltaTime) override;
	};

	class UnbreakableBlock : public Block
	{

	public:
		UnbreakableBlock(const sf::Vector2f& position);
		~UnbreakableBlock() override = default;
	};
}
