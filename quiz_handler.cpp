#include "quiz_handler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include "yes_no_question.h"
#include "multiple_choice_question.h"
#include "direct_answer_question.h"

QuizHandler::QuizHandler(const std::string& quizListFilename)
    : quizListFile(quizListFilename) {}

QuizHandler::~QuizHandler() {
    for (auto qz : quizzes) {
        delete qz;
    }
}

void QuizHandler::loadAllQuizzes() {
    std::ifstream in(quizListFile);
    if (!in.is_open()) {
        // If there's no quiz list file, create an empty one
        std::ofstream createFile(quizListFile);
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        // Format: quizName;dataFilename
        auto pos = line.find(';');
        if (pos != std::string::npos) {
            std::string qName = line.substr(0, pos);
            std::string dataF = line.substr(pos + 1);

            Quiz* newQuiz = new Quiz(qName, dataF);
            newQuiz->loadFromFile();      // load questions
            newQuiz->loadLeaderboard();   // load scoreboard
            quizzes.push_back(newQuiz);
        }
    }
}

void QuizHandler::saveQuizList() {
    std::ofstream out(quizListFile);
    if (!out.is_open()) {
        std::cerr << "Could not write to quiz list file.\n";
        return;
    }
    for (auto qz : quizzes) {
        out << qz->getName() << ";" << qz->getDataFile() << "\n";
    }
}

void QuizHandler::createQuiz() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Ange namn på nytt quiz: ";
    std::string quizName;
    std::getline(std::cin, quizName);

    // Build the data file name, e.g. "ahmad_quiz_data.txt"
    std::string dataFile = quizName + "_quiz_data.txt";

    // Create quiz
    Quiz* newQuiz = new Quiz(quizName, dataFile);

    std::cout << "Hur många frågor vill du lägga till? ";
    int numQ;
    std::cin >> numQ;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < numQ; i++) {
        std::cout << "\nSkapa fråga " << (i + 1) << "...\n"
            << "Välj typ (1=Yes/No, 2=MultipleChoice, 3=DirectAnswer): ";
        int t;
        std::cin >> t;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Ange frågetext: ";
        std::string qtext;
        std::getline(std::cin, qtext);

        if (t == 1) {
            // YesNo
            std::cout << "Är korrekt svar 'yes'? (y/n): ";
            std::string yn;
            std::getline(std::cin, yn);
            bool correct = (yn == "y" || yn == "yes");
            newQuiz->addQuestion(new YesNoQuestion(qtext, correct));
        }
        else if (t == 2) {
            // MultipleChoice
            std::cout << "Hur många alternativ? ";
            int nOpts;
            std::cin >> nOpts;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::vector<std::string> opts;
            opts.reserve(nOpts);
            for (int j = 0; j < nOpts; j++) {
                std::cout << "Alternativ " << (j + 1) << ": ";
                std::string optStr;
                std::getline(std::cin, optStr);
                opts.push_back(optStr);
            }
            std::cout << "Vilket alternativ är korrekt? (ange exakt text): ";
            std::string corr;
            std::getline(std::cin, corr);

            newQuiz->addQuestion(new MultipleChoiceQuestion(qtext, opts, corr));
        }
        else {
            // DirectAnswer
            std::cout << "Vad är rätt svar (text)? ";
            std::string corr;
            std::getline(std::cin, corr);
            newQuiz->addQuestion(new DirectAnswerQuestion(qtext, corr));
        }
    }

    // Save quiz to file
    newQuiz->saveToFile();
    // Load (or init) scoreboard
    newQuiz->loadLeaderboard();

    quizzes.push_back(newQuiz);
    saveQuizList();

    std::cout << "\nQuiz \"" << quizName << "\" skapades!\n";
}

void QuizHandler::listQuizzes() {
    if (quizzes.empty()) {
        std::cout << "\nInga quiz finns ännu.\n";
        return;
    }
    std::cout << "\nTillgängliga quiz:\n";
    for (size_t i = 0; i < quizzes.size(); i++) {
        std::cout << (i + 1) << ") " << quizzes[i]->getName() << "\n";
    }
}

void QuizHandler::playQuiz() {
    if (quizzes.empty()) {
        std::cout << "\nInga quiz finns.\n";
        return;
    }
    listQuizzes();
    std::cout << "Välj quiz (nummer): ";
    int idx;
    std::cin >> idx;

    if (idx < 1 || idx >(int)quizzes.size()) {
        std::cout << "Ogiltigt val.\n";
        return;
    }
    Quiz* chosen = quizzes[idx - 1];

    std::cout << "Ange spelarens namn: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string playerName;
    std::getline(std::cin, playerName);

    int sc = chosen->play(playerName);
    std::cout << "\nSpelare \"" << playerName << "\" fick "
        << sc << " poäng i \"" << chosen->getName() << "\"!\n";
}

void QuizHandler::showQuizLeaderboard() {
    if (quizzes.empty()) {
        std::cout << "\nInga quiz finns.\n";
        return;
    }
    listQuizzes();
    std::cout << "Välj quiz (nummer): ";
    int idx;
    std::cin >> idx;
    if (idx < 1 || idx >(int)quizzes.size()) {
        std::cout << "Ogiltigt val.\n";
        return;
    }
    Quiz* chosen = quizzes[idx - 1];
    chosen->showLeaderboard();
}
