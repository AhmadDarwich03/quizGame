#pragma once
#include <vector>
#include <string>
#include "quiz.h"

class QuizHandler {
private:
    std::vector<Quiz*> quizzes;
    std::string quizListFile; // e.g. "quizzes.txt"

public:
    QuizHandler(const std::string& quizListFilename);
    ~QuizHandler();

    // Load all quiz definitions from quizListFile
    void loadAllQuizzes();
    // Save them back so new quizzes appear in quizListFile
    void saveQuizList();

    void createQuiz();
    void listQuizzes();
    void playQuiz();
    void showQuizLeaderboard();
};
