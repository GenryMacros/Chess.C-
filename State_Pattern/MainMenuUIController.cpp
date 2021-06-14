#include "MainMenuUIController.h"


MainMenuUIController::MainMenuUIController(sf::Vector2u windowSize) {
	_windowSize = windowSize;
	BuildMainPage(_windowSize);
}
void MainMenuUIController::Draw(sf::RenderWindow& win) {
	for (auto& uiElem : _uiElems) {
		uiElem->Draw(win);
	}
};

MainMenuTags MainMenuUIController::HandleEvent(sf::Event& event, sf::Vector2i mouseCoords) {
	for (auto& elem : _uiElems) {
		if (elem->isContainsDot(mouseCoords)) {
			elem->ChangeAnimation(event);
			if (event.type == sf::Event::MouseButtonPressed)
				return DoActionDependingOnTag(elem->Tag);
		}
		else
			elem->ChangeAnimation();
	}
	return MainMenuTags::NONE;
};
MainMenuTags MainMenuUIController::DoActionDependingOnTag(int tag) {
	MainMenuTags tagInMainMenu = (MainMenuTags)tag;

	switch (tagInMainMenu)
	{
	case MainMenuTags::Game:
		return MainMenuTags::Game;
	case MainMenuTags::Options:
		lastPage = currentPage;
		currentPage = MainMenuTags::Options;
		BuildDependingOnPage();
		return MainMenuTags::Options;
	case MainMenuTags::Exit:
		return MainMenuTags::Exit;
	case MainMenuTags::Back:
		currentPage = lastPage;
		BuildDependingOnPage();
		return MainMenuTags::Back;
	default:
		return MainMenuTags::NONE;
	}
}
void MainMenuUIController::BuildDependingOnPage() {
	switch (currentPage)
	{
	case MainMenuTags::Options:
		BuildOptionsPage();
		return;
	case MainMenuTags::Main:
		BuildMainPage(_windowSize);
		return;
	default:
		return;
	}
}
void MainMenuUIController::BuildOptionsPage() {

}
void MainMenuUIController::BuildMainPage(sf::Vector2u windowSize) {
	sf::Vector2i mainMenuBlocksSize(200, 50);
	sf::Vector2f mainMenuFirstBlockPosition(windowSize.x/2 - mainMenuBlocksSize.x/2, windowSize.y/2 - mainMenuBlocksSize.y);
	sf::Color mainMenuBlocksColor(20, 20, 2);
	sf::Color mainActiveColor(60, 30, 15);
	TextOptions defaultTextOptions({ sf::Color::White, 30, DefaultFont });
	float buttonsIndent = mainMenuBlocksSize.y + 10;
	std::unique_ptr<IUiElem> gameBlock = std::make_unique<Recktangle>(mainMenuBlocksSize, mainMenuFirstBlockPosition, mainMenuBlocksColor, defaultTextOptions);
	gameBlock->setAnimator(std::make_unique<FadingAnimator>(mainMenuBlocksColor, mainActiveColor));
	gameBlock->setText("Play");
	gameBlock->Tag = (int)MainMenuTags::Game;

	std::unique_ptr<IUiElem> optionsBlock = gameBlock->Clone();

	optionsBlock->setText("Options")->setPos(
		sf::Vector2f(mainMenuFirstBlockPosition.x, mainMenuFirstBlockPosition.y + buttonsIndent));
	optionsBlock->Tag = (int)MainMenuTags::Options;

	std::unique_ptr<IUiElem> exitBlock = gameBlock->Clone();

	exitBlock->setText("Exit")->setPos(
		sf::Vector2f(mainMenuFirstBlockPosition.x, mainMenuFirstBlockPosition.y + buttonsIndent * 2));
	exitBlock->Tag = (int)MainMenuTags::Exit;

	std::unique_ptr<IUiElem> logoBlock = std::make_unique<Recktangle>(mainMenuBlocksSize,
		sf::Vector2f(mainMenuFirstBlockPosition.x, mainMenuFirstBlockPosition.y - buttonsIndent * 2),
		sf::Color::Black, TextOptions{ sf::Color::White, 55, DefaultFont });
	logoBlock->setAnimator(std::make_unique<DummyAnimator>());
	logoBlock->setText("The Chess");
	logoBlock->Tag = (int)MainMenuTags::NONE;

	_uiElems.push_back(std::move(logoBlock));
	_uiElems.push_back(std::move(gameBlock));
	_uiElems.push_back(std::move(optionsBlock));
	_uiElems.push_back(std::move(exitBlock));
}