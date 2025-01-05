#pragma once
#include "question.h"
#include <string>

class YesNoQuestion : public Question {
private:
    bool correctYes; // true => "yes" is correct

public:
    YesNoQuestion(const std::string& text, bool correctIsYes);

    void displayQuestion() const override;
    bool checkAnswer(const std::string& ans) const override;

    // For saving/loading from file
    static YesNoQuestion* fromFileLine(const std::string& line);
    std::string toFileLine() const;
};
