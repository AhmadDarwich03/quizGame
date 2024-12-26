// quiz_handler.hpp
#pragma once
#include <vector>
#include <string>
#include "quiz.h"

class QuizHandler {
private:
    std::vector<Quiz*> quizzes;
    std::string quizListFile; // ex: "quizzes.txt"

public:
    QuizHandler(const std::string& quizListFilename);
    ~QuizHandler();

    void loadAllQuizzes();  // Läser "quizzes.txt", laddar varje quiz + leaderboard
    void saveQuizList();    // Skriver ut listan av quiz i "quizzes.txt"

    void createQuiz();      // Skapa nytt quiz + spara i fil
    void listQuizzes();
    void playQuiz();
    void showQuizLeaderboard();
};
