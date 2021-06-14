#pragma once
#include "IState.h"
#include "Recktangle.h"
#include "ExitState.h"
#include "FadingAnimator.h"
#include "MainMenuUIController.h"

class MainMenuState : public IState {
private:
	MainMenuUIController _uiControlelr;
	sf::Vector2u _winSize;
public:
	MainMenuState() = delete;

	MainMenuState(App* app, sf::Vector2u windowSize) : _uiControlelr(windowSize), _winSize(windowSize) {
		_app = app;
	}
	virtual void HandleEvent(sf::Event& event, sf::Vector2i mouseCoords) override;
private:
	void HandleTag(MainMenuTags tag);
public:
	virtual void Draw(sf::RenderWindow& win) override;
};

#include "GameState.h"