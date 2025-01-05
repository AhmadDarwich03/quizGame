#include "player.h"

Player::Player(const std::string& n, int s)
    : name(n), score(s) {}

std::string Player::getName() const {
    return name;
}

int Player::getScore() const {
    return score;
}

void Player::addScore(int pts) {
    score += pts;
}
