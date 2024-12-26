// quiz.cpp
#include "quiz.h"
#include "yesnoquestion.h"
#include "multiplechoicequestion.h"
#include "directanswerquestion.h"
#include <fstream>
#include <iostream>
#include <limits>

Quiz::Quiz(const std::string& quizName, const std::string& dataFilename)
    : name(quizName), dataFile(dataFilename)
{}

Quiz::~Quiz() {
    // rensa minne
    for (auto q : questions) {
        delete q;
    }
}

std::string Quiz::getName() const {
    return name;
}

std::string Quiz::getDataFile() const {
    return dataFile;
}

void Quiz::loadFromFile() {
    // Rensa ev. gamla frågor
    for (auto q : questions) {
        delete q;
    }
    questions.clear();

    std::ifstream in(dataFile);
    if (!in.is_open()) {
        // Filen kanske inte finns ännu – inget fel
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        // Titta på prefix "YN", "MC", "DA"
        if (line.rfind("YN;", 0) == 0) {
            // yes/no
            Question* q = YesNoQuestion::fromFileLine(line);
            if (q) questions.push_back(q);
        }
        else if (line.rfind("MC;", 0) == 0) {
            Question* q = MultipleChoiceQuestion::fromFileLine(line);
            if (q) questions.push_back(q);
        }
        else if (line.rfind("DA;", 0) == 0) {
            Question* q = DirectAnswerQuestion::fromFileLine(line);
            if (q) questions.push_back(q);
        }
    }
}

void Quiz::saveToFile() {
    std::ofstream out(dataFile);
    if (!out.is_open()) {
        std::cerr << "Kunde inte spara quiz-data till fil: " << dataFile << "\n";
        return;
    }
    // Skriv ut varje fråga i “toFileLine()”-format
    for (auto q : questions) {
        // För att skilja ut rätt subklass kan vi testa dynamic_cast
        if (auto yn = dynamic_cast<YesNoQuestion*>(q)) {
            out << yn->toFileLine() << "\n";
        }
        else if (auto mc = dynamic_cast<MultipleChoiceQuestion*>(q)) {
            out << mc->toFileLine() << "\n";
        }
        else if (auto da = dynamic_cast<DirectAnswerQuestion*>(q)) {
            out << da->toFileLine() << "\n";
        }
    }
}

void Quiz::loadLeaderboard() {
    std::string lbFile = name + "_leaderboard.txt";
    leaderboard.loadFromFile(lbFile);
}

void Quiz::saveLeaderboard() {
    std::string lbFile = name + "_leaderboard.txt";
    leaderboard.saveToFile(lbFile);
}

void Quiz::addQuestion(Question* q) {
    questions.push_back(q);
}

int Quiz::play(const std::string& playerName) {
    // read leftover
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int totalScore = 0;
    for (auto q : questions) {
        q->displayQuestion();
        std::string ans;
        std::getline(std::cin, ans);
        if (q->checkAnswer(ans)) {
            std::cout << "Rätt!\n";
            totalScore += q->getPoints();
        }
        else {
            std::cout << "Fel!\n";
        }
    }
    // uppdatera scoreboard
    leaderboard.addOrUpdate(playerName, totalScore);
    saveLeaderboard();
    return totalScore;
}

void Quiz::showLeaderboard() {
    leaderboard.display();
}
