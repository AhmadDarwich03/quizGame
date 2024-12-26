#include "DirectAnswerQuestion.h"
#include <iostream>
#include <algorithm>


DirectAnswerQuestion::DirectAnswerQuestion(const std::string& text,
    const std::string& corr)
    : Question(text, 5),
    correctAnswer(corr)
{}

void DirectAnswerQuestion::displayQuestion() const {
    std::cout << questionText << "\nDitt svar: ";
}

bool DirectAnswerQuestion::checkAnswer(const std::string& ans) const {
    std::string userAns = ans, corr = correctAnswer;
    std::transform(userAns.begin(), userAns.end(), userAns.begin(), ::tolower);
    std::transform(corr.begin(), corr.end(), corr.begin(), ::tolower);
    return (userAns == corr);
}

DirectAnswerQuestion* DirectAnswerQuestion::fromFileLine(const std::string& line) {

    size_t first = line.find(';');
    size_t second = line.find(';', first + 1);
    if (first == std::string::npos || second == std::string::npos) return nullptr;

    std::string text = line.substr(first + 1, second - (first + 1));
    std::string corr = line.substr(second + 1);

    return new DirectAnswerQuestion(text, corr);
}

std::string DirectAnswerQuestion::toFileLine() const {
    return "DA;" + questionText + ";" + correctAnswer;
}

