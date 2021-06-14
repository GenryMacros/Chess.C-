#include "GameInProgressState.h"

GameInProgressState::GameInProgressState(std::unique_ptr<IGameRule> rules, sf::Vector2u winSize, TiledGameFiled* holder, std::string backgroundPath) : _rules(std::move(rules)) {
	_holder = holder;
	_winSize = winSize;
	_backgroundIm.loadFromFile(backgroundPath);
	_backgroundTex.loadFromImage(_backgroundIm);
	_backgroundSp.setTexture(_backgroundTex);
	_backgroundSp.setScale(
		winSize.x / _backgroundSp.getLocalBounds().width,
		winSize.y / _backgroundSp.getLocalBounds().height);

	CreateField(sf::Vector2f((_winSize.x - 250) / 8, _winSize.y / 8));
	StartGame();
	CreateUI();
}

void GameInProgressState::HandleEvent(sf::Event& event, sf::Vector2i mousePos) {
	for (auto& elem : _uiElems) {
		if (elem->isContainsDot(mousePos)) {
			GameTags thisElemTag = (GameTags)elem->Tag;
			elem->ChangeAnimation(event);
			if (event.type != sf::Event::MouseButtonPressed)
				return;
			switch (thisElemTag)
			{
			case GameTags::MainMenu:
			{
				std::unique_ptr<IState> thisUptr = (_holder->ChangeAndReturnState(std::make_unique<GamePausedState>(_winSize, _holder)));
				IState* curState = _holder->GetCurrentState();
				dynamic_cast<GamePausedState*>(curState)->SetSavedGame(std::move(thisUptr));
				return;
			}
			break;
			default:
				break;
			}
		}
		else
			elem->ChangeAnimation();
	}
	if (event.type == sf::Event::MouseButtonPressed) {
		std::pair<bool, std::string> gameResult = _rules->HandleClick(mousePos, selectedTiles, _tilesHolder);
		if (gameResult.first == true) {
			_holder->ChangeState(std::make_unique<GameEndState>(gameResult.second, _winSize, _holder, sf::Color::White));
		}
	}
}

void GameInProgressState::Draw(sf::RenderWindow& win) {
	win.draw(_backgroundSp);
	for (auto& uielem : _uiElems)
		uielem->Draw(win);
	_tilesHolder.Draw(win);
}

void  GameInProgressState::setFieldSize(sf::Vector2u fieldSize) {
	_tilesHolder.setXsize(fieldSize.x).setYsize(fieldSize.y);
}

void  GameInProgressState::CreateField(sf::Vector2f tileSize) {
	sf::Vector2u fieldSize = _rules->GetStartFieldSize();
	_tilesHolder.setXsize(fieldSize.x).setYsize(fieldSize.y);
	float xCoord = 0;
	float yCoord = 0;
	for (int i = 0; i < fieldSize.y; i++) {
		CreateRow(sf::Vector2f(xCoord, yCoord), tileSize, fieldSize.x, i);
		xCoord = 0;
		yCoord += tileSize.y;
	}
}

void GameInProgressState::CreateRow(sf::Vector2f startCoord, sf::Vector2f tileSize, int xCount, int y) {
	_tilesHolder.AddRow(xCount);
	auto currentRow = _tilesHolder.lastRow();
	for (int j = 0; j < xCount; j++) {
		(*currentRow)[j].Create(tileSize, sf::Vector2f(startCoord.x, startCoord.y));
		(*currentRow)[j].SetGameCoords(sf::Vector2u(j, y));
		startCoord.x += tileSize.x;
	}
}

void GameInProgressState::StartGame() {
	_rules->PrepareForGame(_tilesHolder);
}

void GameInProgressState::CreateUI() {
	sf::Vector2i menuBlockSize(120, 50);
	sf::Vector2f menuBlockPosition(_winSize.x - menuBlockSize.x*1.5, 0);
	TextOptions defaultTextOptions({ sf::Color::White, 30, DefaultFont });
	sf::Color blockColor(150, 105, 110);
	sf::Color activeColor(255, 255, 255);
	std::unique_ptr<IUiElem> gameBlock = std::make_unique<Recktangle>(menuBlockSize, menuBlockPosition, blockColor, defaultTextOptions);
	gameBlock->setText("Menu");
	gameBlock->setTag((int)GameTags::MainMenu);
	gameBlock->setAnimator(std::make_unique<FadingAnimator>(blockColor, activeColor));
	_uiElems.push_back(std::move(gameBlock));
}

void  GameInProgressState::Reset() {
	_rules->Reset(_tilesHolder);
}