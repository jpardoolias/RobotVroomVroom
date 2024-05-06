#include <algorithm>
#include <cmath>
#include "Robot.hpp"

// Constructeur
Robot::Robot(float x, float y, int health, float speed, int attackPower, int defense,char controlScheme, sf::Color color)
    : posX(x), posY(y), health(health), speed(speed), attackPower(attackPower), defense(defense), controlScheme(controlScheme), color(color){}

// Destructeur

Robot::~Robot() {}

void Robot::setPosition(float x, float y) {
    posX = x;
    posY = y;
}

// Getters
float Robot::getX() const {
    return posX;
}

float Robot::getY() const {
    return posY;
}

int Robot::getHealth() const {
    return health;
}

float Robot::getSpeed() const {
    return speed;
}

// Setters
void Robot::setHealth(int newHealth) {
    health = newHealth;
}

void Robot::moveUp() {
    posY = std::max(0.0f, posY - speed);
}

void Robot::moveDown() {
    posY = std::min(600.0f, posY + speed);
}

void Robot::moveLeft() {
    posX = std::max(0.0f, posX - speed);
}

void Robot::moveRight() {
    posX = std::min(600.0f, posX + speed);
}

void Robot::update(sf::RenderWindow& window) {
    if (controlScheme == 'A') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) moveDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) moveRight();
    } else if (controlScheme == 'B') {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) moveDown();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) moveLeft();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) moveRight();
    }
}

void Robot::handleCollision(Robot& other) {
    if (this->getX() < other.getX() + 50 && this->getX() + 50 > other.getX() &&
        this->getY() < other.getY() + 50 && this->getY() + 50 > other.getY()) {

        // Calcul de la direction de recul
        float deltaX = posX - other.posX;
        float deltaY = posY - other.posY;
        float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

        // Normalisation du vecteur de recul
        if (distance != 0) {
            deltaX /= distance;
            deltaY /= distance;
        }

        // Appliquer un léger recul
        float recul = 5.0f; // Vous pouvez ajuster ce paramètre selon le besoin
        posX += deltaX * recul;
        posY += deltaY * recul;
        other.posX -= deltaX * recul;
        other.posY -= deltaY * recul;

        // Vérifier les limites de la fenêtre pour chaque robot
        posX = std::min(std::max(0.0f, posX), 800.0f - 50.0f); // Largeur de fenêtre moins largeur de robot
        posY = std::min(std::max(0.0f, posY), 600.0f - 50.0f); // Hauteur de fenêtre moins hauteur de robot
        other.posX = std::min(std::max(0.0f, other.posX), 800.0f - 50.0f);
        other.posY = std::min(std::max(0.0f, other.posY), 600.0f - 50.0f);
    }
}


void Robot::draw(sf::RenderWindow& window) {
    sf::RectangleShape shape(sf::Vector2f(50.0f, 50.0f));  // La taille devrait être un membre de la classe Robot
    shape.setPosition(posX, posY);
    shape.setFillColor(color);  // La couleur pourrait aussi être un attribut de Robot
    window.draw(shape);
}