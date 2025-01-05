#pragma once
#include "question.h"
#include <vector>
#include <string>

class MultipleChoiceQuestion : public Question {
private:
    std::vector<std::string> options;
    std::string correctOption;

public:
    MultipleChoiceQuestion(const std::string& text,
        const std::vector<std::string>& opts,
        const std::string& corr);

    void displayQuestion() const override;
    bool checkAnswer(const std::string& ans) const override;

    static MultipleChoiceQuestion* fromFileLine(const std::string& line);
    std::string toFileLine() const;
};
