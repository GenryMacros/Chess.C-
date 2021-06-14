#include "MainMenuState.h"

void MainMenuState::HandleEvent(sf::Event& event, sf::Vector2i mouseCoords) {
	MainMenuTags clickedButtonTag = _uiControlelr.HandleEvent(event, mouseCoords);
	HandleTag(clickedButtonTag);
};
void MainMenuState::HandleTag(MainMenuTags tag) {
	switch (tag)
	{
	case MainMenuTags::Game:
		_app->ChangeState(std::make_unique<GameState>(_app,_winSize));
		break;
	case MainMenuTags::Exit:
		_app->ChangeState(std::make_unique<ExitState>());
		break;
	default:
		break;
	}
}
void MainMenuState::Draw(sf::RenderWindow& win) {
	_uiControlelr.Draw(win);
};