#pragma once
#include "TiledGameFiled.h"
#include "IState.h"
#include "FadingAnimator.h"
#include "Recktangle.h"

enum class GamePausedTags {
	Continue = 1,
	Exit = 2,
	Restart = 3
};

class GamePausedState : public IState {
private:
	std::unique_ptr<IState> _savedGame;
	TiledGameFiled* _holder;
	std::vector<std::unique_ptr<IUiElem>> _uiElems;
	sf::Vector2u _winSize;
	sf::Image backgroundIm;
	sf::Texture backgroundTex;
	sf::Sprite backgroundSp;
public:
	GamePausedState(sf::Vector2u winSize, TiledGameFiled* holder) : _winSize(winSize) {
		_holder = holder;
		backgroundIm.create(winSize.x, winSize.y, sf::Color(0,0,0,210));
		backgroundTex.loadFromImage(backgroundIm);
		backgroundSp.setTexture(backgroundTex);
		CreatePauseMenu();
	};
	void SetSavedGame(std::unique_ptr<IState> savedGame);
	void HandleEvent(sf::Event& event, sf::Vector2i mousePos) override;

	void Draw(sf::RenderWindow& win)  override;
private:
	void CreatePauseMenu();
};

