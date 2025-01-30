#ifndef GAME_STATS_BINARY_H
#define GAME_STATS_BINARY_H

#include <string>
#include <iostream>
#include <fstream>

struct GameStats {
    int WhiteWinsScore;
	int BlackWinsScore;
    int WhiteMovesScore;
	int BlackMovesScore;

    // Constructor
    GameStats(int whtWins = 0, int blckWins = 0, int whtMoves = 0, int blckMoves = 0);

    // Save stats to a binary file
    void saveStatsToFile(const std::string& filename) const;

    // Load stats from a binary file
    void loadSaveFromFile(const std::string& filename);
};

#endif // GAME_STATS_BINARY_H