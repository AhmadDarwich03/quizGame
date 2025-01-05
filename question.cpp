#include "question.h"

Question::Question(const std::string& text, int pts)
    : questionText(text), points(pts) {}

Question::~Question() = default;

int Question::getPoints() const {
    return points;
}

std::string Question::getText() const {
    return questionText;
}
