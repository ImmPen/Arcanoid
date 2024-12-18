#pragma once
#include <random>
#include <vector>
#include <unordered_map>
#include "SoundManager.h"
#include "GameSettings.h"
#include "GameState.h"

namespace Arcanoid
{
	
	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	enum class GameOptions : std::uint8_t
	{
		MUSIC_ON = 0x01,
		SOUNDS_ON = 0x02,
		DEFAULT = MUSIC_ON | SOUNDS_ON,
		Empty = 0
	};

	class Game
	{
	public:
		Game();
		~Game();
		void HandleWindowEvents(sf::RenderWindow& window);
		bool Update(float timer);
		void Draw(sf::RenderWindow& window);
		void Shutdown();

		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);

		void PushState(GameStateType stateType);
		void PopState();
		void SwitchStateTo(GameStateType stateType);

		std::vector<int> GetRecordsTable() const;
		SoundManager& GetSoundManager() { return this->soundManager; }
		
	private:
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;

		GameOptions options = GameOptions::DEFAULT;
		std::vector<int> recordsTable;
		int currentScore = 0;
		SoundManager soundManager;

		void LoadTableFromFile(std::string tablePath);
		void TypeTableToFile(std::string tablePath);
	};
}
