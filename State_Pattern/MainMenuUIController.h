#pragma once
#include <vector>
#include <memory>
#include "IUiElem.h"
#include "Recktangle.h"
#include "FadingAnimator.h"
#include "DummyAnimator.h"

enum class MainMenuTags {
	Main,
	Game,
	Options,
	Exit,
	Back,
	NONE
};

class MainMenuUIController {
private:
	std::vector<std::unique_ptr<IUiElem>> _uiElems;
	MainMenuTags currentPage;
	MainMenuTags lastPage;
	sf::Vector2u _windowSize ;
public:
	MainMenuUIController(sf::Vector2u windowSize);
	void Draw(sf::RenderWindow& win);

	MainMenuTags HandleEvent(sf::Event& event, sf::Vector2i mouseCoords);
private:
	MainMenuTags DoActionDependingOnTag(int tag);
	void BuildDependingOnPage();
	void BuildOptionsPage();
	void BuildMainPage(sf::Vector2u windowSize);
};