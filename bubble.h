#ifndef BUBBLE_H
#define BUBBLE_H

#include <SFML/Graphics.hpp>

class Bubble {
    private:
        sf::CircleShape _bubble;
        double _xDir;
        double _yDir;
    public:
        Bubble();
        Bubble(int width, int height);
        void setXDir(const double NEWX);
        void setYDir(const double NEWY);
        void setColor(const sf::Color COLOR);
        double getXDir();
        double getYDir();
        sf::CircleShape getCircleShape();
        void draw(sf::RenderWindow& renderWindow);
        void updatePosition(int width, int height);
        bool checkClicked(double mouseX, double mouseY);
        bool checkPosition(int width, int height);
};

#endif