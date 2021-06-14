#pragma once
#include "SFML/Graphics.hpp"
#include "IAnimator.h"
#define DefaultFont "../Fonts/Sparkling Bright.ttf"

struct TextOptions {
	sf::Color TextColor = sf::Color::White;
	int FontSize = 20;
	std::string FontPath = DefaultFont;
};

class IUiElem {
protected:
	sf::Font font;
	sf::Image im;
	sf::Texture tex;
	sf::Sprite sp;
public:
	int Tag;

	virtual void Draw(sf::RenderWindow&) = 0;
	virtual bool isContainsDot(sf::Vector2i) = 0;
	virtual void Animate() = 0;
	virtual void ChangeAnimation(sf::Event& event) = 0;
	virtual void ChangeAnimation() = 0;
	virtual std::unique_ptr<IUiElem> Clone() = 0;
	virtual IUiElem* setTag(int) = 0;
	virtual IUiElem* setText(std::string) = 0;
	virtual IUiElem* setPos(sf::Vector2f) = 0;
	virtual IUiElem* setAnimator(std::unique_ptr<IAnimator>) = 0;
};