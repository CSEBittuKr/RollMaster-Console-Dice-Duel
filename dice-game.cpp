#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>

class Dice {
public:
    int roll() {
        return rand() % 6 + 1;
    }
};

class Player {
private:
    std::string name;
    int score;

public:
    Player(std::string pName) : name(pName), score(0) {}

    std::string getName() const {
        return name;
    }

    int getScore() const {
        return score;
    }

    void incrementScore() {
        score++;
    }
};

class DiceGame {
private:
    std::vector<Player> players;
    Dice dice;
    int rounds;
    
    
    void waitForEnter() {
        std::cout << " (Press Enter to continue)";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

public:
    DiceGame(const std::vector<std::string>& playerNames, int numRounds) {
        for (const auto& name : playerNames) {
            players.push_back(Player(name));
        }
        rounds = numRounds;
    }

    void play() {
        for (int i = 0; i < rounds; ++i) {
            std::cout << "\n\n--- ዙ Round " << i + 1 << " ---" << std::endl;

            int highestRoll = 0;
            int winnerIndex = -1;
            bool isTie = false;
            std::vector<int> currentRolls;

            for (size_t j = 0; j < players.size(); ++j) {
                std::cout << "It's " << players[j].getName() << "'s turn! Press Enter to roll... 🎲";
                std::cin.get(); 
                
                int rollValue = dice.roll();
                currentRolls.push_back(rollValue);
                std::cout << "🎯 " << players[j].getName() << " rolled a " << rollValue << "!" << std::endl;
            }

            for (size_t j = 0; j < players.size(); ++j) {
                if (currentRolls[j] > highestRoll) {
                    highestRoll = currentRolls[j];
                    winnerIndex = j;
                    isTie = false;
                } else if (currentRolls[j] == highestRoll) {
                    isTie = true;
                }
            }
            
            std::cout << "\n--- Round Results ---" << std::endl;
            if (isTie) {
                std::cout << "🤝 It's a tie this round! No points awarded." << std::endl;
            } else if (winnerIndex != -1) {
                std::cout << "🏆 " << players[winnerIndex].getName() << " wins the round with a " << highestRoll << "!" << std::endl;
                players[winnerIndex].incrementScore();
            }
        }
        showHistory();
    }

    void showHistory() {
        std::cout << "\n\n🏁 ===== FINAL SCOREBOARD ===== 🏁" << std::endl;
        for (const auto& player : players) {
            std::cout << "🥇 " << player.getName() << ": " << player.getScore() << " wins" << std::endl;
        }
        std::cout << "================================" << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "🎉 Welcome to the Interactive Dice Game! 🎉" << std::endl;

    int numPlayers;
    std::cout << "How many players? 🤔 ";
    while (!(std::cin >> numPlayers) || numPlayers <= 0) {
        std::cout << "Invalid input. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::string> playerNames;
    for (int i = 0; i < numPlayers; ++i) {
        std::cout << "Enter name for Player " << i + 1 << ": ";
        std::string name;
        getline(std::cin, name);
        playerNames.push_back(name);
    }

    int numRounds;
    std::cout << "How many rounds would you like to play? ";
     while (!(std::cin >> numRounds) || numRounds <= 0) {
        std::cout << "Invalid input. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    DiceGame game(playerNames, numRounds);
    game.play();

    std::cout << "\nThanks for playing! 👋" << std::endl;

    return 0;
}