#pragma once
#include "TiledGameFiled.h"
#include "MainMenuState.h"
#include "ChessGameRule.h"
#include "GameInProgressState.h"

#define Default_Background "../OtherIm/Background1.jpg"

class GameState : public IState {
private:
	TiledGameFiled field;
	sf::Vector2u _winSize;
public:
	GameState(App* app, sf::Vector2u winSize);
	void HandleEvent(sf::Event& event, sf::Vector2i mouseCoords) override;
	void Draw(sf::RenderWindow& win) override;
	void EndGame();
};
