#pragma once
<<<<<<< HEAD
#include "Question.h"
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
=======
#include <iostream>
#include <vector>
#include <string>
#include "Question.h"

using namespace std;

class MultipleChoiceQuestion : public Question {
private:
    vector<string> optionM; 
    string correctAnswer; 
    Question* points;
    Question* questionText;

public:
   
    MultipleChoiceQuestion(string questionText, int points, const vector<string>& optionM, string correctAnswer);
    MultipleChoiceQuestion();
    void displayQuestion() override;                      
    bool checkAnswer(const string& answers);      
    vector<string> getOption() const;                   
    string getCorrectAnswer() const;                       
>>>>>>> b3460aba0274644809c230a5b357411d20acc504
};
