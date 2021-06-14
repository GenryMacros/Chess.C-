#pragma once
class Tile;
#include "SFML/Graphics.hpp"
#include "GameObject.h"

struct TileInitParams {
	sf::Vector2f size;
	sf::Color color;
};

class Tile {
protected:
	sf::Image im;
	sf::Texture tex;
	sf::Sprite sp;
	sf::Vector2u gameObjectCoords;
	sf::Color startColor;
	std::unique_ptr<GameObject> _gameObject = nullptr;
public:
	Tile() = default;
	void Draw(sf::RenderWindow& win);
	void Create(sf::Vector2f size, sf::Vector2f coords);
	sf::Vector2f GetPosition();
	void PlaceGameObject(std::unique_ptr<GameObject> piece);
	bool IsContainingGameObject();
	GameObject* GetGameObject();
	void SetColor(sf::Color color);
	sf::Vector2u GetGameCoords();
	void SetGameCoords(sf::Vector2u gameCoords);
	bool IsGivenCoordInTile(sf::Vector2i coord);
	GameObject* PlaceGameObjectFromAnotherTile(Tile* anotherTile);
	sf::Color GetStartColor();
	void ResetImageWithColor(sf::Color color);
	void ClearSpriteColor();
	void SwapGameObejcts(Tile& swapWith);
	std::unique_ptr<GameObject> ReplaceGameObj(Tile& newobj);
	void DestroyGameObject();
};