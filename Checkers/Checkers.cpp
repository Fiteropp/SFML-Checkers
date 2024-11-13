// Checkers.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 720), "C+Checkers");
    sf::View view = window.getDefaultView();
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Event e;


    //Creating shape
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(400.0f, 400.0f));



    //Start position
    rect.setPosition(160, 160);


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
                // resize my view
                view.setSize({
                        static_cast<float>(e.size.width),
                        static_cast<float>(e.size.height)
                    });
                window.setView(view);
            }



            //Render
            window.clear(sf::Color{ 2, 60, 31 });
            window.draw(rect);
            window.display();

        }
    }
}
