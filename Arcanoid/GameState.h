#pragma once
#include <SFML/Graphics.hpp>
#include <utility>

namespace Arcanoid
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		Pause,
		Records
	};

	class GameState
	{
	public:
		GameState() = default;
		GameState(GameStateType type);
		GameState(const GameState& state) = delete;
		GameState(GameState&& state) noexcept { operator=(std::move(state)); }

		~GameState();

		GameState& operator= (const GameState& state) = delete;
		GameState& operator= (GameState&& state) noexcept
		{
			type = state.type;
			data = state.data;
			state.data = nullptr;
			return *this;
		}

		GameStateType GetType() const { return type; }

		template<class T>
		T* GetData() const
		{
			return static_cast<T>(data);
		}

		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(sf::Event& event);

	private:
		GameStateType type = GameStateType::None;
		void* data = nullptr;
	};
}
