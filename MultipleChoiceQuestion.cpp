#include "MultipleChoiceQuestion.h"
<<<<<<< HEAD
#include <iostream>
#include <sstream>   // <-- viktigt för stringstream
#include <algorithm> // <-- om du använder transform/sort
#include <string>    // <-- för std::string


MultipleChoiceQuestion::MultipleChoiceQuestion(const std::string& text,
    const std::vector<std::string>& opts,
    const std::string& corr)
    : Question(text, 5),
    options(opts),
    correctOption(corr)
{}

void MultipleChoiceQuestion::displayQuestion() const {
    std::cout << questionText << "\n";
    for (size_t i = 0; i < options.size(); i++) {
        std::cout << (i + 1) << ") " << options[i] << "\n";
    }
    std::cout << "Ange ditt svar (text eller siffra): ";
}

bool MultipleChoiceQuestion::checkAnswer(const std::string& ans) const {
    if (ans == correctOption) return true;
    try {
        int idx = std::stoi(ans) - 1;
        if (idx >= 0 && idx < (int)options.size()) {
            return (options[idx] == correctOption);
        }
    }
    catch (...) {}
    return false;
}

// Anta filformat: "MC;Vad är 2+2?;4|5|6|7;4"
MultipleChoiceQuestion* MultipleChoiceQuestion::fromFileLine(const std::string& line) {
    // Splitta på ';'
    // 0: "MC"
    // 1: "Vad är 2+2?"
    // 2: "4|5|6|7"
    // 3: "4"
    std::vector<std::string> parts;
    {
        std::stringstream ss(line);
        std::string segment;
        while (std::getline(ss, segment, ';')) {
            parts.push_back(segment);
        }
    }
    if (parts.size() < 4) return nullptr;

    std::string text = parts[1];
    std::string optStr = parts[2];
    std::string corrOpt = parts[3];

    // splitta optStr på '|'
    std::vector<std::string> opts;
    {
        std::stringstream sopt(optStr);
        std::string o;
        while (std::getline(sopt, o, '|')) {
            opts.push_back(o);
        }
    }
    return new MultipleChoiceQuestion(text, opts, corrOpt);
}

std::string MultipleChoiceQuestion::toFileLine() const {

    std::string optStr;
    for (size_t i = 0; i < options.size(); i++) {
        optStr += options[i];
        if (i + 1 < options.size()) optStr += "|";
    }
    return "MC;" + questionText + ";" + optStr + ";" + correctOption;
}
=======

MultipleChoiceQuestion::MultipleChoiceQuestion(string questionText, int points, const vector<string>& optionM, string correctAnswer)
    :Question(questionText, points), optionM(optionM), correctAnswer(correctAnswer)
{
}

void MultipleChoiceQuestion::displayQuestion()
{
    cout << questionText << endl;
    for (size_t i = 0; i < optionM.size(); ++i) {
        cout << i + 1 << ". " << optionM[i] << endl;
    }
}

bool MultipleChoiceQuestion::checkAnswer(const string& answers)
{
    if (answers == correctAnswer)
    {
        return true;
    }
    return false;
}

vector<string> MultipleChoiceQuestion::getOption() const
{
    return optionM;
}

string MultipleChoiceQuestion::getCorrectAnswer() const
{
    return correctAnswer;
}


>>>>>>> b3460aba0274644809c230a5b357411d20acc504
