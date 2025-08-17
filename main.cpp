#include <SFML/Graphics.hpp>
using namespace sf;

#include <iostream>
using namespace std;

#include "bubble.h"
#include <vector>

int main() {

    Clock clock;

    // create a window
    RenderWindow window( VideoMode(2880, 1620), "Bounce"/* , Style::Fullscreen */);

    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    vector<Bubble*> bubbles;

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // create an event object once to store future events
    Event event;

    // while the window is open
    while( window.isOpen() ) {
        // clear any existing contents
        window.clear();

        /////////////////////////////////////
        // BEGIN DRAWING HERE
        for (size_t i = 0; i < bubbles.size(); i++) {
            bubbles.at(i)->draw(window);
        };

        //  END  DRAWING HERE
        /////////////////////////////////////


        // display the current contents of the window
        window.display();

        /////////////////////////////////////
        // BEGIN EVENT HANDLING HERE
        // check if any events happened since the last time checked
        while( window.pollEvent(event) ) {
            // if event type corresponds to pressing window X
            if(event.type == Event::Closed) {
                // tell the window to close
                window.close();
            }
            // check addition event types to handle additional events   
            if(event.type == event.KeyPressed) {
                if( Keyboard::isKeyPressed(Keyboard::Space)) {
                    bubbles.push_back(new Bubble(window.getSize().x, window.getSize().y));
                }
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    for (size_t i = 0; i < bubbles.size(); i++) {
                        bubbles.at(i)->setXDir(bubbles.at(i)->getXDir()*1.1);
                        bubbles.at(i)->setYDir(bubbles.at(i)->getYDir()*1.1);
                    }
                } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    for (size_t i = 0; i < bubbles.size(); i++) {
                        bubbles.at(i)->setXDir(bubbles.at(i)->getXDir()*0.9);
                        bubbles.at(i)->setYDir(bubbles.at(i)->getYDir()*0.9);
                    }
                }            }
            if(Mouse::isButtonPressed(Mouse::Left)) {
                Vector2i mousePos = Mouse::getPosition(window);
                for (size_t i = 0; i < bubbles.size(); i++) {
                    bool click = bubbles.at(i)->checkClicked(mousePos.x, mousePos.y);
                    if (click == true) {
                        Bubble* bubble = bubbles.at(i);
                        delete bubble;
                        bubbles.erase(bubbles.begin()+i);
                    }
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
        }
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////
        Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.02) {
            for (size_t i = 0; i < bubbles.size(); i++) {
                bubbles.at(i)->updatePosition(window.getSize().x, window.getSize().y);
                if (bubbles.at(i)->checkPosition(window.getSize().x, window.getSize().y)) {
                    bubbles.at(i)->setColor(Color(255,255,255));
                }
            }
            clock.restart();
        }
    }
    for (size_t i = 0; i < bubbles.size(); i++) {
        delete bubbles.at(i);
    }
    return 0;
}