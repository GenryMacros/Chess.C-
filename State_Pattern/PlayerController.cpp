#include "PlayerController.h"


std::optional<MoveCoords> PlayerController::MakeTurn(sf::Vector2i mouseCoord, TilesHolder& holder) {
	switch (currentTurn) {
	case Turns::FirstPlayerTurn:
		return _firstPlayer->HandleClick(mouseCoord, holder, _secondPlayer->GetControllerObjects());
	case Turns::SecondPlayerTurn:
		return _secondPlayer->HandleClick(mouseCoord, holder, _firstPlayer->GetControllerObjects());
	}
}
void PlayerController::SetPlayerOneGameObjs(std::list<Tile*>* objects) {
	_firstPlayer->SetControllableObjects(objects);
}
void PlayerController::SetPlayerTwoGameObjs(std::list<Tile*>* objects) {
	_secondPlayer->SetControllableObjects(objects);
}
std::list<Tile*>* PlayerController::GetCurrentPlayerObjects() {
	switch (currentTurn)
	{
	case Turns::FirstPlayerTurn:
		return _firstPlayer->GetControllerObjects();
	case Turns::SecondPlayerTurn:
		return _secondPlayer->GetControllerObjects();
	}
}
std::list<Tile*>* PlayerController::GetCurrentPlayerEnemyObjects() {
	switch (currentTurn)
	{
	case Turns::FirstPlayerTurn:
		return _secondPlayer->GetControllerObjects();
	case Turns::SecondPlayerTurn:
		return _firstPlayer->GetControllerObjects();
	}
}
void PlayerController::PassTurn() {
	switch (currentTurn)
	{
	case Turns::FirstPlayerTurn:
		currentTurn = Turns::SecondPlayerTurn;
		break;
	case Turns::SecondPlayerTurn:
		currentTurn = Turns::FirstPlayerTurn;
		break;
	}
}
int PlayerController::GetCurrentPlayer() {
	return (int)currentTurn;
}
std::list<Tile*> PlayerController::GetCurrentPossibleMoves(TilesHolder& holder) {
	switch (currentTurn)
	{
	case Turns::FirstPlayerTurn:
		return _firstPlayer->GetPossibleMoves(holder);
	case Turns::SecondPlayerTurn:
		return _secondPlayer->GetPossibleMoves(holder);
	}
}
std::list<Tile*> PlayerController::GetToCurrentEnemyPossibleMoves(TilesHolder& holder) {
	switch (currentTurn)
	{
	case Turns::FirstPlayerTurn:
		return _secondPlayer->GetPossibleMoves(holder);
	case Turns::SecondPlayerTurn:
		return _firstPlayer->GetPossibleMoves(holder);
	}
}
void PlayerController::Reset() {
	currentTurn = Turns::FirstPlayerTurn;
	_firstPlayer->Reset();
	_secondPlayer->Reset();
}
sf::Color PlayerController::GetPlayerSelectColor(int player) {
	Turns corplayer = (Turns)player;
	switch (corplayer)
	{
	case Turns::FirstPlayerTurn:
		return _firstPlayer->GetColor();
	case Turns::SecondPlayerTurn:
		return _secondPlayer->GetColor();
	}
}