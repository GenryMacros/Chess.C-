#pragma once
#include <list>
#include <vector>
#include <stdexcept>
#include <limits>
#include "Pawn.h";
#include "Castle.h"
#include "Horse.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

enum class Team {
	WHITE,
	BLACK
};

struct ChessFieldInfo {
	std::list<Tile*> whiteTiles;
	std::list<Tile*> blackTiles;
	sf::Vector2u whiteKingPos;
	sf::Vector2u blackKingPos;
};

class ChessFieldGenerator{
private:
	sf::Color whiteColor = sf::Color(200, 200, 200);
	sf::Color blackColor = sf::Color(150, 150, 150);
	std::vector<Pieces> _spawnOrder = {
		Pieces::Castle  , Pieces::Horse ,Pieces::Bishop,
		 Pieces::King,Pieces::Queen ,Pieces::Bishop,
		Pieces::Horse , Pieces::Castle };
	ChessFieldInfo returnedParams;
public:
	ChessFieldInfo PrepareForGame(TilesHolder& holder);
private:
	void ArrangeFigures(Team spawnBlack, int& yPos, bool& isnextWhite, TilesHolder& holder);
	void PaintTilesBetweenTeams(int& yPos, bool& isNextWhite, TilesHolder& holder);
	std::list<Tile*> ArrangePawns(Team spawnBlack, int& yPos, bool& isNextWhite, TilesHolder& holder);
	std::list<Tile*> ArrangeRetinue(Team spawnBlack, int& yPos, bool& isNextWhite, TilesHolder& holder);
	void PutPieceInTile(int spawnOrderIndex, Team team, Tile* tile, sf::Vector2u pieceGameCoords);
};