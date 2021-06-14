#include "Tile.h"


void Tile::Draw(sf::RenderWindow& win) {
	win.draw(sp);
	if (_gameObject.get())
		_gameObject->Draw(win);
};
void Tile::Create(sf::Vector2f size, sf::Vector2f coords) {
	im.create(size.x, size.y, sf::Color::White);
	tex.loadFromImage(im);
	sp.setTexture(tex);
	sp.setPosition(coords);
}
sf::Vector2f Tile::GetPosition() {
	return sp.getPosition();
}
void Tile::PlaceGameObject(std::unique_ptr<GameObject> piece) {
	_gameObject = std::move(piece);
	if (_gameObject.get())
		_gameObject->SetPos(sp.getPosition());
}
bool Tile::IsContainingGameObject() {
	return _gameObject.get();
}
GameObject* Tile::GetGameObject() {
	return _gameObject.get();
}
void Tile::SetColor(sf::Color color) {
	sp.setColor(color);
}
sf::Vector2u Tile::GetGameCoords() {
	return gameObjectCoords;
}
void Tile::SetGameCoords(sf::Vector2u gameCoords) {
	gameObjectCoords = gameCoords;
}
bool Tile::IsGivenCoordInTile(sf::Vector2i coord) {
	return sp.getGlobalBounds().contains(coord.x, coord.y);
}
GameObject* Tile::PlaceGameObjectFromAnotherTile(Tile* anotherTile) {
	GameObject* returned = _gameObject.release();
	_gameObject = std::move(anotherTile->_gameObject);
	_gameObject->SetPos(sp.getPosition());
	return returned;
}
sf::Color Tile::GetStartColor() {
	return startColor;
}
void Tile::ResetImageWithColor(sf::Color color) {
	sf::Vector2u curSize = im.getSize();
	im.create(curSize.x, curSize.y, color);
	tex.loadFromImage(im);
	sp.setTexture(tex);
}
void Tile::ClearSpriteColor() {
	sp.setColor(sf::Color::White);
}
void Tile::SwapGameObejcts(Tile& swapWith) {
	std::unique_ptr<GameObject> thisGameObj = std::move(_gameObject);
	PlaceGameObject(std::move(swapWith._gameObject));
	swapWith.PlaceGameObject(std::move(thisGameObj));
}
std::unique_ptr<GameObject> Tile::ReplaceGameObj(Tile& newobj) {
	std::unique_ptr<GameObject> ret = std::move(newobj._gameObject);
	newobj.PlaceGameObject(std::move(_gameObject));
	return ret;
}
void Tile::DestroyGameObject() {
	_gameObject.reset();
}