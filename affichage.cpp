#include "affichage.hpp"

bool Affiche::menu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("Ecriture.ttf")) {
        // Gestion de l'erreur si le chargement de la police échoue
        return false;
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Robot and Hexagon Arena");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::White);
    title.setPosition(180, 50);

    sf::Text singlePlayerOption;
    singlePlayerOption.setFont(font);
    singlePlayerOption.setString("Jouer tout seul");
    singlePlayerOption.setCharacterSize(20);
    singlePlayerOption.setFillColor(sf::Color::White);
    singlePlayerOption.setPosition(300, 200);

    sf::Text multiPlayerOption;
    multiPlayerOption.setFont(font);
    multiPlayerOption.setString("Jouer a deux joueurs");
    multiPlayerOption.setCharacterSize(20);
    multiPlayerOption.setFillColor(sf::Color::White);
    multiPlayerOption.setPosition(275, 250);

    sf::Text goButton;
    goButton.setFont(font);
    goButton.setString("Go !");
    goButton.setCharacterSize(25);
    goButton.setFillColor(sf::Color::White);
    goButton.setPosition(350, 350);

	// Rectangle vert pour encadrer l'option sélectionnée
    sf::RectangleShape selectionRect(sf::Vector2f(singlePlayerOption.getLocalBounds().width + 60, singlePlayerOption.getLocalBounds().height + 20));
    selectionRect.setFillColor(sf::Color::Transparent);
    selectionRect.setOutlineThickness(2);
    selectionRect.setOutlineColor(sf::Color::Green);
    selectionRect.setPosition(singlePlayerOption.getPosition() - sf::Vector2f(27, 5)); // Déplacer le rectangle autour de l'option sélectionnée

    // Boucle principale du menu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false; // Retourne false si la fenêtre est fermée
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (singlePlayerOption.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour démarrer le jeu en mode un joueur
                    // Exemple : initialiser un seul robot
                    nbPlayers=1;
					selectionRect.setPosition(singlePlayerOption.getPosition() - sf::Vector2f(27, 5));
                } else if (multiPlayerOption.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour démarrer le jeu en mode deux joueurs
                    // Exemple : initialiser deux robots
                    nbPlayers=2;
					selectionRect.setPosition(singlePlayerOption.getPosition() - sf::Vector2f(27, -55));
            		
                } else if (goButton.getGlobalBounds().contains(mousePosition)) {
                    // Logique pour lancer le jeu après avoir choisi le mode de jeu
                    return true; // Retourne true pour démarrer le jeu
                }
            }
		
        }
		
        window.clear();
        window.draw(title);
		window.draw(selectionRect);
        window.draw(singlePlayerOption);
        window.draw(multiPlayerOption);
        window.draw(goButton);
        window.display();
    }
	fin=true;
    return false; // Retourne false par défaut
}


bool Affiche::refresh(sf::RenderWindow& window,sf::Time timePerMove,sf::Clock clock,sf::Event event){
        // Effacement de la fenêtre
        window.clear();
		while(window.isOpen()){
        // Dessin de l'arrière-plan
		while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if (clock.getElapsedTime() >= timePerMove) {
			if(nbPlayers==2){
				// Mettre à jour les mouvements des robots seulement quand l'intervalle de temps est atteint
				P1.update(window);
				P2.update(window);

				// Vérification des collisions entre les robots
				P1.handleCollision(P2);
				P2.handleCollision(P1);
				}
			else{
				// Mettre à jour les mouvements des robots seulement quand l'intervalle de temps est atteint
				P1.update(window);

				// Vérification des collisions entre les robots
				P1.handleCollision(P2);
			}
            clock.restart();  // Redémarrer l'horloge après chaque mise à jour
        }

		window.clear(sf::Color::White);
		window.draw(sprite);
        hexagon.drawHexagon(window, sf::Color::Green); 
        P1.draw(window);  // Dessiner le premier robot
		if(nbPlayers==2) P2.draw(window);  // Dessiner le deuxième robot
        window.display();
		return true;
		}
	return false;
}