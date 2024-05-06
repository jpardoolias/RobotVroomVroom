#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <SFML/Graphics.hpp>

class Robot {
public:
    // Constructeur
    Robot(float x, float y, int health, float speed, int attackPower, int defense, char controlScheme, sf::Color color);

    // Destructeur
    virtual ~Robot();

    // Fonctions de mouvement
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

	void setPosition(float x, float y);

	void saveLastPosition() {
        lastPosX = posX;
        lastPosY = posY;
    }

	void revertToLastPosition() {
        posX = lastPosX;
        posY = lastPosY;
    }

    // Getters et Setters
    float getX() const;
    float getY() const;
    int getHealth() const;
	float getSpeed() const;

    void setHealth(int newHealth);

	void update(sf::RenderWindow& window);
	void handleCollision(Robot& other);

	void draw(sf::RenderWindow& window);


protected:
    float posX, posY; // Position actuelle du robot
    int health;       // Santé actuelle du robot
    float speed;      // Vitesse de déplacement du robot
    int attackPower;  // Puissance d'attaque
    int defense;      // Capacité de défense
	float lastPosX, lastPosY;
	char controlScheme;  // 'A' pour les flèches, 'B' pour ZQSD
	sf::Color color;
};


#endif // ROBOT_HPP