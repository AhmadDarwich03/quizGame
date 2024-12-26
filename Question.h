#pragma once
#include <string>
#include <iostream>

class Question {
protected:
    std::string questionText;
    int points; // ex 5

public:
<<<<<<< HEAD
    Question(const std::string& text, int pts);
    virtual ~Question();
=======
	Question(string questionText, int points, string answer);
	Question(string questionText, int points);
	Question();
	~Question();
	virtual void displayQuestion() = 0;
	bool checkAnswer(const string& answers);
	int getPoints();
	string getQuestionText();
	bool operator == (const Question& other);
};
>>>>>>> b3460aba0274644809c230a5b357411d20acc504

    virtual void displayQuestion() const = 0;
    virtual bool checkAnswer(const std::string& ans) const = 0;

    int getPoints() const;
    std::string getText() const;
};
