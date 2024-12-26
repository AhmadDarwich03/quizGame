#include "Question.h"

<<<<<<< HEAD

Question::Question(const std::string& text, int pts)
    : questionText(text), points(pts) {}

Question::~Question() = default;

int Question::getPoints() const {
    return points;
=======
Question::Question(string questionText, int points, string answer)
    :questionText(questionText), points(points), answer(answer)
{
}

Question::Question(string questionText, int points)
    :questionText(questionText), points(points)
{
}

Question::Question()
    :questionText(""), points(0), answer("")
{
>>>>>>> b3460aba0274644809c230a5b357411d20acc504
}

std::string Question::getText() const {
    return questionText;
}

<<<<<<< HEAD
=======
void Question::displayQuestion()
{
}

bool Question::checkAnswer(const string& answers)
{
    if (answers == answer)
    {
        return true;
    }
    return false;
}

int Question::getPoints()
{
    return points;
}

string Question::getQuestionText()
{
    return questionText;
}

bool Question::operator==(const Question& other)
{
    return this->answer == other.answer;
}
>>>>>>> b3460aba0274644809c230a5b357411d20acc504
