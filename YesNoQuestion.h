#pragma once
#include "Question.h"


class YesNoQuestion : public Question {
private:
    bool correctYes; // true => "yes" är korrekt

public:
    YesNoQuestion(const std::string& text, bool correctIsYes);

    void displayQuestion() const override;
    bool checkAnswer(const std::string& ans) const override;

    // En hjälpmetod för att spara/ladda denna fråga från fil
    // (ej nödvändigtvis virtual eftersom vi kallar den direkt i koden)
    static YesNoQuestion* fromFileLine(const std::string& line);
    std::string toFileLine() const;
};
