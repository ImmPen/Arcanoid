#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStatePause.h"
#include "GameStateRecords.h"

namespace Arcanoid
{
	GameState::GameState(GameStateType type) : 
		type(type)
	{
		switch (type)
		{
		case GameStateType::Playing:
			this->data = std::make_unique<GameStatePlayingData>();
			break;
		case GameStateType::GameOver:
			this->data = std::make_unique<GameStateGameOverData>();
			break;
		case GameStateType::MainMenu:
			this->data = std::make_unique<GameStateMainMenuData>();
			break;
		case GameStateType::Pause:
			this->data = std::make_unique<GameStatePauseData>();
			break;
		case GameStateType::Records:
			this->data = std::make_unique<GameStateRecordsData>();
			break;
		default:
			break;
		}
		if (data)
		{
			data->Init();
		}
	}

	GameState::~GameState()
	{
		if (data)
		{
			data = nullptr;
		}
	}

	void GameState::Update(float timeDelta)
	{
		data->Update(timeDelta);
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		data->Draw(window);
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		data->HandleWindowEvent(event);
	}
}
