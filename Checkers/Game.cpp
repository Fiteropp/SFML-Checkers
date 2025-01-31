#include "Game.h"
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include "Saves.h"
#include <iostream>
#include <iomanip>

#define DEBUG // Comment this out to disable debug mode


//Reset button
sf::Texture resetButtonTexture;
sf::Sprite restartButtonSprite;

//Play Button in menu
sf::Texture playbtnTexture;
sf::Sprite playBtnSprite;

//Logo in menu
sf::Texture logoTexture;
sf::Sprite logoTextureSprite;

//Exit button in menu
sf::Texture menuGameExitTexture;
sf::Sprite menuGameExitSprite;

//CurrentPlayer Frame
sf::Texture currentPlayerFrameTexture;
sf::Sprite currentPlayerFrameSprite;

//Victory texture on winner screen
sf::Texture victoryTextTexture;
sf::Sprite victoryTextSprite;

//Winner text
sf::Texture winnerTextTexture;
sf::Sprite winnerTextSprite;

//Close button
sf::Texture closeVictoryScreenBtnTexture;
sf::Sprite  closeVictoryScreenBtnSprite;

//Close stats button
sf::Texture closeStatsScreenBtnTexture;
sf::Sprite  closeStatsScreenBtnSprite;

//Black checker
sf::Texture playerWinnerTextureBlack;
sf::Sprite playerWinnerSpriteBlack;

//White checker
sf::Texture playerWinnerTextureWhite;
sf::Sprite playerWinnerSpriteWhite;

//Stats button
sf::Texture statsButtonTexture;
sf::Sprite statsButtonSprite;

sf::Font font;

//Text
sf::Text whiteWins;
sf::Text blackWins;
sf::Text whiteMoves;
sf::Text blackMoves;
sf::Text whiteWinPercent;
sf::Text blackWinPercent;
sf::Text winsText;
sf::Text movesText;
sf::Text winPercentText;


Game::Game()
    : window(sf::VideoMode(800, 600), "C++ Checkers", sf::Style::Titlebar | sf::Style::Close),
    currentPlayer(Piece::Type::WHITE), isGameOver(false),
    board(this), victoryScreenVisible(false) {  // debug variable frog win screen

    board.loadTextures();

    InitializeUI();
    loadButtonsTextures();
    LoadFont();
}

void Game::LoadFont()
{
    if (!font.loadFromFile("pixel-font/slkscr.ttf")) {
        std::cout << ("Failed to load font: pixel-font/slkscr.ttf");
    }
    else {
        std::cout << ("Font loaded successfully\n ");
    }
}

void Game::InitializeUI()
{
    menuBackground.setSize(sf::Vector2f(800, 600));
    menuBackground.setFillColor(sf::Color(0, 128, 111, 255));

    winScreenBackground.setSize(sf::Vector2f(800, 180));
    winScreenBackground.setFillColor(sf::Color(116, 123, 123, 220));
    winScreenBackground.setPosition(0, 240);

	statsBackground.setSize(sf::Vector2f(800, 600));
	statsBackground.setFillColor(sf::Color(0, 128, 111, 255));
}




bool Game::loadTexture(const std::string& filePath, sf::Texture& texture) {
    if (!texture.loadFromFile(filePath)) {
#ifdef DEBUG
        std::cerr << "Failed to load texture " << filePath << std::endl;
#endif
        return false; 
    }
#ifdef DEBUG
#endif
    return true; 
}

void Game::configureSprite(sf::Sprite& sprite, sf::Texture& texture,
    sf::Vector2f position,
    sf::Vector2f scale) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(scale);
}

void Game::configureFontAndString(sf::Text& text, sf::Font& font,
    sf::Vector2f position,
    int scale,
    const sf::Color& color,
	int string
    ) {
	text.setFont(font);
    text.setPosition(position);
    text.setCharacterSize(scale);
	text.setFillColor(color);
	std::string str = std::to_string(string);
    text.setString(str);
}

void Game::configureFontAndText(sf::Text& text, sf::Font& font,
    sf::Vector2f position,
    int scale,
    const sf::Color& color,
    sf::String string
) {
    text.setFont(font);
    text.setPosition(position);
    text.setCharacterSize(scale);
    text.setFillColor(color);
    text.setString(string);
}



