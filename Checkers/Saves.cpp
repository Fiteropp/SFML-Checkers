#include "Saves.h"
#include <cstring> // For strncpy

// Constructor
GameStats::GameStats(int whtWins, int blckWins, int whtMoves, int blckMoves) {
    WhiteWinsScore = whtWins;
	BlackWinsScore = blckWins;
	WhiteMovesScore = whtMoves;
	BlackMovesScore = blckMoves;
    
}

// Save stats to a binary file
void GameStats::saveStatsToFile(const std::string& filename) const {
    // Read existing stats from the file (if any)
    GameStats existingStats(0, 0, 0, 0);
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> existingStats.WhiteWinsScore
            >> existingStats.BlackWinsScore
            >> existingStats.WhiteMovesScore
            >> existingStats.BlackMovesScore;
        inFile.close();
    }

    // Add current instance's stats to existing stats
    GameStats newStats(
        existingStats.WhiteWinsScore + this->WhiteWinsScore,
        existingStats.BlackWinsScore + this->BlackWinsScore,
        existingStats.WhiteMovesScore + this->WhiteMovesScore,
        existingStats.BlackMovesScore + this->BlackMovesScore
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
            << newStats.BlackMovesScore;
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
            >> this->BlackMovesScore;
        inFile.close();
        std::cout << "Game statistics loaded from text format!" << std::endl;
    }
    else {
        std::cerr << "Failed to open file for loading!" << std::endl;
    }
}


