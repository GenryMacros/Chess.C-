#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "GameObject.h"
class Piece;

#define bCastle_Path "../Black_Figures/castle.png"
#define bBishop_Path "../Black_Figures/bishop.png"
#define bHorse_Path "../Black_Figures/horse.png"
#define bKing_Path "../Black_Figures/king.png"
#define bPawn_Path "../Black_Figures/pawn.png"
#define bQueen_Path "../Black_Figures/queen.png"

#define wCastle_Path "../White_Figures/castle.png"
#define wBishop_Path "../White_Figures/bishop.png"
#define wHorse_Path "../White_Figures/horse.png"
#define wKing_Path "../White_Figures/king.png"
#define wPawn_Path "../White_Figures/pawn.png"
#define wQueen_Path "../White_Figures/queen.png"

enum Pieces {
	Castle,
	Bishop,
	Horse,
	Queen,
	King,
	Pawn
};

enum XMovement {
	Right=1,
	Left=-1
};

enum YMovement {
	Up=1,
	Down=-1
};

struct Appearence {
	sf::Image im;
	sf::Texture tex;
	sf::Sprite sp;
};
namespace playPieces {
	class Piece : public GameObject {
	protected:
		sf::Vector2u _home;
		bool _isBlack;
	public:
		Piece(bool isBlack, sf::Vector2u home) :
			_isBlack(isBlack), _home(home) {}

		virtual void SelectTiles(sf::Vector2u posIn_field, std::list<Tile*>& selectArr, TilesHolder& holder) = 0;
		bool isBlack() {
			return _isBlack;
		}
	};
}

