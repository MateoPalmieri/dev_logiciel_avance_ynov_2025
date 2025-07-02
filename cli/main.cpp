#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <string>
#include <limits>

std::mutex buzzer_mutex;
bool someoneBuzzed = false;
int winnerId = -1;
int playerCount = 0;
std::string question;

void waitForBuzz() {
    bool waiting = true;

    while (waiting && !someoneBuzzed) {
        int id;
        std::cout << "\nQuel joueur buzz ? (1 a " << playerCount << ") : ";
        std::cin >> id;

        if (std::cin.fail() || id < 1 || id > playerCount) {
            std::cin.clear(); // reset l'état d'erreur
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // vider le buffer
            std::cout << "Entrée invalide. Réessayez.\n";
            continue;
        }

        std::lock_guard<std::mutex> lock(buzzer_mutex);
        if (!someoneBuzzed) {
            someoneBuzzed = true;
            winnerId = id;
            std::cout << "Joueur " << id << " a buzzé en premier !\n";

            // Envoi MQTT du gagnant
            std::string cmd = "mosquitto_pub -t buzzers/winner -m " + std::to_string(id);
            int result = system(cmd.c_str());
            if (result != 0) {
                std::cerr << "Erreur lors de l'envoi du message MQTT.\n";
            }

            waiting = false;
        } else {
            std::cout << "Trop tard, un joueur a déjà buzzé.\n";
        }
    }
}

void resetGame() {
    someoneBuzzed = false;
    winnerId = -1;
}

void playRound() {
    std::cout << "\nNouvelle question : ";
    std::getline(std::cin, question);

    std::cout << "Envoi de la question...\n";
    std::string questionCmd = "mosquitto_pub -t buzzers/question -m \"" + question + "\"";
    int resultQuestion = system(questionCmd.c_str());
    if (resultQuestion != 0) {
        std::cerr << "Erreur lors de l'envoi de la question.\n";
    }

    std::cout << "Envoi du nombre de joueurs...\n";
    std::string countCmd = "mosquitto_pub -t buzzers/playerCount -m " + std::to_string(playerCount);
    int resultCount = system(countCmd.c_str());
    if (resultCount != 0) {
        std::cerr << "Erreur lors de l'envoi du nombre de joueurs.\n";
    }

    waitForBuzz();
}

int main() {
    std::cout << "=== Quiz Room CLI ===\n";

    bool validInput = false;
    while (!validInput) {
        std::cout << "\nCombien de joueurs ? ";
        std::cin >> playerCount;

        if (std::cin.fail() || playerCount <= 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrée invalide.\n";
        } else {
            std::cin.ignore(); // Vider le \n
            validInput = true;
        }
    }

    bool keepPlaying = true;

    while (keepPlaying) {
        resetGame();
        playRound();

        std::string again;
        std::cout << "\nVoulez-vous rejouer ? (o/n) : ";
        std::getline(std::cin, again);

        if (again != "o" && again != "O") {
            keepPlaying = false;
            std::cout << "Fin du jeu.\n";
        }
    }

    return 0;
}
