#pragma once
#include <string>

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& n, int s = 0);

    std::string getName() const;
    int getScore() const;
    void addScore(int pts);
};
