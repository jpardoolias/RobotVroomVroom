#include <SFML/Graphics.hpp>
#include "Robot.hpp"
#include "arene.hpp"
#include <iostream>
#include "bonus.hpp"


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Robot and Hexagon Arena");
    sf::Clock clock;
    const sf::Time timePerMove = sf::milliseconds(100);  // Définir l'intervalle de mise à jour

    // Création des robots
    Robot robot1(400, 300, 100, 5, 20, 10, 'A', sf::Color::Red);
    Robot robot2(200, 300, 100, 5, 15, 10, 'B', sf::Color::Blue);
    Hexagone hexagon(window.getSize().x, window.getSize().y);
	Bonus bonus(hexagon);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (clock.getElapsedTime() >= timePerMove) {
            // Mettre à jour les mouvements des robots seulement quand l'intervalle de temps est atteint
            robot1.update(window);
            robot2.update(window);

            // Vérification des collisions entre les robots
            robot1.handleCollision(robot2);
            robot2.handleCollision(robot1);

            clock.restart();  // Redémarrer l'horloge après chaque mise à jour
        }

        window.clear(sf::Color::White);
        hexagon.drawHexagon(window, sf::Color::Green); 
		bonus.drawBonus(window); // Dessiner l'hexagone
        robot1.draw(window);  // Dessiner le premier robot
        robot2.draw(window);  // Dessiner le deuxième robot
        window.display();
    }

    return 0;
}
