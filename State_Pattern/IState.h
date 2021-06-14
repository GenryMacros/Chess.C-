#pragma once
#include "App.h"
class IState {
protected:
	App* _app;
public:
	virtual void HandleEvent(sf::Event&, sf::Vector2i) = 0;
	virtual void Draw(sf::RenderWindow&) = 0;
	virtual ~IState() {};
};

