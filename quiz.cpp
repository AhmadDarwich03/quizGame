#include "quiz.h"
#include "yes_no_question.h"
#include "multiple_choice_question.h"
#include "direct_answer_question.h"
#include <fstream>
#include <iostream>
#include <limits>

Quiz::Quiz(const std::string& quizName, const std::string& dataFilename)
    : name(quizName), dataFile(dataFilename)
{}

Quiz::~Quiz() {
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
    // clear existing
    for (auto q : questions) {
        delete q;
    }
    questions.clear();

    std::ifstream in(dataFile);
    if (!in.is_open()) {
        // might not exist yet
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        // YN, MC, DA
        if (line.find("YN;", 0) == 0) {
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
        std::cerr << "Could not write quiz data to file: " << dataFile << "\n";
        return;
    }
    for (auto q : questions) {
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
    // flush leftover input
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
    leaderboard.addOrUpdate(playerName, totalScore);
    saveLeaderboard();
    return totalScore;
}

void Quiz::showLeaderboard() {
    leaderboard.display();
}
