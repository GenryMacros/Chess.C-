#include "App.h"
using namespace std;

void App::HandleEvents(sf::Event event, sf::Vector2i mousePos) {
	state->HandleEvent(event, mousePos);
}
void App::Draw(sf::RenderWindow& win) {
	if (!state.get())
		throw exception("App is stateless");
	state->Draw(win);
	win.display();
}
void App::ChangeState(std::unique_ptr<IState> newState) {
	IState* ptr = newState.release();
	state.reset(ptr);
}
