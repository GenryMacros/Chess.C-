#include "FadingAnimator.h"



	void FadingAnimator::SetTarget(sf::Sprite* target)  {
		_target = target;
	}

	std::unique_ptr<IAnimator> FadingAnimator::Clone() {
		std::unique_ptr<FadingAnimator> clone = std::make_unique<FadingAnimator>();
		clone->_base = _base;
		clone->_active = _active;
		clone->colorChangeSpeed = colorChangeSpeed;

		return clone;
	};
	void FadingAnimator::ChangeAnimation()  {
		currentState = isFading() ? AnimationStates::Fading : AnimationStates::NONE;
		return;
	}
	void FadingAnimator::ChangeAnimation(sf::Event& event)  {
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			currentState = AnimationStates::Clicked;
			break;
		case sf::Event::MouseMoved:
			currentState = AnimationStates::Hover;
			break;
		default:
			currentState = isFading() ? AnimationStates::Fading : AnimationStates::NONE;
			break;
		}
	};
	bool FadingAnimator::isFading() {
		if (_target->getColor() == _base)
			return false;
		return true;
	}
	void FadingAnimator::Animate()  {
		if (_target == nullptr)
			throw std::exception("No target");

		switch (currentState)
		{
		case AnimationStates::NONE:
			break;
		case AnimationStates::Hover:
			Hover();
			break;
		case AnimationStates::Fading:
			Fading();
			break;
		case AnimationStates::Clicked:
			Clicked();
			break;
		default:
			break;
		}
	};

	bool isZero(sf::Color verifiable) {
		return !(verifiable.r != 0 && verifiable.g != 0 && verifiable.b != 0);
	}
	bool is255(sf::Color verifiable) {
		return !(verifiable.r != 255 && verifiable.g != 255 && verifiable.b != 255);
	}

	void FadingAnimator::Hover() {
		sf::Color currentTragetColor = _target->getColor();
		if ((currentTragetColor.r >= _active.r && currentTragetColor.g >= _active.g && currentTragetColor.b >= _active.b) || is255(currentTragetColor))
			return;
		currentTragetColor.r += currentTragetColor.r >= _active.r ? 0 : colorChangeSpeed;
		currentTragetColor.g += currentTragetColor.g >= _active.g ? 0 : colorChangeSpeed;
		currentTragetColor.b += currentTragetColor.b >= _active.b ? 0 : colorChangeSpeed;
		_target->setColor(currentTragetColor);
	}

	void FadingAnimator::Fading() {
		sf::Color currentTragetColor = _target->getColor();
		if ((currentTragetColor.r <= _base.r && currentTragetColor.g <= _base.g && currentTragetColor.b <= _base.b) || isZero(currentTragetColor))
			return;
		currentTragetColor.r -= currentTragetColor.r <= _base.r ? 0 : colorChangeSpeed;
		currentTragetColor.g -= currentTragetColor.g <= _base.g ? 0 : colorChangeSpeed;
		currentTragetColor.b -= currentTragetColor.b <= _base.b ? 0 : colorChangeSpeed;
		_target->setColor(currentTragetColor);
	}

	void FadingAnimator::Clicked() {
		sf::Color currentTragetColor = _target->getColor();
		if ((currentTragetColor.r >= _active.r && currentTragetColor.g >= _active.g && currentTragetColor.b >= _active.b) || is255(currentTragetColor))
			return;
		currentTragetColor.r += currentTragetColor.r >= _active.r ? 0 : colorChangeSpeed * 2;
		currentTragetColor.g += currentTragetColor.g >= _active.g ? 0 : colorChangeSpeed * 2;
		currentTragetColor.b += currentTragetColor.b >= _active.b ? 0 : colorChangeSpeed * 2;
		_target->setColor(currentTragetColor);
	}