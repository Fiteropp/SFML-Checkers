#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Piece.h"
#include "Player.h"

class Game {
private:
        Board board;
    sf::RectangleShape menuBackground;
    sf::RectangleShape winScreenBackground;
	sf::RectangleShape DebugButton;
    sf::Sprite playBtnSprite;
    bool isMenuVisible = true;  
    bool victoryScreenVisible = false;
	bool areStatsVisible = true;
    bool isGameOver;
    bool winRegistered;
    

    bool loadTexture(const std::string& filePath, sf::Texture& texture);
    void configureSprite(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f position = { 0, 0 }, sf::Vector2f scale = { 1.0f, 1.0f });
    void configureFontAndString(sf::Text& text, sf::Font& font, sf::Vector2f position, int scale, const sf::Color& color, int string);
    void processInput();
    void HandleButtonClicks(int mouseX, int mouseY);
	void loadStats();
    void update();
    void render();
    void drawMenuAndUI();
    void renderVictoryScreen();
    void hideMenu();

public:
    sf::RenderWindow window;      

    Piece::Type currentPlayer;

    Game();
    void LoadFont();
    void InitializeUI();
    void loadButtonsTextures();
    void loadIcon();
    void run();
    void stopGame();  
    void restartGame();
};
