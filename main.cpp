#include <SFML/Graphics.hpp>
#include "Robot.hpp"
#include "arene.hpp"
#include <iostream>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Robot and Hexagon Arena");
    sf::Clock clock;
    const sf::Time timePerMove = sf::milliseconds(100);

    // Création des robots
    Robot robot1(400, 300, 100, 5, 20, 10, 'A', sf::Color::Red); // 'A' pour les flèches
    Robot robot2(200, 300, 100, 5, 15, 10, 'B', sf::Color::Blue); // 'B' pour ZQSD
    Hexagone hexagon(window.getSize().x, window.getSize().y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            robot1.update(window, event);
            robot2.update(window, event);
        }

        if (clock.getElapsedTime() > timePerMove) {
            clock.restart();
            // Vérification des collisions entre les robots
            robot1.handleCollision(robot2);
            robot2.handleCollision(robot1);
        }

        window.clear(sf::Color::White);
        hexagon.drawHexagon(window, sf::Color::Green);  // Dessiner l'hexagone
        robot1.draw(window);  // Dessiner le premier robot
        robot2.draw(window);  // Dessiner le deuxième robot
        window.display();
    }

    return 0;
}


