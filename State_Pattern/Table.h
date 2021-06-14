#pragma once
class Table;
#include <vector>
#include <stdexcept>
#include <limits>
#include "SmartMatrix.h"
#include "Pawn.h";
#include "Castle.h"
#include "Horse.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
enum class Team {
	BLACK,
	WHITE
};

struct TableColor_settings {
	sf::Color blackCol = sf::Color(150, 150, 150);
	sf::Color whiteCol = sf::Color(200, 200, 200);
	sf::Color selectColor = sf::Color(215,150,215,100);
};

class Play_field {
private:
	sf::Texture blackTileTexture;
	sf::Texture whiteTileTexture;
	sf::Image blackTileImage;
	sf::Image whiteTileImage;

	std::vector<Pieces> _spawnOrder = {
		Pieces::Castle , Pieces::Bishop , Pieces::Horse ,
		Pieces::Queen ,  Pieces::King , Pieces::Horse ,
		Pieces::Bishop , Pieces::Castle };
	Tile* _selectedPiece = nullptr;
	std::vector<Tile*> _selectedTiles;
	TableColor_settings _settings;
	SmartMatrix _field;
	sf::Vector2u _tileSize;
public:

	Play_field(sf::Vector2u tileSize, TableColor_settings settings);
	void Draw(sf::RenderWindow& win);
	SmartMatrix& getTable();
	void handleClick(sf::Vector2i mousePos);

private:
	void CreateBoardTilesTextures();
	void spawnFigures(Team spawnBlack, int& yPos, bool& isnextWhite);
	void spawnSpaceBetweenTeams(int& yPos, bool& isNextWhite);
	bool isThisTileClicked(sf::Vector2i mousePos, sf::Vector2i matrixIJ);
	bool ifPieceSelected(sf::Vector2i matrixIJ);
	bool ifNoPieceSelected(sf::Vector2i matrixIJ);
	void spawnPawns(Team spawnBlack, int& yPos, bool& isNextWhite);
	void spawnRetinue(Team spawnBlack, int& yPos, bool& isNextWhite);
	void createPieceInTile(int spawnOrderIndex, Team team);
	void toNormalColor();
};
