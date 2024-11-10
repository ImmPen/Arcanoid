#include "SoundManager.h"
#include "Game.h"
#include "Application.h"
#include <assert.h>

namespace Arcanoid
{
	SoundManager::SoundManager()
	{
		std::string musicPath = RESOURCES_PATH + "Clinthammer__Background_Music.wav";
		std::string reboundSoundPath = RESOURCES_PATH + "Owlstorm__Snake_hit.wav";
		std::string gameOverSoundPath = RESOURCES_PATH + "Maodin204__Lose.wav";
		std::string menuHoverSoundPath = RESOURCES_PATH + "Theevilsocks__menu-hover.wav";
		assert(this->music.openFromFile(musicPath));
		assert(this->gameOverBuffer.loadFromFile(gameOverSoundPath));
		assert(this->reboundBuffer.loadFromFile(reboundSoundPath));
		assert(this->menuHoverBuffer.loadFromFile(menuHoverSoundPath));

		this->gameOverSound.setBuffer(this->gameOverBuffer);
		this->reboundSound.setBuffer(this->reboundBuffer);
		this->menuHoverSound.setBuffer(this->menuHoverBuffer);
	}
	void SoundManager::PlaySound(Sounds sound)
	{
		if ((std::uint8_t)Application::Instance().GetGame().IsEnableOptions(GameOptions::SOUNDS_ON))
		{
			switch (sound)
			{
			case Sounds::reboundSound:
				this->reboundSound.play();
				break;
			case Sounds::gameOverSound:
				this->gameOverSound.play();
				break;
			case Sounds::menuHoverSound:
				//this->menuHoverSound.play();
				break;
			default:
				break;
			}
		}
	}
	void SoundManager::PlayMusic()
	{
		if ((std::uint8_t)Application::Instance().GetGame().IsEnableOptions(GameOptions::MUSIC_ON))
		{
			if (this->music.getStatus() != sf::Music::Playing)
			{
				this->music.play();
			}
		}
		else
		{
			this->music.stop();
		}
	}
}
