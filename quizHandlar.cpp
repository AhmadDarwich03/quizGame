// quiz_handler.cpp
#include "quizhandlar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include "yesnoquestion.h"
#include "multiplechoicequestion.h"
#include "directanswerquestion.h"

QuizHandler::QuizHandler(const std::string& quizListFilename)
    : quizListFile(quizListFilename) {}

QuizHandler::~QuizHandler() {
    // Rensa minne
    for (auto qz : quizzes) {
        delete qz;
    }
}

// Ladda in quiz-listan
void QuizHandler::loadAllQuizzes() {
    std::ifstream in(quizListFile);
    if (!in.is_open()) {
        // Filen kanske inte finns, skapa en tom
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

            // Skapa quiz-objekt
            Quiz* newQuiz = new Quiz(qName, dataF);
            // Ladda fr�gor
            newQuiz->loadFromFile();
            // Ladda scoreboard
            newQuiz->loadLeaderboard();

            quizzes.push_back(newQuiz);
        }
    }
}

// Spara listan av quiz i quizListFile
void QuizHandler::saveQuizList() {
    std::ofstream out(quizListFile);
    if (!out.is_open()) {
        std::cerr << "Kunde inte skriva quiz-listan till fil.\n";
        return;
    }
    for (auto qz : quizzes) {
        out << qz->getName() << ";" << qz->getDataFile() << "\n";
    }
}

// Skapa nytt quiz interaktivt
void QuizHandler::createQuiz() {
    // Rensa ev. cin
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Ange namn p� nytt quiz: ";
    std::string quizName;
    std::getline(std::cin, quizName);

    // Bygg ett filnamn f�r fr�gorna
    // T.ex. "ahmad_quiz_data.txt"
    std::string dataFile = quizName + "_quiz_data.txt";

    // Skapa quiz
    Quiz* newQuiz = new Quiz(quizName, dataFile);

    // Fr�ga hur m�nga fr�gor
    std::cout << "Hur m�nga fr�gor vill du l�gga till? ";
    int numQ;
    std::cin >> numQ;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < numQ; i++) {
        std::cout << "\nSkapa fr�ga " << (i + 1) << "...\n";
        std::cout << "V�lj typ (1=Yes/No, 2=MultipleChoice, 3=DirectAnswer): ";
        int t;
        std::cin >> t;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Ange fr�getext: ";
        std::string qtext;
        std::getline(std::cin, qtext);

        if (t == 1) {
            // Yes/No
            std::cout << "�r korrekt svar 'yes'? (y/n): ";
            std::string yn;
            std::getline(std::cin, yn);
            bool correct = (yn == "y" || yn == "yes");
            newQuiz->addQuestion(new YesNoQuestion(qtext, correct));
        }
        else if (t == 2) {
            // Flervalsfr�ga
            std::cout << "Hur m�nga alternativ? ";
            int nOpts;
            std::cin >> nOpts;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::vector<std::string> opts;
            opts.reserve(nOpts);
            for (int j = 0; j < nOpts; j++) {
                std::cout << "Alternativ " << (j + 1) << ": ";
                std::string o;
                std::getline(std::cin, o);
                opts.push_back(o);
            }
            std::cout << "Vilket alternativ �r korrekt? (ange exakt text): ";
            std::string corr;
            std::getline(std::cin, corr);

            newQuiz->addQuestion(new MultipleChoiceQuestion(qtext, opts, corr));
        }
        else {
            // DirectAnswer
            std::cout << "Vad �r r�tt svar (text)? ";
            std::string corr;
            std::getline(std::cin, corr);
            newQuiz->addQuestion(new DirectAnswerQuestion(qtext, corr));
        }
    }

    // Spara fr�gorna direkt till fil
    newQuiz->saveToFile();
    // Ladda in scoreboard (skapas tomt om inget finns)
    newQuiz->loadLeaderboard();

    // L�gg in i vektor
    quizzes.push_back(newQuiz);

    // Uppdatera quiz-listan
    saveQuizList();

    std::cout << "\nQuiz \"" << quizName << "\" skapades!\n";
}

// Lista quiz
void QuizHandler::listQuizzes() {
    if (quizzes.empty()) {
        std::cout << "\nInga quiz finns i systemet �nnu.\n";
        return;
    }
    std::cout << "\nTillg�ngliga quiz:\n";
    for (size_t i = 0; i < quizzes.size(); i++) {
        std::cout << (i + 1) << ") " << quizzes[i]->getName() << "\n";
    }
}

// Spela
void QuizHandler::playQuiz() {
    if (quizzes.empty()) {
        std::cout << "\nInga quiz tillg�ngliga.\n";
        return;
    }
    listQuizzes();
    std::cout << "V�lj quiz (nummer): ";
    int idx;
    std::cin >> idx;
    if (idx < 1 || idx >(int)quizzes.size()) {
        std::cout << "Ogiltigt val.\n";
        return;
    }
    Quiz* qz = quizzes[idx - 1];

    std::cout << "Ange spelarens namn: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string playerName;
    std::getline(std::cin, playerName);

    int sc = qz->play(playerName);
    std::cout << playerName << ", du fick " << sc << " po�ng!\n";
}

// Visa scoreboard
void QuizHandler::showQuizLeaderboard() {
    if (quizzes.empty()) {
        std::cout << "\nInga quiz tillg�ngliga.\n";
        return;
    }
    listQuizzes();
    std::cout << "V�lj quiz (nummer): ";
    int idx;
    std::cin >> idx;
    if (idx < 1 || idx >(int)quizzes.size()) {
        std::cout << "Ogiltigt val.\n";
        return;
    }
    Quiz* qz = quizzes[idx - 1];
    qz->showLeaderboard();
}
