#include "direct_answer_question.h"
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
    // case-insensitive
    std::string userAns = ans;
    std::string corr = correctAnswer;

    std::transform(userAns.begin(), userAns.end(), userAns.begin(), ::tolower);
    std::transform(corr.begin(), corr.end(), corr.begin(), ::tolower);

    return (userAns == corr);
}

// e.g. "DA;What is 2+2?;4"
DirectAnswerQuestion* DirectAnswerQuestion::fromFileLine(const std::string& line) {
    size_t first = line.find(';');
    size_t second = line.find(';', first + 1);
    if (first == std::string::npos || second == std::string::npos) return nullptr;

    std::string text = line.substr(first + 1, second - (first + 1));
    std::string corr = line.substr(second + 1);

    return new DirectAnswerQuestion(text, corr);
}

std::string DirectAnswerQuestion::toFileLine() const {
    // "DA;questionText;correctAnswer"
    return "DA;" + questionText + ";" + correctAnswer;
}
