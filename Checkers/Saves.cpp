#include "Saves.h"
#include <cstring> // For strncpy

// Constructor
GameStats::GameStats(int whtWins, int blckWins, int whtMoves, int blckMoves, int gameCounter, double whtWinPercent, double blckWinPercent) {
    WhiteWinsScore = whtWins;
    BlackWinsScore = blckWins;
    WhiteMovesScore = whtMoves;
    BlackMovesScore = blckMoves;
    GameCounter = whtWins + blckWins;
	WhiteWinPercent = whtWins == 0 ? 0.0 : (double)whtWins / GameCounter * 100;
	BlackWinPercent = blckWins == 0 ? 0.0 : (double)blckWins / GameCounter * 100;
}

// Save stats to a binary file
void GameStats::saveStatsToFile(const std::string& filename) const {
    // Read existing stats from the file (if any)
    GameStats existingStats(0, 0, 0, 0, 0, 0.0, 0.0);
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> existingStats.WhiteWinsScore
            >> existingStats.BlackWinsScore
            >> existingStats.WhiteMovesScore
            >> existingStats.BlackMovesScore
            >> existingStats.GameCounter
            >> existingStats.WhiteWinPercent
            >> existingStats.BlackWinPercent;
        inFile.close();
    }

    // Add current instance's stats to existing stats
    GameStats newStats(
        existingStats.WhiteWinsScore + this->WhiteWinsScore,
        existingStats.BlackWinsScore + this->BlackWinsScore,
        existingStats.WhiteMovesScore + this->WhiteMovesScore,
        existingStats.BlackMovesScore + this->BlackMovesScore,
        existingStats.GameCounter + this->GameCounter,
        existingStats.WhiteWinPercent,
        existingStats.BlackWinPercent
    );

    // Debug: Print the values being written
    std::cout << "Writing to file: "
        << "WhiteWinsScore = " << newStats.WhiteWinsScore << ", "
        << "BlackWinsScore = " << newStats.BlackWinsScore << ", "
        << "WhiteMovesScore = " << newStats.WhiteMovesScore << ", "
        << "BlackMovesScore = " << newStats.BlackMovesScore << std::endl;

    // Write the combined stats back to the file
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << newStats.WhiteWinsScore << " "
            << newStats.BlackWinsScore << " "
            << newStats.WhiteMovesScore << " "
            << newStats.BlackMovesScore << " "
            << newStats.GameCounter << " "
            << newStats.WhiteWinPercent << " "
            << newStats.BlackWinPercent;
        if (!outFile) {
            std::cerr << "Error writing to file!" << std::endl;
        }
        outFile.close();
        std::cout << "Game statistics saved in text format!" << std::endl;
    }
    else {
        std::cerr << "Failed to open file for saving!" << std::endl;
    }
}

// Load stats from a binary file
void GameStats::loadSaveFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> this->WhiteWinsScore
            >> this->BlackWinsScore
            >> this->WhiteMovesScore
            >> this->BlackMovesScore
            >> this->GameCounter
            >> this->WhiteWinPercent
            >> this->BlackWinPercent;
        inFile.close();
        std::cout << "Game statistics loaded from text format!" << std::endl;
    }
    else {
        std::cerr << "Failed to open file for loading!" << std::endl;
    }
}



