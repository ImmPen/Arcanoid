#include "Block.h"
#include "GameSettings.h"
#include <assert.h>
#include "Sprite.h"
#include "Ball.h"

namespace Arcanoid
{
	void Block::OnHit()
	{
		this->hitCount -= hitDecrease;
	}

	Block::Block(const sf::Vector2f& position, const int color)
		: GameObject(
			RESOURCES_PATH + (std::string)"spritesheet-breakout.png",
			BLOCK_RECT_IN_TEXTURE,
			position,
			BLOCK_WIDTH,
			BLOCK_HEIGHT)
	{
		auto rect = BLOCK_RECT_IN_TEXTURE;
		this->color = color % NUM_COLORS;
		rect.top = BLOCK_RECT_IN_TEXTURE.top + this->color * BLOCK_HEIGHT_ON_TILESET;
		assert(this->texture.loadFromFile(RESOURCES_PATH + "spritesheet-breakout.png", rect));
	}

	void Block::Update(float timeDelta)
	{

	}

	bool Block::GetCollision(std::shared_ptr<ICollidable> collidableObject) const
	{
		return GetSpriteRect().intersects(collidableObject->GetRect());
	}

	bool Block::IsBroken()
	{
		return this->hitCount <= 0;
	}


	void SmoothDestroyableBlock::OnHit()
	{
		Super::OnHit();
		if (this->hitCount <= 0)
		{
			StartTimer(BREAK_TIME);
		}
	}

	bool SmoothDestroyableBlock::IsBroken()
	{
		return (Super::IsBroken() && !this->isTimerStarted);
	}

	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position, const int color)
		:
		Block(position, color)
	{

	}

	void SmoothDestroyableBlock::Update(float deltaTime)
	{
		Super::Update(deltaTime);
		UpdateTimer(deltaTime);
	}

	bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<ICollidable> collidableObject) const
	{
		if (isTimerStarted)
		{
			return false;
		}
		return Super::GetCollision(collidableObject);
	}

	void SmoothDestroyableBlock::EachTickAction(float deltaTime)
	{
		const float timeSinceStartedAnimation = destroyTime - currentTime;
		const int currentFrame = static_cast<int>(timeSinceStartedAnimation / TIME_ON_FRAME);
		sf::IntRect rectOnTileSet = BLOCK_RECT_IN_TEXTURE;
		rectOnTileSet.top = BLOCK_RECT_IN_TEXTURE.top + this->color * BLOCK_HEIGHT_ON_TILESET;
		rectOnTileSet.left = BLOCK_RECT_IN_TEXTURE.left + currentFrame * BLOCK_WIDTH_ON_TILESET;
		assert(this->texture.loadFromFile(RESOURCES_PATH + "spritesheet-breakout.png", rectOnTileSet));
	}

}