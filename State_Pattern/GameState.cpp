#include "GameState.h"

GameState::GameState(App* app, sf::Vector2u winSize) : field(std::make_unique<GameInProgressState>(std::make_unique<ChessGameRule>(), winSize, &field, Default_Background), this) {
	_winSize = winSize;
	_app = app;
}
void GameState::HandleEvent(sf::Event& event, sf::Vector2i mouseCoords)  {
	field.HandleEvent(event, mouseCoords);
};
void GameState::Draw(sf::RenderWindow& win)  {
	field.Draw(win);
};
void GameState::EndGame() {
	_app->ChangeState(std::make_unique<MainMenuState>(_app, _winSize));
}