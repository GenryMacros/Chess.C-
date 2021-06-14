#include "Table.h"

Play_field::Play_field(sf::Vector2u tileSize, TableColor_settings settings) :
	_tileSize(tileSize), _settings(settings) {
	CreateBoardTilesTextures();
	_field.setXsize(8).setYsize(8);
	int yPos = 0;
	bool isnextWhite = true;
	spawnFigures(Team::WHITE, yPos, isnextWhite);
	spawnSpaceBetweenTeams(yPos, isnextWhite);
	spawnFigures(Team::BLACK, yPos, isnextWhite);
}

void Play_field::Draw(sf::RenderWindow& win) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Tile& curTile = *_field.getTile(sf::Vector2u(j, i));
			curTile.sp.setColor(curTile.curColor);
			win.draw(curTile.sp);
			if (curTile.containedPiece.get())
				curTile.containedPiece->Draw(win);
		}
	}
}

SmartMatrix& Play_field::getTable() {
	return _field;
}

void Play_field::handleClick(sf::Vector2i mousePos) {
	toNormalColor();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (isThisTileClicked(mousePos, sf::Vector2i(i, j)))
				return;
		}
	}
}

void Play_field::CreateBoardTilesTextures() {
	blackTileImage.create(_tileSize.x, _tileSize.y, _settings.blackCol);
	blackTileTexture.loadFromImage(blackTileImage);
	whiteTileImage.create(_tileSize.x, _tileSize.y, _settings.whiteCol);
	whiteTileTexture.loadFromImage(whiteTileImage);
}

void Play_field::spawnFigures(Team spawnBlack, int& yPos, bool& isnextWhite) {
	switch (spawnBlack) {
	case Team::WHITE:
		spawnRetinue(spawnBlack, yPos, isnextWhite);
		spawnPawns(spawnBlack, yPos, isnextWhite);
		break;

	case Team::BLACK:
		spawnPawns(spawnBlack, yPos, isnextWhite);
		spawnRetinue(spawnBlack, yPos, isnextWhite);
		break;
	default:
		throw std::invalid_argument("Wrong team given");
	}
}

void Play_field::spawnSpaceBetweenTeams(int& yPos, bool& isNextWhite) {
	int xPos = 0;
	for (int i = 2; i < 6; i++, isNextWhite = !isNextWhite, yPos += _tileSize.y) {
		_field.AddRow(std::vector<Tile>(8));
		for (int j = 0; j < 8; j++, isNextWhite = !isNextWhite, xPos += _tileSize.x) {
			Tile& curTile = _field.createTile(sf::Vector2u(j, i), TileInitParams{ sf::Vector2f(xPos, yPos),
			isNextWhite ? _settings.whiteCol : _settings.blackCol,
			isNextWhite ? whiteTileTexture : blackTileTexture });
		}
		xPos = 0;
	}
}

bool Play_field::isThisTileClicked(sf::Vector2i mousePos, sf::Vector2i matrixIJ) {
	if ((*_field.getTile(sf::Vector2u(matrixIJ.x, matrixIJ.y))).sp.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		if (ifPieceSelected(matrixIJ))
			return true;
		else if (ifNoPieceSelected(matrixIJ))
			return true;
	}
	return false;
}

bool Play_field::ifPieceSelected(sf::Vector2i matrixIJ) {
	if (_selectedPiece != nullptr) {
		for (auto& it : _selectedTiles) {
			Tile& curTile = *_field.getTile(sf::Vector2u(matrixIJ.x, matrixIJ.y));
			if ((*it).sp.getPosition() == curTile.sp.getPosition()) {
				curTile.containedPiece = std::move(_selectedPiece->containedPiece);
				curTile.containedPiece->setFigurePos((*_field.getTile(sf::Vector2u(matrixIJ.x, matrixIJ.y))).sp.getPosition());
			}
		}
		_selectedTiles.clear();
		_selectedPiece = nullptr;
		return true;
	}
	return false;
}

bool Play_field::ifNoPieceSelected(sf::Vector2i matrixIJ) {
	if (_field.isTileContainsPiece(sf::Vector2u(matrixIJ.x, matrixIJ.y))) {
		_selectedPiece = _field.getTile(sf::Vector2u(matrixIJ.x, matrixIJ.y));
		_selectedPiece->containedPiece->canMove(_settings.selectColor, sf::Vector2u(matrixIJ.y, matrixIJ.x), _selectedTiles);
		return true;
	}
	return false;
}

void Play_field::spawnPawns(Team spawnBlack, int& yPos, bool& isNextWhite) {
	int xPos = 0;
	_field.AddRow(std::vector<Tile>(8));
	for (int i = 0; i < 8; i++, isNextWhite = !isNextWhite, xPos += _tileSize.x) {
		Tile& curTile = _field.createTile(sf::Vector2u(i, yPos / _tileSize.y), TileInitParams{ sf::Vector2f(xPos, yPos),
			isNextWhite ? _settings.whiteCol : _settings.blackCol,
			isNextWhite ? whiteTileTexture : blackTileTexture });
		sf::Vector2f pos = curTile.sp.getPosition();
		curTile.containedPiece = (std::make_unique<playPieces::Pawn>(static_cast<bool>(spawnBlack), _field, pos));
	}
	isNextWhite = !isNextWhite;
	yPos += _tileSize.y;
}

void Play_field::spawnRetinue(Team spawnBlack, int& yPos, bool& isNextWhite) {
	int xPos = 0;
	_field.AddRow(std::vector<Tile>(8));
	for (int i = 0; i < _spawnOrder.size(); i++, isNextWhite = !isNextWhite, xPos += _tileSize.x) {
		_field.createTile(sf::Vector2u(i, yPos / _tileSize.y), TileInitParams{ sf::Vector2f(xPos, yPos),
			isNextWhite ? _settings.whiteCol : _settings.blackCol,
			isNextWhite ? whiteTileTexture : blackTileTexture });
		createPieceInTile(i, spawnBlack);
	}
	isNextWhite = !isNextWhite;
	yPos += _tileSize.y;
}

void Play_field::createPieceInTile(int spawnOrderIndex, Team team) {
	auto& refToVec = *_field.lastRow();
	switch (_spawnOrder[spawnOrderIndex]) {
	case Castle:
		refToVec[spawnOrderIndex].PlaceGameObject(std::make_unique<playPieces::Castle>(static_cast<bool>(team), _field, refToVec[spawnOrderIndex].sp.getPosition()));
		break;
	case Bishop:
		refToVec[spawnOrderIndex].PlaceGameObject(std::make_unique<playPieces::Bishop>(static_cast<bool>(team), _field, refToVec[spawnOrderIndex].sp.getPosition()));
		break;
	case Horse:
		refToVec[spawnOrderIndex].PlaceGameObject(std::make_unique<playPieces::Horse>(static_cast<bool>(team), _field, refToVec[spawnOrderIndex].sp.getPosition()));
		break;
	case Queen:
		refToVec[spawnOrderIndex].PlaceGameObject(std::make_unique<playPieces::Queen>(static_cast<bool>(team), _field, refToVec[spawnOrderIndex].sp.getPosition()));
		break;
	case King:
		refToVec[spawnOrderIndex].PlaceGameObject(std::make_unique<playPieces::King>(static_cast<bool>(team), _field, refToVec[spawnOrderIndex].sp.getPosition()));
		break;
	}
}

void Play_field::toNormalColor() {
	for (auto i : _selectedTiles)
		i->curColor = i->defaultColor;
}