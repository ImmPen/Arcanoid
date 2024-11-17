#include <assert.h>
#include "GameObject.h"
#include "Sprite.h"

namespace Arcanoid
{
	GameObject::GameObject(std::string& texture, sf::IntRect& rectInTexture, sf::Vector2f& position, int desiredWidth, int desiredHeight)
	{
		assert(this->texture.loadFromFile(texture, rectInTexture));

		InitSprite(this->sprite, desiredWidth, desiredHeight, this->texture);
		this->sprite.setPosition(position);
	}
	void GameObject::Draw(sf::RenderWindow& window)
	{
		window.draw(this->sprite);
	}
}