void Game::loadButtonsTextures()
{

    if (loadTexture("textures/exit_btn.png", menuGameExitTexture)) {
        configureSprite(menuGameExitSprite, menuGameExitTexture);
    }

    // logo texture
    if (loadTexture("textures/logo.png", logoTexture)) {
        configureSprite(logoTextureSprite, logoTexture);
    }

    // play button texture
    if (loadTexture("textures/play_btn.png", playbtnTexture)) {
        configureSprite(playBtnSprite, playbtnTexture, { 267, 230 }, { 5.5f, 5.5f });
    }

    // restart button texture
    if (loadTexture("textures/restart_btn.png", resetButtonTexture)) {
        configureSprite(restartButtonSprite, resetButtonTexture, { 610, 20 }, { 2.25f, 2.25f });
    }

    // current player frame
    if (loadTexture("textures/current_player_frame.png", currentPlayerFrameTexture)) {
        configureSprite(currentPlayerFrameSprite, currentPlayerFrameTexture, { 630, 200 }, { 2.0f, 2.0f });
    }

    // victory text texture
    if (loadTexture("textures/victory_text.png", victoryTextTexture)) {
        configureSprite(victoryTextSprite, victoryTextTexture, { 80, 20 }, { 1.0f, 1.0f });
    }

    // winner text texture
    if (loadTexture("textures/winner_text.png", winnerTextTexture)) {
        configureSprite(winnerTextSprite, winnerTextTexture, { 180, 270 }, { 1.0f, 1.0f });
    }
    
    // close button
    if (loadTexture("textures/close_btn.png", closeVictoryScreenBtnTexture)) {
        configureSprite(closeVictoryScreenBtnSprite, closeVictoryScreenBtnTexture, { 350, 370 }, { 1.5f, 1.5f });
    }

    // close button
    if (loadTexture("textures/close_btn.png", closeStatsScreenBtnTexture)) {
        configureSprite(closeStatsScreenBtnSprite, closeStatsScreenBtnTexture, { 360, 30 }, { 2.0f, 2.0f });
    }

	// stats button
    if (loadTexture("textures/stats_btn.png", statsButtonTexture)) {
        configureSprite(statsButtonSprite, statsButtonTexture, { 335, 500 }, { 2.3f, 2.3f });
    }

    // white checker texture
    if (loadTexture("textures/white_king.png", playerWinnerTextureWhite)) {
        configureSprite(playerWinnerSpriteWhite, playerWinnerTextureWhite, { 85, 270 }, { 5.0f, 5.0f });
    }

    // black checker texture
    if (loadTexture("textures/black_king.png", playerWinnerTextureBlack)) {
        configureSprite(playerWinnerSpriteBlack, playerWinnerTextureBlack, { 85, 270 }, { 5.0f, 5.0f });
    }

    
    
    loadIcon();
}

void Game::loadIcon()
{
    //loadIcon
    auto appIcon = sf::Image{};
    if (!appIcon.loadFromFile("textures/icon.png"))
    {
        std::cerr << "Failed to load Icon " << std::endl;
    }

    window.setIcon(appIcon.getSize().x, appIcon.getSize().y, appIcon.getPixelsPtr());
}

void Game::hideMenu() {
    isMenuVisible = false;  
	areStatsVisible = false;
}

void Game::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int mouseX = event.mouseButton.x;
            int mouseY = event.mouseButton.y;

            const float tileSize = 75;

            int gridX = mouseX / tileSize; 
            int gridY = mouseY / tileSize;

            board.handleClick(gridX, gridY, currentPlayer);  

            HandleButtonClicks(mouseX, mouseY);
        }
    }
}

void Game::HandleButtonClicks(int mouseX, int mouseY)
{
    if (restartButtonSprite.getGlobalBounds().contains(mouseX, mouseY)) {
        restartGame();
    }

    if (playBtnSprite.getGlobalBounds().contains(mouseX, mouseY)) {
        hideMenu();
    }

    if (closeVictoryScreenBtnSprite.getGlobalBounds().contains(mouseX, mouseY) && victoryScreenVisible) {
        restartGame();
    }

    if (closeStatsScreenBtnSprite.getGlobalBounds().contains(mouseX, mouseY)) {
		areStatsVisible = false;
    }

    if (statsButtonSprite.getGlobalBounds().contains(mouseX, mouseY)) {
        loadStats();
    }

    if (menuGameExitSprite.getGlobalBounds().contains(mouseX, mouseY)) {
        std::cout << "Exit button clicked" << std::endl;
        stopGame();
    }
}

