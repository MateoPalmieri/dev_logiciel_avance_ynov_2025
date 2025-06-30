#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <string>

std::mutex buzzer_mutex;
bool someoneBuzzed = false;
int winnerId = -1;

void playerThread(int id) {
    std::cout << "Joueur " << id << ", appuie sur Entree pour buzzer...\n";
    std::cin.get();

    if (buzzer_mutex.try_lock()) {
        if (!someoneBuzzed) {
            someoneBuzzed = true;
            winnerId = id;
            std::cout << "Joueur " << id << " a buzze en premier !\n";

            // Appel système vers MQTT
            std::string cmd = "mosquitto_pub -t buzzers/winner -m " + std::to_string(id);
            system(cmd.c_str());
        }
        buzzer_mutex.unlock();
    } else {
        std::cout << "Joueur " << id << " a buzzé trop tard.\n";
    }
}

int main() {
    int n;
    std::cout << "Combien de joueurs ? ";
    std::cin >> n;
    
    std::string countCmd = "mosquitto_pub -t buzzers/playerCount -m " + std::to_string(n);
    system(countCmd.c_str());

    std::cin.ignore();

    // std::string countCmd = "mosquitto_pub -t buzzers/playerCount -m " + std::to_string(n);
    // system(countCmd.c_str());

    std::vector<std::thread> threads;
    for (int i = 1; i <= n; ++i) {
        threads.emplace_back(playerThread, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
