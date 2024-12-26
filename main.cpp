// main.cpp
#include <iostream>
#include "quizhandlar.h"

int main() {
    QuizHandler handler("quizzes.txt");
    // Ladda alla quiz som redan finns i fil
    handler.loadAllQuizzes();

    while (true) {
        std::cout << "\n=== HUVUDMENY ===\n"
            << "1) Skapa nytt quiz\n"
            << "2) Spela quiz\n"
            << "3) Visa leaderboard\n"
            << "4) Avsluta\n"
            << "Val: ";
        int val;
        std::cin >> val;

        if (!std::cin) {
            // rensa
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ogiltig inmatning!\n";
            continue;
        }

        if (val == 1) {
            handler.createQuiz();
        }
        else if (val == 2) {
            handler.playQuiz();
        }
        else if (val == 3) {
            handler.showQuizLeaderboard();
        }
        else {
            std::cout << "Avslutar...\n";
            break;
        }
    }

    return 0;
}
