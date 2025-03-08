#include "BlockFactory.h"
#include "Block.h"
#include "VariousBlock.h"

namespace Arcanoid
{
    std::shared_ptr<Block> AnimatedBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        return std::make_shared<SmoothDestroyableBlock>(position);
    }
    std::unique_ptr<BlockFactory> AnimatedBlockFactory::clone()
    {
        return std::make_unique<AnimatedBlockFactory>();
    }
    std::shared_ptr<Block> UnbreakableBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        return std::make_shared<UnbreakableBlock>(position);
    }
    std::unique_ptr<BlockFactory> UnbreakableBlockFactory::clone()
    {
        return std::make_unique<UnbreakableBlockFactory>();
    }
    std::shared_ptr<Block> MultipleHitBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        return std::make_shared<MultipleHitBlock>(position);
    }
    std::unique_ptr<BlockFactory> MultipleHitBlockFactory::clone()
    {
        return std::make_unique<MultipleHitBlockFactory>();
    }
    std::shared_ptr<Block> GlassBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        return std::make_shared<GlassBlock>(position);
    }
    std::unique_ptr<BlockFactory> GlassBlockFactory::clone()
    {
        return std::make_unique<GlassBlockFactory>();
    }
}
