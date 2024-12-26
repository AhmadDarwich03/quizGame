#pragma once
#include <vector>
#include <string>
#include "player.h"


class Leaderboard {
private:
    std::vector<Player> players;

public:
    // Ladda/spara
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    // Uppdatera
    void addOrUpdate(const std::string& playerName, int newPoints);

    // Skriva ut i konsolen
    void display() const;
};