// Stop the game
void Game::stopGame() {
    isGameOver = true;
    if (window.isOpen()) {
        window.close();
    }

        GameStats stats(board.whitePieceWinsCounter, board.blackPieceWinsCounter, board.whitePieceMoveCounter, board.blackPieceMoveCounter);

        // Save Stats
        stats.saveStatsToFile("game_stats.dat");
   
}


void Game::restartGame() {
    std::cout << "Restarting Game" << std::endl;

    isGameOver = false;
    victoryScreenVisible = false;
    winRegistered = false;

    currentPlayer = Piece::Type::WHITE;
    board.initializeBoard();
}


void Game::update() {
    if (victoryScreenVisible) return; // Prevent multiple updates

    if (board.checkWinCondition(currentPlayer)) {
        victoryScreenVisible = true;
        
        if (!winRegistered) {
            if (currentPlayer == Piece::Type::BLACK) {
                board.blackPieceWinsCounter += 1;
            }
            else {
                board.whitePieceWinsCounter += 1;
            }
            winRegistered = true; // Mark win as counted
        }
        
    }
}


void Game::loadStats() {
   
    GameStats stats;
    
    stats.loadSaveFromFile("game_stats.dat");

    configureFontAndString(whiteMoves, font, { 230, 230 }, 30, sf::Color::Black, stats.WhiteMovesScore);
    configureFontAndString(blackMoves, font, { 520, 230 }, 30, sf::Color::Black, stats.BlackMovesScore);
    configureFontAndString(whiteWins, font, { 230, 330 }, 30, sf::Color::Black, stats.WhiteWinsScore);
    configureFontAndString(blackWins, font, { 520, 330 }, 30, sf::Color::Black, stats.BlackWinsScore);
	configureFontAndString(whiteWinPercent, font, { 230, 430 }, 30, sf::Color::Black, stats.WhiteWinPercent);
	configureFontAndString(blackWinPercent, font, { 520, 430 }, 30, sf::Color::Black, stats.BlackWinPercent);
	configureFontAndText(movesText, font, { 60, 230 }, 30, sf::Color(14, 12, 26), "Moves:");
    configureFontAndText(winsText, font, { 60, 330 }, 30, sf::Color(14, 12, 26), "Wins:");
	configureFontAndText(winPercentText, font, { 60, 430 }, 30, sf::Color(14, 12, 26), "Win %:");
	areStatsVisible = true;
}


void Game::run() {
    
    while (window.isOpen()) {
        processInput(); 
        update();       
        render();       
    }
}

void Game::render() {
    window.clear(sf::Color(0, 24, 30));   
    board.render(window);
    window.draw(restartButtonSprite);

    logoTextureSprite.setPosition(20, 25);
    logoTextureSprite.setScale(1.65f, 1.65f);

    menuGameExitSprite.setPosition(280, 370);
    menuGameExitSprite.setScale(5.0f, 5.0f);

    drawMenuAndUI();
    renderVictoryScreen();

    if (areStatsVisible && isMenuVisible) {
		window.draw(statsBackground);
		window.draw(winsText);
		window.draw(movesText);
		window.draw(winPercentText);
		window.draw(whiteWins);
		window.draw(blackWins);
		window.draw(whiteMoves);
		window.draw(blackMoves);
		window.draw(whiteWinPercent);
		window.draw(blackWinPercent);
        window.draw(playerWinnerSpriteBlack);
		playerWinnerSpriteBlack.setPosition(230, 100);
		window.draw(playerWinnerSpriteWhite);
		playerWinnerSpriteWhite.setPosition(520, 100);
		window.draw(closeStatsScreenBtnSprite);
    }
  
     window.display();
}

void Game::drawMenuAndUI()
{
    if (isMenuVisible) {
        window.draw(menuBackground);
        window.draw(playBtnSprite);
        window.draw(logoTextureSprite);
        window.draw(menuGameExitSprite);
        window.draw(statsButtonSprite);
    }
    else {
		areStatsVisible = true;
        menuGameExitSprite.setScale(2.0f, 2.0f);
        menuGameExitSprite.setPosition(650, 530);

        window.draw(menuGameExitSprite);
        window.draw(restartButtonSprite);
        window.draw(currentPlayerFrameSprite);
    }
}

void Game::renderVictoryScreen()
{
    if (victoryScreenVisible) {

        window.draw(winScreenBackground);
        window.draw(victoryTextSprite);
        window.draw(winnerTextSprite);
        window.draw(closeVictoryScreenBtnSprite);

        currentPlayer == Piece::Type::BLACK ? window.draw(playerWinnerSpriteWhite) : window.draw(playerWinnerSpriteBlack);
    };
}
