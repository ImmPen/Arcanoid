#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
namespace Arcanoid
{
	class Block;

	class BlockFactory
	{
	protected:

	public:
		virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) = 0;
		virtual std::unique_ptr<BlockFactory> clone() = 0;
		virtual ~BlockFactory() = default;
	};

	class AnimatedBlockFactory : public BlockFactory
	{
	public:
		virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		virtual std::unique_ptr<BlockFactory> clone() override;
		~AnimatedBlockFactory() = default;
	};
	class UnbreakableBlockFactory : public BlockFactory
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		virtual std::unique_ptr<BlockFactory> clone() override;
		~UnbreakableBlockFactory() override = default;
	};
	class MultipleHitBlockFactory : public BlockFactory
	{
	public:
		virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		virtual std::unique_ptr<BlockFactory> clone() override;
		~MultipleHitBlockFactory() = default;
	};
	class GlassBlockFactory : public BlockFactory
	{
	public:
		virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		virtual std::unique_ptr<BlockFactory> clone() override;
		~GlassBlockFactory() override = default;
	};
}
