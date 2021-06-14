#pragma once
#include "SFML/Graphics.hpp"

enum class AnimationStates {
	NONE,
	Hover,
	Fading,
	Clicked
};

class IAnimator {
public:
	virtual void Animate() = 0;
	virtual void ChangeAnimation(sf::Event&) = 0;
	virtual void ChangeAnimation() = 0;
	virtual std::unique_ptr<IAnimator> Clone() = 0;
	virtual void SetTarget(sf::Sprite*) = 0;
};