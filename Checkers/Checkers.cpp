// Checkers.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "C+Checkers");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
   
    sf::Event e;


    //Creating shape
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(400.0f, 400.0f));



    //Start position
   rect.setPosition(440, 200);


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
        }

       

        //Render
        window.clear(sf::Color::White);
        window.draw(rect);
        window.display();

    }
    return 0;
}
