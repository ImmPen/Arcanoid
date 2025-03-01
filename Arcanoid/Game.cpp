#include "Game.h"
#include <fstream>
#include <assert.h>
#include "GameStatePlaying.h"

namespace Arcanoid
{
	void Game::LoadTableFromFile(std::string tablePath)
	{
		std::ifstream in(tablePath);
		if (!in.is_open())
		{
			for (int i = 0; i < SETTINGS.NUM_RECORDS_IN_TABLE; i++)
			{
				this->recordsTable.push_back(0);
			}
		}
		else
		{
			while (!in.eof())
			{
				int record;
				while (in >> record)
				{
					this->recordsTable.push_back(record);
				}
			}
		}
		in.close();
	}

	void Game::TypeTableToFile(std::string tablePath)
	{
		std::fstream out(tablePath);
		int i = 0;
		for (auto it = this->recordsTable.begin(); it != this->recordsTable.end() && i < SETTINGS.NUM_RECORDS_IN_TABLE; it++, i++)
		{
			out << *it << "\n";
		}
		out.close();
	}

	Game::Game()
	{
		this->gameStateChangeType = GameStateChangeType::None;
		this->pendingGameStateType = GameStateType::None;
		SwitchStateTo(GameStateType::MainMenu);

		std::string tablePath = SETTINGS.RESOURCES_PATH + "Records.txt";
		this->LoadTableFromFile(tablePath);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (this->gameStateStack.size() > 0)
			{
				this->gameStateStack.back().HandleWindowEvent(event);
			}
		}
	}
	
	void Game::Shutdown()
	{
		while (this->gameStateStack.size() > 0)
		{
			this->gameStateStack.pop_back();
		}
		this->gameStateChangeType = GameStateChangeType::None;
		this->pendingGameStateType = GameStateType::None;
		this->TypeTableToFile(SETTINGS.RESOURCES_PATH + "Records.txt");
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value) {
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else {
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}
	
	bool Game::Update(float timer)
	{
		switch (this->gameStateChangeType)			// Обрабатываем смену стейтов
		{
		case GameStateChangeType::Pop:
			if (this->gameStateStack.size() > 0)
			{
				this->gameStateStack.pop_back();
			}
			break;
		case GameStateChangeType::Switch:
			while (this->gameStateStack.size() > 0)
			{
				this->gameStateStack.pop_back();
			}
			break;
		default:
			break;
		}
		if (this->pendingGameStateType != GameStateType::None)
		{
			this->gameStateStack.push_back(GameState(this->pendingGameStateType));
		}
		this->pendingGameStateType = GameStateType::None;
		this->gameStateChangeType = GameStateChangeType::None;

		if (this->gameStateStack.size() > 0)	// Обновляем игру
		{
			this->soundManager.PlayMusic();
			this->gameStateStack.back().Update(timer);
			return true;
		}
		return false;	// Если в итоге стек стейтов пустой, то выходим из цикла
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (this->gameStateStack.size() > 0)
		{
			for (auto it = this->gameStateStack.begin(); it != this->gameStateStack.end(); it++)
			{
				it->Draw(window);
			}
		}
	}

	void Game::PushState(GameStateType stateType)
	{
		this->pendingGameStateType = stateType;
		this->gameStateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		this->pendingGameStateType = GameStateType::None;
		this->gameStateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType stateType)
	{
		this->pendingGameStateType = stateType;
		this->gameStateChangeType = GameStateChangeType::Switch;
	}

	std::vector<int> Game::GetRecordsTable() const
	{
		return this->recordsTable;
	}
	void Game::StartGame()
	{
		SwitchStateTo(GameStateType::Playing);
	}

	void Game::PauseGame()
	{
		PushState(GameStateType::Pause);
	}

	void Game::WinGame()
	{
		PushState(GameStateType::Win);
	}

	void Game::LoseGame()
	{
		PushState(GameStateType::GameOver);
	}

	void Game::UpdateGame(float timeDelta, sf::RenderWindow& window)
	{
		HandleWindowEvents(window);

		if (Update(SETTINGS.TIME_PER_FRAME))
		{
			window.clear();

			Draw(window);

			window.display();
		}
		else
		{
			window.close();
		}
	}

	void Game::ExitGame()
	{
		SwitchStateTo(GameStateType::MainMenu);
	}

	void Game::QuitGame()
	{
		SwitchStateTo(GameStateType::None);
	}

	void Game::ShowRecords()
	{
		SwitchStateTo(GameStateType::Records);
	}

	void Game::LoadNextLevel()
	{
		assert(gameStateStack.back().GetType() == GameStateType::Playing);
		auto playingData = (gameStateStack.back().GetData<GameStatePlayingData>());
		playingData->LoadNextLevel();
	}

}
