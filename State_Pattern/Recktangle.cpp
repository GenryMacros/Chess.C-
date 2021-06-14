#include "Recktangle.h"

	Recktangle::Recktangle(sf::Vector2i size, sf::Vector2f pos, sf::Color color, TextOptions textOptions) {
		im.create(size.x, size.y, sf::Color::White);
		tex.loadFromImage(im);
		sp.setTexture(tex);
		sp.setPosition(pos.x, pos.y);
		sp.setColor(color);
		_color = color;

		font.loadFromFile(textOptions.FontPath);
		text.setFont(font);
		text.setFillColor(textOptions.TextColor);
		text.setCharacterSize(textOptions.FontSize);
		setTextPos(im.getSize());
	};
	Recktangle::Recktangle(std::string pathToIm, sf::Vector2f pos, sf::Vector2f scale) {
		im.loadFromFile(pathToIm);
		tex.loadFromImage(im);
		sp.setTexture(tex);
		sp.setPosition(pos.x, pos.y);
		sp.setScale(scale);
	}
	void Recktangle::Draw(sf::RenderWindow& win)  {
		Animate();
		win.draw(sp);
		win.draw(text);
	};
	bool Recktangle::isContainsDot(sf::Vector2i mouseCoords)  {
		return sp.getGlobalBounds().contains(mouseCoords.x, mouseCoords.y);
	};
	std::unique_ptr<IUiElem> Recktangle::Clone()  {
		std::unique_ptr<Recktangle> clone = std::make_unique<Recktangle>();
		clone->im = im;
		clone->tex = tex;
		clone->sp = sp;
		clone->_color = _color;
		clone->text = text;
		clone->animator = animator->Clone();
		clone->animator->SetTarget(&clone->sp);
		return clone;
	};
	void Recktangle::Animate()  {
		if (!animator.get())
			return;

		animator->Animate();
	};
	void Recktangle::ChangeAnimation(sf::Event& event)  {
		if (!animator.get())
			return;
		animator->ChangeAnimation(event);
	};
	void Recktangle::ChangeAnimation()  {
		if (!animator.get())
			return;
		animator->ChangeAnimation();
	}
	 IUiElem* Recktangle::setTag(int newTag)  {
		Tag = newTag;
		return this;
	};
	IUiElem* Recktangle::setText(std::string newText)  {
		text.setString(newText);
		setTextPos(im.getSize());
		return this;
	};
	IUiElem* Recktangle::setPos(sf::Vector2f pos)  {
		sp.setPosition(pos.x, pos.y);
		setTextPos(im.getSize());
		return this;
	}
	void Recktangle::setTextPos(sf::Vector2u containerSize) {
		float textWidth = text.getLocalBounds().width;
		float indent = (containerSize.x - textWidth) / 2;
		text.setPosition(sp.getPosition().x + indent, sp.getPosition().y);
	}
	IUiElem* Recktangle::setAnimator(std::unique_ptr<IAnimator> newAnimator)  {
		animator = std::move(newAnimator);
		animator->SetTarget(&sp);
		return this;
	}