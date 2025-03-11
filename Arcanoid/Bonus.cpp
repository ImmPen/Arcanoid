#include "Bonus.h"


namespace Arcanoid
{
	void Bonus::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + SETTINGS.BONUS_SPEED * timeDelta * sf::Vector2f{ 0, 1 };
		this->sprite.setPosition(pos);
	}
}