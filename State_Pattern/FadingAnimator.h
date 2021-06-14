#pragma once
#include "IAnimator.h"

class FadingAnimator : public IAnimator {
private:
	sf::Sprite* _target = nullptr;
	AnimationStates currentState = AnimationStates::NONE;
	sf::Color _base;
	sf::Color _active;
	float colorChangeSpeed = 3.0f;
public:
	FadingAnimator() = default;
	FadingAnimator(sf::Color base,sf::Color active) : 
		_base(base),_active(active){}

	virtual void SetTarget(sf::Sprite* target) override;
	virtual std::unique_ptr<IAnimator> Clone() override;
	virtual void ChangeAnimation() override;
	virtual void ChangeAnimation(sf::Event& event) override;
private:
	bool isFading();
public:
	virtual void Animate() override;
private:
	void Hover();
	void Fading();
	void Clicked();
};