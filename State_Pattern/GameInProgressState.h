#pragma once
#include "IState.h"
#include "TiledGameFiled.h"
#include "GamePausedState.h"
#include "GameEndState.h"


enum class GameTags {
	MainMenu
};


class GameInProgressState : public IState {
private:
	TiledGameFiled* _holder;
	std::vector<std::unique_ptr<IUiElem>> _uiElems;
	std::vector<Tile*> selectedTiles;
	sf::Image _backgroundIm;
	sf::Texture _backgroundTex;
	sf::Sprite _backgroundSp;
	TilesHolder _tilesHolder;
	std::unique_ptr<IGameRule> _rules;
	sf::Vector2u _winSize;
public:
	GameInProgressState() = delete;
	GameInProgressState(std::unique_ptr<IGameRule> rules, sf::Vector2u winSize, TiledGameFiled* holder, std::string backgroundPath = "");
	void HandleEvent(sf::Event& event, sf::Vector2i mousePos) override;
	void Draw(sf::RenderWindow& win) override;
	void setFieldSize(sf::Vector2u fieldSize);
	void CreateField(sf::Vector2f tileSize);
private:
	void CreateRow(sf::Vector2f startCoord, sf::Vector2f tileSize, int xCount, int y);
public:
	void StartGame();
	void CreateUI();
	void Reset();
};