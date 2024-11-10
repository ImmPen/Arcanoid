#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

namespace Arcanoid
{
	enum class ETileTextureType
	{
		Ground,
		Wall
	};

	enum class ETileCollisionType
	{
		NoCollision,
		Collision
	};

	struct Tile
	{
		ETileCollisionType collisionType;
		ETileTextureType textureType;
	};

	class LevelDescriptor
	{
	public:
		void LoadFromFile(std::string fileName);
		std::vector<std::vector<char>> GetLevelSymbols();
		sf::Texture GetTexture();
		std::map<ETileTextureType, sf::IntRect> GetMap();
	private:
		std::vector<std::vector<char>> levelSymbols;
		std::map<ETileTextureType, sf::IntRect> tileTextureTypeToTextureRect;
		sf::Texture tileSetTexture;
	};

	class Level
	{
	public:
		Level(LevelDescriptor& levelDescriptor);
		void Draw(sf::RenderWindow& win);
	private:
		std::vector<std::vector<Tile>> tiles;
		std::map<ETileTextureType, sf::Sprite> tileTextureTypeToSprite;
	};

}