// Checkers.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Test");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    sf::Event e;


    //Creating shape
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(100, 100));


    //Start position
    sf::Vector2f rectPosition(400, 400);


    //Texture
    sf::Texture dvdtexture;
    dvdtexture.loadFromFile("pngegg.png");
    rect.setTexture(&dvdtexture);


    float xVelocity = 3;
    float yVelocity = 3;

    while (window.isOpen())
    {
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        //Phys
        rectPosition.x += xVelocity;
        rectPosition.y += yVelocity;
        
        rect.setPosition(rectPosition);

        if (rectPosition.x < 0 || rectPosition.x > 1280 - 100) xVelocity *= -1;
        if (rectPosition.y < 0 || rectPosition.y > 720 - 100) yVelocity *= -1;


        //Render
        window.clear();
        window.draw(rect);
        window.display();

    }
}
