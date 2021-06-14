class IState;
class MainMenuState;
#pragma once
#include "SFML/Graphics.hpp"
#include <memory>
#include <vector>

class App {
private:
	 sf::Vector2i _windowSize;
	 std::unique_ptr<IState> state;
public:
	App(sf::Vector2u windowSize) : _windowSize(windowSize) {}
	void HandleEvents(sf::Event, sf::Vector2i);
	void Draw(sf::RenderWindow&);
	void ChangeState(std::unique_ptr<IState>);
};

#include "IState.h"