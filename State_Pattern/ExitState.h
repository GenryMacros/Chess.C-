#pragma once
#include "IState.h"

class ExitState : public IState {
private:

public:
	virtual void HandleEvent(sf::Event&, sf::Vector2i) override {};
	virtual void Draw(sf::RenderWindow& win) override {
		win.close();
		return;
	};


}; 
