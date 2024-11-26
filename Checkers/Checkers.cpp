// Checkers.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "SFML/Graphics.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 720), "C+Checkers");
    sf::View view(sf::Vector2f(350, 300), sf::Vector2f(300, 200));
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);


    //Event
    sf::Event e;


    //Creating shape
    sf::RectangleShape rect(sf::Vector2f(400.f, 400.f));
    rect.setOrigin(rect.getSize().x / 2.f, rect.getSize().y / 2.f);


    auto centerShape = [&](sf::RectangleShape& shape, const sf::RenderWindow& win) {
        sf::Vector2u windowSize = win.getSize(); // Get the current size of the window
        shape.setPosition(windowSize.x / 2.f, windowSize.y / 2.f); // Set shape's position to the center
    };

    centerShape(rect, window);
    
    
    
    //Texture
    sf::Texture board;
    board.loadFromFile("board.png");
    rect.setTexture(&board);







    while (window.isOpen())
    {
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
            if (e.type == sf::Event::Resized) {
                
                sf::FloatRect visibleArea(0, 0, e.size.width, e.size.height);
                window.setView(sf::View(visibleArea));

                centerShape(rect, window);
                
             

            }

        }

        

        //Render
        window.clear(sf::Color{ 2, 60, 31 });
        window.draw(rect);
        window.display();

    }
}
