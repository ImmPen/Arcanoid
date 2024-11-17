#include <assert.h>
#include "GameStateGameOver.h"
#include "Game.h"
#include "Application.h"

namespace Arcanoid
{
	void GameStateGameOverData::Init()
	{
		assert(this->font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		MenuItem newGameItem;
		newGameItem.text.setString("Start new game");
		newGameItem.text.setFont(this->font);
		newGameItem.text.setCharacterSize(24);
		newGameItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
			};

		MenuItem mainMenuItem;
		mainMenuItem.text.setString("Exit main menu");
		mainMenuItem.text.setFont(this->font);
		mainMenuItem.text.setCharacterSize(24);
		mainMenuItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().SwitchStateTo(GameStateType::MainMenu);
			};

		MenuItem gameOverMenu;
		gameOverMenu.hintText.setString("Game Over");
		gameOverMenu.hintText.setFont(this->font);
		gameOverMenu.hintText.setCharacterSize(24);
		gameOverMenu.hintText.setFillColor(sf::Color::Red);
		gameOverMenu.childrenOrientation = Orientation::Horizontal;
		gameOverMenu.childrenAlignment = Alignment::Middle;
		gameOverMenu.childrenSpacing = 20.f;
		gameOverMenu.childrens.push_back(newGameItem);
		gameOverMenu.childrens.push_back(mainMenuItem);

		this->menu.Init(gameOverMenu);
		
		int i = 0;
		auto recordsTable = Application::Instance().GetGame().GetRecordsTable();
		for (auto it = recordsTable.begin(); it < recordsTable.end() && i < NUM_RECORDS_IN_TABLE; it++, i++)
		{
			this->recordsTableTexts.emplace_back();
			sf::Text& text = this->recordsTableTexts.back();

			text.setString(std::to_string(i + 1) + ". " + std::to_string(*it));
			text.setFont(this->font);
			text.setFillColor(sf::Color::White);
			text.setCharacterSize(24);
		}

		this->background.setFillColor(sf::Color(0, 0, 0, 128));
	}
	void GameStateGameOverData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().SwitchStateTo(GameStateType::MainMenu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				this->menu.PressOnSelectedItem();
			}

			Orientation orientation = this->menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				Application::Instance().GetGame().GetSoundManager().PlaySound(Sounds::menuHoverSound);
				this->menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				Application::Instance().GetGame().GetSoundManager().PlaySound(Sounds::menuHoverSound);
				this->menu.SwitchToNextMenuItem();
			}
		}
	}
	void GameStateGameOverData::Update(float timeDelta)
	{
	}
	void GameStateGameOverData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &this->menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		this->menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}