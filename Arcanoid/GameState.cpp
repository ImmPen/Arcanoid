#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStatePause.h"
#include "GameStateRecords.h"
namespace Arcanoid
{
	GameState::GameState(GameStateType type)
	{
		switch (type)
		{
		case GameStateType::Playing:
			this->type = type;
			this->data = new GameStatePlayingData();
			((GameStatePlayingData*)data)->Init();
			break;
		case GameStateType::GameOver:
			this->type = type;
			this->data = new GameStateGameOverData();
			((GameStateGameOverData*)data)->Init();
			break;
		case GameStateType::MainMenu:
			this->type = type;
			this->data = new GameStateMainMenuData();
			((GameStateMainMenuData*)data)->Init();
			break;
		case GameStateType::Pause:
			this->type = type;
			this->data = new GameStatePauseData();
			((GameStatePauseData*)data)->Init();
			break;
		case GameStateType::Records:
			this->type = type;
			this->data = new GameStateRecordsData();
			((GameStateRecordsData*)data)->Init();
			break;
		default:
			break;
		}
	}

	GameState::~GameState()
	{
		if (this->data)
		{
			switch (this->type)
			{
			case GameStateType::Playing:
				delete ((GameStatePlayingData*)data);
				break;
			case GameStateType::GameOver:
				delete ((GameStateGameOverData*)data);
				break;
			case GameStateType::MainMenu:
				delete ((GameStateMainMenuData*)data);
				break;
			case GameStateType::Pause:
				delete ((GameStatePauseData*)data);
				break;
			case GameStateType::Records:
				delete ((GameStateRecordsData*)data);
				break;
			default:
				break;
			}
		}
	}

	void GameState::Update(float timeDelta)
	{
		switch (this->type)
		{
		case GameStateType::Playing:
			((GameStatePlayingData*)data)->Update(timeDelta);
			break;
		case GameStateType::GameOver:
			((GameStateGameOverData*)data)->Update(timeDelta);
			break;
		case GameStateType::MainMenu:
			((GameStateMainMenuData*)data)->Update(timeDelta);
			break;
		case GameStateType::Pause:
			((GameStatePauseData*)data)->Update(timeDelta);
			break;
		case GameStateType::Records:
			((GameStateRecordsData*)data)->Update(timeDelta);
			break;
		default:
			break;
		}
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		switch (this->type)
		{
		case GameStateType::Playing:
			((GameStatePlayingData*)data)->Draw(window);
			break;
		case GameStateType::GameOver:
			((GameStateGameOverData*)data)->Draw(window);
			break;
		case GameStateType::MainMenu:
			((GameStateMainMenuData*)data)->Draw(window);
			break;
		case GameStateType::Pause:
			((GameStatePauseData*)data)->Draw(window);
			break;
		case GameStateType::Records:
			((GameStateRecordsData*)data)->Draw(window);
			break;
		default:
			break;
		}
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		switch (this->type)
		{
		case GameStateType::Playing:
			((GameStatePlayingData*)data)->HandleWindowEvent(event);
			break;
		case GameStateType::GameOver:
			((GameStateGameOverData*)data)->HandleWindowEvent(event);
			break;
		case GameStateType::MainMenu:
			((GameStateMainMenuData*)data)->HandleWindowEvent(event);
			break;
		case GameStateType::Pause:
			((GameStatePauseData*)data)->HandleWindowEvent(event);
			break;
		case GameStateType::Records:
			((GameStateRecordsData*)data)->HandleWindowEvent(event);
			break;
		default:
			break;
		}
	}
}
