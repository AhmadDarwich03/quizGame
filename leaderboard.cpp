#include "leaderboard.h"

#include <fstream>
#include <iostream>
#include <algorithm>

void Leaderboard::loadFromFile(const std::string& filename) {
    players.clear();
    std::ifstream in(filename);
    if (!in.is_open()) {
        // Filen kanske inte finns �nnu � inget fel
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        // Format: playerName,score
        auto pos = line.find(',');
        if (pos != std::string::npos) {
            std::string pname = line.substr(0, pos);
            int sc = std::stoi(line.substr(pos + 1));
            players.emplace_back(pname, sc);
        }
    }
}

void Leaderboard::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Kunde inte skriva leaderboard till fil: " << filename << "\n";
        return;
    }
    for (auto& p : players) {
        out << p.getName() << "," << p.getScore() << "\n";
    }
}

void Leaderboard::addOrUpdate(const std::string& playerName, int newPoints) {
    for (auto& p : players) {
        if (p.getName() == playerName) {
            p.addScore(newPoints);
            return;
        }
    }
    // Om inte hittad
    players.emplace_back(playerName, newPoints);
}

void Leaderboard::display() const {
    // Sortera f�rst
    std::vector<Player> sortedPlayers = players;
    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
        [](const Player& a, const Player& b) {
            return a.getScore() > b.getScore();
        }
    );
    std::cout << "\n--- Leaderboard ---\n";
    for (size_t i = 0; i < sortedPlayers.size(); i++) {
        std::cout << (i + 1) << ". " << sortedPlayers[i].getName()
            << " - " << sortedPlayers[i].getScore() << " po�ng\n";
    }
}