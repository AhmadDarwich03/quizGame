#pragma once
#include <string>
#include <vector>
#include "leaderboard.h"
#include "question.h"

class Quiz {
private:
    std::string name;      // e.g. "ahmad"
    std::string dataFile;  // e.g. "ahmad_quiz_data.txt"
    Leaderboard leaderboard;
    std::vector<Question*> questions;

public:
    Quiz(const std::string& quizName, const std::string& dataFilename);
    ~Quiz();

    std::string getName() const;
    std::string getDataFile() const;

    // load/save questions from/to dataFile
    void loadFromFile();
    void saveToFile();

    void loadLeaderboard();
    void saveLeaderboard();

    void addQuestion(Question* q);

    int play(const std::string& playerName);
    void showLeaderboard();
};
