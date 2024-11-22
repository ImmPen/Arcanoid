#include "VariousBlock.h"
#include "GameSettings.h"
#include <assert.h>
namespace Arcanoid
{
	MultipleHitBlock::MultipleHitBlock(const sf::Vector2f& position, int durability)
		:Block(position, 7)
	{
		auto rect = BLOCK_RECT_IN_TEXTURE;
		rect.top = BLOCK_RECT_IN_TEXTURE.top + this->color * BLOCK_HEIGHT_ON_TILESET;
		rect.left = BLOCK_RECT_IN_TEXTURE.left + BLOCK_WIDTH_ON_TILESET;
		assert(this->texture.loadFromFile(RESOURCES_PATH + "spritesheet-breakout.png", rect));
		this->hitCount = durability;
	}
	void MultipleHitBlock::StageChange()
	{
		this->sprite.setColor(sf::Color(255, 255, 255, (int)(this->hitCount / (float)MAX_DURABILITY * 255)));
	}
	void MultipleHitBlock::OnHit(CollisionType type)
	{
		Super::OnHit(type);
		StageChange();
	}
	GlassBlock::GlassBlock(const sf::Vector2f& position)
		: Block(position, 6)
	{

	}
	CollisionType GlassBlock::GetCollision(std::shared_ptr<ICollidable> collidable) const 
	{
		return Super::GetCollision(collidable) == CollisionType::Hit
			? CollisionType::Overlap : CollisionType::None;
	}
}