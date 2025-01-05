#pragma once
#include <string>

class Question {
protected:
    std::string questionText;
    int points; // e.g. 5 for a correct answer

public:
    Question(const std::string& text, int pts);
    virtual ~Question();

    virtual void displayQuestion() const = 0;
    virtual bool checkAnswer(const std::string& ans) const = 0;

    int getPoints() const;
    std::string getText() const;
};
