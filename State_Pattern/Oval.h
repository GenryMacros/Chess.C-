#pragma once
#include "SFML/Graphics.hpp"
#include "IUiElem.h"
#include "IAnimator.h"

class Oval : public IUiElem {
private:
	std::unique_ptr<IAnimator> animator;
	sf::Color _color;
	sf::Text text;
	int Tag = -1;

public:
	Oval() = default;
	Oval(sf::Vector2i size, sf::Vector2f pos, sf::Color color, TextOptions textOptions);
	virtual void Draw(sf::RenderWindow & win) override;
	virtual bool isContainsDot(sf::Vector2i mouseCoords) override;
	virtual std::unique_ptr<IUiElem> Clone() override;
	virtual void Animate() override;
	virtual void ChangeAnimation(sf::Event & event) override;
	virtual void ChangeAnimation() override;
	virtual IUiElem* setTag(int newTag) override;
	virtual IUiElem* setText(std::string newText) override;
	virtual IUiElem* setPos(sf::Vector2f pos) override;
	void setTextPos(sf::Vector2u containerSize);
	virtual IUiElem* setAnimator(std::unique_ptr<IAnimator> newAnimator) override;
};