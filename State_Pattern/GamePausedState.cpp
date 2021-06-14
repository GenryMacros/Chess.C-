#include "GamePausedState.h"


void GamePausedState::SetSavedGame(std::unique_ptr<IState> savedGame) {
	_savedGame = std::move(savedGame);
}

void GamePausedState::HandleEvent(sf::Event& event, sf::Vector2i mousePos) {
	for (auto& elem : _uiElems) {
		if (elem->isContainsDot(mousePos)) {
			elem->ChangeAnimation(event);
			if (event.type != sf::Event::MouseButtonPressed)
				continue;
			GamePausedTags thisTileTag = (GamePausedTags)elem->Tag;
			switch (thisTileTag)
			{
			case GamePausedTags::Continue:
				_holder->ChangeState(std::move(_savedGame));
				return;
			case GamePausedTags::Exit:
				_holder->EndGame();
				return;
			case GamePausedTags::Restart:
				dynamic_cast<GameInProgressState*>(_savedGame.get())->Reset();
				_holder->ChangeState(std::move(_savedGame));
				return;
			default:
				break;
			}
		}
		else
			elem->ChangeAnimation();
	}
};

void GamePausedState::Draw(sf::RenderWindow& win) {
	_savedGame->Draw(win);
	win.draw(backgroundSp);
	for (auto& elem : _uiElems)
		elem->Draw(win);
};
void GamePausedState::CreatePauseMenu() {
	TextOptions defaultTextOptions({ sf::Color::White, 25, DefaultFont });

	sf::Vector2i holderBlockSize(250, 350);
	sf::Vector2f holderBlockPosition(_winSize.x / 2 - holderBlockSize.x / 2, _winSize.y / 2 - holderBlockSize.y / 2);
	sf::Color holderBlockkColor(100, 100, 100);
	std::unique_ptr<IUiElem> holdBlock = std::make_unique<Recktangle>(holderBlockSize, holderBlockPosition, holderBlockkColor, defaultTextOptions);

	sf::Vector2i gamePausedElementSize(250, 50);
	sf::Vector2f  gamePausedElementPosition(holderBlockPosition.x, holderBlockPosition.y + 100);
	sf::Color  gamePausedElementColor(100, 100, 100);
	sf::Color  gamePausedActiveColor(200, 130, 130);

	std::unique_ptr<IUiElem> gamePausedText = std::make_unique<Recktangle>(gamePausedElementSize, sf::Vector2f{ holderBlockPosition.x, holderBlockPosition.y}, gamePausedElementColor, TextOptions{ sf::Color::White, 35 , DefaultFont });
	gamePausedText->setText("Game paused");
	std::unique_ptr<IUiElem> continueBlock = std::make_unique<Recktangle>(gamePausedElementSize, sf::Vector2f{ gamePausedElementPosition.x, gamePausedElementPosition.y }, gamePausedElementColor, defaultTextOptions);
	continueBlock->setAnimator(std::make_unique<FadingAnimator>(gamePausedElementColor, gamePausedActiveColor))->setText("Continue");
	continueBlock->Tag = (int)GamePausedTags::Continue;

	std::unique_ptr<IUiElem> restartBlock = std::move(continueBlock->Clone());
	restartBlock->setPos(sf::Vector2f(gamePausedElementPosition.x, gamePausedElementPosition.y + gamePausedElementSize.y));
	restartBlock->setText("Restart");
	restartBlock->Tag = (int)GamePausedTags::Restart;

	std::unique_ptr<IUiElem> exitBlock = std::move(restartBlock->Clone());
	exitBlock->setPos(sf::Vector2f(gamePausedElementPosition.x, gamePausedElementPosition.y + gamePausedElementSize.y * 2));
	exitBlock->setText("Exit");
	exitBlock->Tag = (int)GamePausedTags::Exit;


	_uiElems.push_back(std::move(holdBlock));
	_uiElems.push_back(std::move(gamePausedText));
	_uiElems.push_back(std::move(continueBlock));
	_uiElems.push_back(std::move(exitBlock));
	_uiElems.push_back(std::move(restartBlock));
}