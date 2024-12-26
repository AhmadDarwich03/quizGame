#include <algorithm>
#include <iostream>
#include "YesNoQuestion.h"

YesNoQuestion::YesNoQuestion(const std::string& text, bool correctIsYes)
    : Question(text, 5), correctYes(correctIsYes) {}

void YesNoQuestion::displayQuestion() const {
    std::cout << questionText << " (yes/no)? ";
}

bool YesNoQuestion::checkAnswer(const std::string& ans) const {
    std::string lower = ans;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    bool userSaidYes = (lower == "yes" || lower == "y");
    return (userSaidYes == correctYes);
}

// Anta filformat: "YN;Is the sky blue?;yes"
YesNoQuestion* YesNoQuestion::fromFileLine(const std::string& line) {
    // Ex: line = "YN;Is the sky blue?;yes"
    // Splitta på ';'
    // 0: "YN"
    // 1: "Is the sky blue?"
    // 2: "yes" (eller "no")

    size_t first = line.find(';');
    size_t second = line.find(';', first + 1);
    if (first == std::string::npos || second == std::string::npos) {
        return nullptr;
    }
    // questionText
    std::string text = line.substr(first + 1, second - (first + 1));
    // yes/no
    std::string yesno = line.substr(second + 1);
    bool correct = false;
    if (yesno == "yes") correct = true;

    return new YesNoQuestion(text, correct);
}

std::string YesNoQuestion::toFileLine() const {
    // "YN;questionText;yes" eller "no"
    std::string yesno = (correctYes ? "yes" : "no");
    return "YN;" + questionText + ";" + yesno;
}
