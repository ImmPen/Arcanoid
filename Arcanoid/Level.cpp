#include "Level.h"
#include <fstream>
#include "GameSettings.h"

namespace Arcanoid
{
	void LevelDescriptor::LoadFromFile(std::string fileName)
	{
		std::ifstream in(fileName);
		if (!in.is_open())
		{
			for (int i = 0; i < MAP_HEIGHT; i++)
			{
				this->levelSymbols.push_back({});
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					this->levelSymbols[i].push_back('.');
				}
			}
		}
		else
		{
			int i = 0;
			levelSymbols.push_back({});
			while (!in.eof())
			{
				char sym;
				in.get(sym);
				if (sym == '\n')
				{
					i++;
					if (!in.eof())
					{
						this->levelSymbols.push_back({});
					}
				}
				else
				{
					this->levelSymbols[i].push_back(sym);
				}
			}
		}
		in.close();
	}

	std::vector<std::vector<char>> LevelDescriptor::GetLevelSymbols()
	{
		return levelSymbols;
	}

	sf::Texture LevelDescriptor::GetTexture()
	{
		return this->tileSetTexture;
	}

	std::map<ETileTextureType, sf::IntRect> LevelDescriptor::GetMap()
	{
		return this->tileTextureTypeToTextureRect;
	}

	void Level::Draw(sf::RenderWindow& win)
	{
		for (int i = 0; i < this->tiles.size(); i++)
		{
			for (int j = 0; j < this->tiles[i].size(); j++)
			{
				const Tile& tile = this->tiles[i][j];
				sf::Sprite& sprite = this->tileTextureTypeToSprite[tile.textureType];
				sprite.setPosition(tileSize.x * j, tileSize.y * i);
				win.draw(sprite);
			}
		}
	}

	Level::Level(LevelDescriptor& levelDescriptor)
	{
		for (int i = 0; i < levelDescriptor.GetLevelSymbols().size(); i++)
		{
			this->tiles.push_back({});
			for (int j = 0; j < levelDescriptor.GetLevelSymbols()[i].size(); j++)
			{
				Tile tile;
				if (levelDescriptor.GetLevelSymbols()[i][j] == '#')
				{
					tile.collisionType = ETileCollisionType::Collision;
					tile.textureType = ETileTextureType::Wall;
				}
				else if (levelDescriptor.GetLevelSymbols()[i][j] == '.')
				{
					tile.collisionType = ETileCollisionType::NoCollision;
					tile.textureType = ETileTextureType::Ground;
				}
				this->tiles[i].push_back(tile);
			}
		}

		for (const auto& tileTextureTypeToRect : levelDescriptor.GetMap())
		{
			sf::Sprite sprite;
			sprite.setTexture(levelDescriptor.GetTexture());
			sprite.setTextureRect(tileTextureTypeToRect.second);
			this->tileTextureTypeToSprite[tileTextureTypeToRect.first] = sprite;
		}
	}
}