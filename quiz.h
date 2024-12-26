#pragma once
#include <string>
#include <vector>
#include "question.h"
#include "leaderboard.h"

class Quiz {
private:
    std::string name;                 // t.ex. "ahmad"
    std::string dataFile;            // t.ex. "ahmad_quiz_data.txt"
    Leaderboard leaderboard;         // egen scoreboard
    std::vector<Question*> questions;

public:
    Quiz(const std::string& quizName, const std::string& dataFilename);
    ~Quiz();

    std::string getName() const;
    std::string getDataFile() const;

    void loadFromFile(); // läs in questions från dataFile
    void saveToFile();   // spara questions till dataFile

    void loadLeaderboard(); // "ahmad_leaderboard.txt"
    void saveLeaderboard();

    void addQuestion(Question* q);
    int play(const std::string& playerName);
    void showLeaderboard();
};

