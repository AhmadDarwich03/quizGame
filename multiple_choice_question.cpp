#include "multiple_choice_question.h"
#include <iostream>
#include <sstream>   

MultipleChoiceQuestion::MultipleChoiceQuestion(const std::string& text,
    const std::vector<std::string>& opts,
    const std::string& corr)
    : Question(text, 5),
    options(opts),
    correctOption(corr)
{}

void MultipleChoiceQuestion::displayQuestion() const {
    std::cout << questionText << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << (i + 1) << ") " << options[i] << "\n";
    }
    std::cout << "Ange ditt svar (text eller siffra): ";
}

bool MultipleChoiceQuestion::checkAnswer(const std::string& ans) const {
    // Direct text match
    if (ans == correctOption) return true;

    // Try numeric
    try {
        int idx = std::stoi(ans) - 1;
        if (idx >= 0 && idx < (int)options.size()) {
            return (options[idx] == correctOption);
        }
    }
    catch (...) {
        // stoi failed
    }
    return false;
}

// Format: "MC;What is 2+2?;2|3|4|5;4"
MultipleChoiceQuestion* MultipleChoiceQuestion::fromFileLine(const std::string& line) {
    // Split by ';'
    //  0: "MC"
    //  1: "What is 2+2?"
    //  2: "2|3|4|5"
    //  3: "4"
    std::stringstream ss(line);
    std::vector<std::string> parts;
    {
        std::string token;
        while (std::getline(ss, token, ';')) {
            parts.push_back(token);
        }
    }
    if (parts.size() < 4) return nullptr;

    std::string text = parts[1];
    std::string optStr = parts[2];
    std::string corrOpt = parts[3];

    // Split optStr on '|'
    std::vector<std::string> opts;
    {
        std::stringstream sopt(optStr);
        std::string piece;
        while (std::getline(sopt, piece, '|')) {
            opts.push_back(piece);
        }
    }

    return new MultipleChoiceQuestion(text, opts, corrOpt);
}

std::string MultipleChoiceQuestion::toFileLine() const {
    // "MC;questionText;alt1|alt2|...;correctOption"
    std::string optStr;
    for (size_t i = 0; i < options.size(); ++i) {
        optStr += options[i];
        if (i + 1 < options.size()) optStr += "|";
    }
    return "MC;" + questionText + ";" + optStr + ";" + correctOption;
}
