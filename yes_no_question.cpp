#include "yes_no_question.h"
#include <iostream>
#include <algorithm> // for transform

YesNoQuestion::YesNoQuestion(const std::string& text, bool correctIsYes)
    : Question(text, 5),  // 5 points by default
    correctYes(correctIsYes)
{}

void YesNoQuestion::displayQuestion() const {
    std::cout << questionText << " (yes/no)? ";
}

bool YesNoQuestion::checkAnswer(const std::string& ans) const {
    std::string lower = ans;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    bool userSaidYes = (lower == "yes" || lower == "y");
    return (userSaidYes == correctYes);
}

// Format: "YN;Is the sky blue?;yes"
YesNoQuestion* YesNoQuestion::fromFileLine(const std::string& line) {
    // Split on ';'
    // 0: "YN"
    // 1: "Is the sky blue?"
    // 2: "yes"
    size_t first = line.find(';');
    size_t second = line.find(';', first + 1);
    if (first == std::string::npos || second == std::string::npos) {
        return nullptr;
    }
    std::string text = line.substr(first + 1, second - (first + 1));
    std::string yesno = line.substr(second + 1);
    bool correct = (yesno == "yes");

    return new YesNoQuestion(text, correct);
}

std::string YesNoQuestion::toFileLine() const {
    // e.g. "YN;Is the sky blue?;yes"
    std::string yesno = (correctYes ? "yes" : "no");
    return "YN;" + questionText + ";" + yesno;
}
