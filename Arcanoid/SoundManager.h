#pragma once
#include <SFML/Audio.hpp>

namespace Arcanoid
{
	class Game;

	enum class Sounds
	{
		reboundSound,
		gameOverSound,
		menuHoverSound
	};

	class SoundManager
	{
	public:
		SoundManager();
		void PlaySound(Sounds sound);
		void PlayMusic();
	private:
		sf::SoundBuffer reboundBuffer;
		sf::SoundBuffer gameOverBuffer;
		sf::SoundBuffer menuHoverBuffer;

		sf::Sound reboundSound;
		sf::Sound gameOverSound;
		sf::Sound menuHoverSound;

		sf::Music music;
	};
}