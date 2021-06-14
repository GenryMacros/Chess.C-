#pragma once
class TiledGameFiled;
class GameState;
#include "SFML/Graphics.hpp"
#include "IState.h"

class TiledGameFiled {
private:
	std::unique_ptr<IState> _state = nullptr;
	GameState* _holder = nullptr;
public:
	TiledGameFiled(std::unique_ptr<IState> startState, GameState* holder);
	TiledGameFiled() = delete;

	std::unique_ptr<IState> ChangeAndReturnState(std::unique_ptr<IState> newState);
	void ChangeState(std::unique_ptr<IState> newState);
public:
	void Draw(sf::RenderWindow& win);
	void HandleEvent(sf::Event& event, sf::Vector2i mouseCoords);
	IState* GetCurrentState();
	void EndGame();
};

#include "GameState.h"