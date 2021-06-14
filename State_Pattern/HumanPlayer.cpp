#include "HumanPlayer.h"

void HumanPlayer::SetControllableObjects(std::list<Tile*>* objects)  {
	_controlledObjects = objects;
}
std::optional<MoveCoords> HumanPlayer::HandleClick(sf::Vector2i mouseCoords, TilesHolder& holder, std::list<Tile*>* opponentControlledObjects)  {
	if (selectedTiles.empty()) {
		SelectTiles(mouseCoords, holder, *opponentControlledObjects);
		return std::optional<MoveCoords>();
	}
	else {
		std::optional<sf::Vector2u> newCoords = MakeTurn(mouseCoords, holder, *opponentControlledObjects);
		return newCoords.has_value() ? MoveCoords{ selectedTile->GetGameCoords(), newCoords.value() } : std::optional<MoveCoords>();
	}
}
void HumanPlayer::SelectTiles(sf::Vector2i mouseCoords, TilesHolder& holder, std::list<Tile*>& opponentControlledObjects) {
	for (Tile* tile : *_controlledObjects) {
		if (tile->IsGivenCoordInTile(mouseCoords)) {
			selectedTile = tile;
			playPieces::Piece* selectedPiece = dynamic_cast<playPieces::Piece*>(selectedTile->GetGameObject());
			selectedPiece->SelectTiles(tile->GetGameCoords(), selectedTiles, holder);
			PaintSelected();
		}
	}
}
void HumanPlayer::PaintSelected() {
	for (Tile* elem : selectedTiles)
		elem->SetColor(tileSelectColor);
}
std::optional<sf::Vector2u> HumanPlayer::MakeTurn(sf::Vector2i mouseCoords, TilesHolder& holder, std::list<Tile*>& opponentControlledObjects) {
	for (Tile* tile : selectedTiles) {
		if (tile->IsGivenCoordInTile(mouseCoords) && tile != selectedTile) {
			UnSelectTiles();
			return tile->GetGameCoords();
		}
	}
	UnSelectTiles();
	return std::optional<sf::Vector2u>();
};
void HumanPlayer::UnSelectTiles() {
	for (Tile* tile : selectedTiles)
		tile->ClearSpriteColor();
	selectedTiles.clear();
}
std::list<Tile*>* HumanPlayer::GetControllerObjects()  {
	return _controlledObjects;
}
std::list<Tile*> HumanPlayer::GetPossibleMoves(TilesHolder& holder)  {
	std::list<Tile*> possibleMoves;
	for (Tile* tile : *_controlledObjects) {
		tile->GetGameObject()->SelectTiles(tile->GetGameCoords(), possibleMoves, holder);
	}
	possibleMoves.erase(possibleMoves.begin());
	return possibleMoves;
}
sf::Color HumanPlayer::GetColor()  {
	return tileSelectColor;
}
void HumanPlayer::Reset()  {
	_controlledObjects = nullptr;
	selectedTile = nullptr;
	selectedTiles.clear();
}