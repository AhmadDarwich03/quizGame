#pragma once
#include "question.h"
#include <string>

class DirectAnswerQuestion : public Question {
private:
    std::string correctAnswer;

public:
    DirectAnswerQuestion(const std::string& text, const std::string& corr);

    void displayQuestion() const override;
    bool checkAnswer(const std::string& ans) const override;

    static DirectAnswerQuestion* fromFileLine(const std::string& line);
    std::string toFileLine() const;
};
