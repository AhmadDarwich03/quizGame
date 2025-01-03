#pragma once
#include "Question.h"


class YesNoQuestion : public Question {
private:
    bool correctYes; // true => "yes" �r korrekt

public:
    YesNoQuestion(const std::string& text, bool correctIsYes);

    void displayQuestion() const override;
    bool checkAnswer(const std::string& ans) const override;

    // En hj�lpmetod f�r att spara/ladda denna fr�ga fr�n fil
    // (ej n�dv�ndigtvis virtual eftersom vi kallar den direkt i koden)
    static YesNoQuestion* fromFileLine(const std::string& line);
    std::string toFileLine() const;
};
