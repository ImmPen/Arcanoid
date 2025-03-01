#include "BlockFactory.h"
#include "Block.h"
#include "VariousBlock.h"

namespace Arcanoid
{
    /*int BlockFactory::GetCreatedBreakableBlocksCount()
    {
        return this->createdBreakableBlocksCount;
    }
    void BlockFactory::ClearCounter()
    {
        this->createdBreakableBlocksCount = 0;
    }*/
    std::shared_ptr<Block> AnimatedBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        //++createdBreakableBlocksCount;
        return std::make_shared<SmoothDestroyableBlock>(position);
    }
    std::shared_ptr<Block> UnbreakableBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        return std::make_shared<UnbreakableBlock>(position);
    }
    std::shared_ptr<Block> MultipleHitBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        //++createdBreakableBlocksCount;
        return std::make_shared<MultipleHitBlock>(position);
    }
    std::shared_ptr<Block> GlassBlockFactory::CreateBlock(const sf::Vector2f& position)
    {
        //++createdBreakableBlocksCount;
        return std::make_shared<GlassBlock>(position);
    }
}
