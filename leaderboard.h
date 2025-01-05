#pragma once
#include <vector>
#include <string>
#include "player.h"

class Leaderboard {
private:
    std::vector<Player> players;

public:
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    void addOrUpdate(const std::string& playerName, int newPoints);

    void display() const;
};
