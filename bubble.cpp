#include "bubble.h"
#include <random>
#include <cmath>

std::random_device rd;
std::mt19937 mt( rd() );

Bubble::Bubble() {
    std::uniform_real_distribution<double> realDistDir(-0.1667, 0.1667); 
    double randXDir = realDistDir(mt);
    double randYDir = realDistDir(mt);
    
    _xDir = randXDir;
    _yDir = randYDir;

    std::uniform_int_distribution<int> intDist(50,100); 
    int randRadius = intDist(mt);

    _bubble.setRadius(randRadius);
    _bubble.setPosition(0.1, 0.1);

    std::uniform_int_distribution<int> intDistColor(0,255); 
    int randR = intDistColor(mt);
    int randG = intDistColor(mt);
    int randB = intDistColor(mt);
    _bubble.setFillColor(sf::Color(randR,randG,randB));
}

Bubble::Bubble(int width, int height) {
    std::uniform_real_distribution<double> realDistDir(-1, 1); 
    double randXDir = realDistDir(mt);
    double randYDir = realDistDir(mt);
    
    _xDir = randXDir;
    _yDir = randYDir;

    std::uniform_int_distribution<int> intDist(10,100); 
    int randRadius = intDist(mt);

    _bubble.setRadius(randRadius);

    std::uniform_real_distribution<double> realDistXPos(0,width-randRadius*2); 
    double randXPos = realDistXPos(mt);

    std::uniform_real_distribution<double> realDistYPos(0,height-randRadius*2); 
    double randYPos = realDistYPos(mt);

    _bubble.setPosition(randXPos, randYPos);

    std::uniform_int_distribution<int> intDistColor(0,255); 
    int randR = intDistColor(mt);
    int randG = intDistColor(mt);
    int randB = intDistColor(mt);
    _bubble.setFillColor(sf::Color(randR,randG,randB));
}

void Bubble::setXDir(const double NEWX) {
    _xDir = NEWX;
}

void Bubble::setYDir(const double NEWY) {
    _yDir = NEWY;
}

void Bubble::setColor(const sf::Color COLOR) {
    _bubble.setFillColor(COLOR);
}

double Bubble::getXDir() {
    return _xDir;
}

double Bubble::getYDir() {
    return _yDir;
}

sf::CircleShape Bubble::getCircleShape() {
    return _bubble;
}

void Bubble::draw(sf::RenderWindow& renderWindow) {
    renderWindow.draw(_bubble);
}

void Bubble::updatePosition(int width, int height) {
    sf::Vector2f coords = _bubble.getPosition();
    int diameter = _bubble.getRadius()*2;
    if ((coords.x >= width-diameter && _xDir > 0) || (coords.x <= 0 && _xDir < 0)) {
        _xDir = -_xDir;
    }
    if ((coords.y >= height-diameter && _yDir > 0) || (coords.y <= 0 && _yDir < 0)) {
        _yDir = -_yDir;
    } 
    _bubble.setPosition(coords.x +_xDir, coords.y +_yDir);
}

bool Bubble::checkClicked(double mouseX, double mouseY) {
    sf::Vector2f coords = _bubble.getPosition();
    double centerX = coords.x+_bubble.getRadius();
    double centerY = coords.y+_bubble.getRadius();
    double distance = sqrt(((mouseX-centerX)*(mouseX-centerX))+((mouseY-centerY)*(mouseY-centerY)));
    if (distance <= _bubble.getRadius()) {
        return true;
    } else {
        return false;
    }
}

bool Bubble::checkPosition(int width, int height) {
    sf::Vector2f coords = _bubble.getPosition();
    int diameter = _bubble.getRadius()*2;
    if (((coords.x >= width-diameter && _xDir > 0) || (coords.x <= 0 && _xDir < 0)) && ((coords.y >= height-diameter && _yDir > 0) || (coords.y <= 0 && _yDir < 0))) {
        return true;
    }
    return false;
}