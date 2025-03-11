#pragma once
#include "GameObject.h"
#include "GameSettings.h"
#include "SFML/Graphics.hpp"
#include "Collidable.h"

namespace Arcanoid
{
	enum class BonusType
	{
		OnBallBonus,
		OnBlockBonus,
		OnPlatformBonus
	};

	class Bonus :
		public GameObject//, public ICollidable//, public IDelayedAction
	{
	public:
		Bonus(sf::Vector2f position) :
			GameObject(
				SETTINGS.RESOURCES_PATH + (std::string)"Powerups.png",
				SETTINGS.BONUS_RECT_IN_TEXTURE,
				position,
				SETTINGS.BONUS_WIDTH,
				SETTINGS.BONUS_HEIGHT)
		{	
					
		}
		virtual void Update(float timeDelta) override;

	private:

	};

	class OnBallBonus : public Bonus
	{
	public:
		OnBallBonus(sf::Vector2f position) :
			Bonus(position)
		{

		}
	};
}
