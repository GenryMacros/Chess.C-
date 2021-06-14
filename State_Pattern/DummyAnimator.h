#pragma once
#include "IAnimator.h"

class DummyAnimator : public IAnimator {
public:
	virtual void Animate() override {};
	virtual void ChangeAnimation(sf::Event&) override {};
	virtual void ChangeAnimation() override {};
	virtual std::unique_ptr<IAnimator> Clone() override { return std::make_unique<DummyAnimator>(); };
	virtual void SetTarget(sf::Sprite*) override {};
};