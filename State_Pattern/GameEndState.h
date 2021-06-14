#pragma once
#include "TiledGameFiled.h"
#include "IState.h"
#include "FadingAnimator.h"
#include "Recktangle.h"

enum class GameEndTags {
	ToMainMenu = 1
};

class GameEndState : public IState {
private:
	std::string _winnerName;
	std::vector<std::unique_ptr<IUiElem>> _uiElems;
	sf::Vector2u _winSize;
	TiledGameFiled* _holder = nullptr;
public:
	GameEndState(std::string winnerName, sf::Vector2u winSize, TiledGameFiled* holder,sf::Color winnerColor) : _winnerName(std::move(winnerName)), _winSize(winSize), _holder(holder) {
		CreateGameEndInterface(winnerColor);
	}
private:
	void CreateGameEndInterface(sf::Color winnerColor) {
		TextOptions defaultTextOptions({ sf::Color::White, 30, DefaultFont });

		sf::Vector2i holderBlockSize(400, 400);
		sf::Vector2f holderBlockPosition(_winSize.x / 2 - holderBlockSize.x / 2, _winSize.y / 2 - holderBlockSize.y / 2);
		sf::Color holderBlockkColor(100, 100, 100);
		std::unique_ptr<IUiElem> holdBlock = std::make_unique<Recktangle>(holderBlockSize, holderBlockPosition, holderBlockkColor, defaultTextOptions);


		std::unique_ptr<IUiElem> blockWithWinnerName = std::make_unique<Recktangle>(sf::Vector2i{ holderBlockSize.x,100}, holderBlockPosition, holderBlockkColor, TextOptions({ sf::Color::White, 35, DefaultFont }));
		blockWithWinnerName->setText("Congratulations " + _winnerName + "!");

		sf::Vector2i winnerImageBlockSize(holderBlockSize.x, 100);
		sf::Vector2f winnerImageBlockPosition(holderBlockPosition.x, holderBlockPosition.y + 100);
		std::unique_ptr<IUiElem> winnerImageBlock = std::make_unique<Recktangle>(winnerImageBlockSize,
			winnerImageBlockPosition
			, winnerColor, defaultTextOptions);

		sf::Vector2i toMainMenuSize(holderBlockSize.x, 50);
		sf::Vector2f toMainMenuElementPosition(holderBlockPosition.x, holderBlockPosition.y + holderBlockSize.y);
		sf::Color toMainMenuElementColor(100, 100, 100);
		sf::Color toMainMenuActiveColor(200, 130, 130);
		std::unique_ptr<IUiElem> toMainMenuBlock = std::make_unique<Recktangle>(toMainMenuSize, toMainMenuElementPosition, toMainMenuElementColor, defaultTextOptions);
		toMainMenuBlock->setAnimator(std::make_unique<FadingAnimator>(toMainMenuElementColor, toMainMenuActiveColor))->setText("To menu");
		toMainMenuBlock->Tag = (int)GameEndTags::ToMainMenu;

		_uiElems.push_back(std::move(holdBlock));
		_uiElems.push_back(std::move(toMainMenuBlock));
		_uiElems.push_back(std::move(winnerImageBlock));
		_uiElems.push_back(std::move(blockWithWinnerName));
	}
public:
	virtual void HandleEvent(sf::Event& event, sf::Vector2i mouseCoord) {
		for (auto& elem : _uiElems) {
			if (elem->isContainsDot(mouseCoord)) {
				elem->ChangeAnimation(event);
				if (event.type != sf::Event::MouseButtonPressed)
					continue;
				GameEndTags thisTileTag = (GameEndTags)elem->Tag;
				switch (thisTileTag)
				{
				case GameEndTags::ToMainMenu:
					_holder->EndGame();
					return;
				default:
					break;
				}
			}
			else
				elem->ChangeAnimation();
		}
	}
	virtual void Draw(sf::RenderWindow& win) {
		for (auto& elem : _uiElems)
			elem->Draw(win);

	}
};