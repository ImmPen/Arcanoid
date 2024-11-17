#pragma once
#include <SFML/Graphics.hpp>
namespace Arcanoid
{
	class GameObject
	{
	public:
		virtual ~GameObject() = default;
		GameObject(std::string& texture, sf::IntRect& rectInTexture, sf::Vector2f& position, int desiredWidth, int desiredHeight);
		virtual void Update(float timeDelta) = 0;
		virtual void Draw(sf::RenderWindow& window);

		const sf::Vector2f& GetPosition() const { return this->sprite.getPosition(); }
		const sf::FloatRect& GetSpriteRect() const { return this->sprite.getGlobalBounds(); }
	protected:
		sf::Sprite sprite;
		sf::Texture texture;
	};
}
