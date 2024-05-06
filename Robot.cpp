#include <algorithm>
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

void Robot::update(sf::RenderWindow& window, const sf::Event& event) {
	saveLastPosition();
    if (controlScheme == 'A') {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) moveUp();
            if (event.key.code == sf::Keyboard::Down) moveDown();
            if (event.key.code == sf::Keyboard::Left) moveLeft();
            if (event.key.code == sf::Keyboard::Right) moveRight();
        }
    } else if (controlScheme == 'B') {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Z) moveUp();
            if (event.key.code == sf::Keyboard::S) moveDown();
            if (event.key.code == sf::Keyboard::Q) moveLeft();
            if (event.key.code == sf::Keyboard::D) moveRight();
        }
    }
}

void Robot::handleCollision(Robot& other) {
    if (this->getX() < other.getX() + 50 && this->getX() + 50 > other.getX() &&
        this->getY() < other.getY() + 50 && this->getY() + 50 > other.getY()) {
        revertToLastPosition(); // Revenir à la dernière position sûre
        other.revertToLastPosition();
    }
}

void Robot::draw(sf::RenderWindow& window) {
    sf::RectangleShape shape(sf::Vector2f(50.0f, 50.0f));  // La taille devrait être un membre de la classe Robot
    shape.setPosition(posX, posY);
    shape.setFillColor(color);  // La couleur pourrait aussi être un attribut de Robot
    window.draw(shape);
}