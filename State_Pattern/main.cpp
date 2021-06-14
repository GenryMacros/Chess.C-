#include "SFML/Graphics.hpp"
#include "MainMenuState.h"
#include "App.h"

using namespace std;
int main() {
    sf::Vector2u winSize(1250, 1000);
	sf::RenderWindow win(sf::VideoMode(winSize.x, winSize.y),"State");
    win.setFramerateLimit(60);
    App app(winSize);
    app.ChangeState(make_unique<MainMenuState>(&app, winSize));
	while (win.isOpen()) {
        win.clear();
        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) win.close();
            sf::Vector2i mousePos = sf::Mouse::getPosition(win);
            app.HandleEvents(event, mousePos);
        }
        app.Draw(win);
	}

}