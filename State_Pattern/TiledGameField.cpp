#include "TiledGameFiled.h"
#include "Recktangle.h"
#include "FadingAnimator.h"



using namespace std;
TiledGameFiled::TiledGameFiled(std::unique_ptr<IState> startState, GameState* holder) {
		_holder = holder;
		_state = std::move(startState);
	}

	void TiledGameFiled::HandleEvent(sf::Event& event, sf::Vector2i mouseCoords) {
		_state->HandleEvent(event, mouseCoords);
	}
	void TiledGameFiled::Draw(sf::RenderWindow& win) {
		_state->Draw(win);
	}
	std::unique_ptr<IState> TiledGameFiled::ChangeAndReturnState(std::unique_ptr<IState> newState) {
		std::unique_ptr<IState> oldState = std::move(_state);
		_state = std::move(newState);
		return oldState;
	}
	void TiledGameFiled::ChangeState(std::unique_ptr<IState> newState) {
		IState* ptr = newState.release();
		_state.reset(ptr);
	}
	IState* TiledGameFiled::GetCurrentState() {
		return _state.get();
	}
	void TiledGameFiled::EndGame() {
		_holder->EndGame();
	}