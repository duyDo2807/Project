#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

class Card {
 public:
  int value;
  Card() {
    value = rand() % 11 + 1;  // Random card value between 1 and 11
  }
};

class Player {
 public:
  vector<Card> hand;
  int score;

  Player() { score = 0; }

  void drawCard() {
    Card newCard;
    hand.push_back(newCard);
    score += newCard.value;
  }

  void displayHand() {
    cout << "Your hand: ";
    for (const Card& card : hand) {
      cout << card.value << " ";
    }
    cout << "\nYour score: " << score << endl;
  }

  void displayLatestComputerCard(int cardValue) {
    cout << "\nComputer's newest card: " << cardValue << endl;
  }
};

class Game {
 public:
  Player player;
  Player computer;

  Game() {
    srand(static_cast<unsigned>(
        time(nullptr)));  // Seed the random number generator
  }

  void start() {
    cout << "This is a simplified Blackjack game:" << endl;
    cout << "- Both Player and the Computer aim to get closer to 21 by drawing "
            "random value number card, but getting over 21 will result in "
            "player bust. If both player and computer bust, whoever has a "
            "higher "
            "score will lose."
         << endl;
    cout << "- Both Player and Computer will start the game by getting first 2 "
            "cards, but Player can only know the Computer's first card. The "
            "second card is hidden.\n"
         << endl;

    player.drawCard();
    player.drawCard();
    computer.drawCard();
    computer.drawCard();

    player.displayHand();
    cout << "Computer's first card: " << computer.hand[0].value << endl;

    char choice;
    while (player.score < 21) {
      cout << "Do you want to draw another card? (y/n): ";
      cin >> choice;

      if (choice == 'y' || choice == 'Y') {
        player.drawCard();
        player.displayHand();

        // Draw a card for the computer and display the newest card
        if (computer.score < 17) {
          computer.drawCard();
          computer.displayLatestComputerCard(computer.hand.back().value);
        } else {
          cout << "Computer stops drawing cards." << endl;
        }
      } else if (choice == 'n' || choice == 'N') {
        if (computer.score < 17) {
          cout << "\nComputer keeps drawing card after Player selects 'n'"
               << endl;
        }
        while (computer.score < 17) {
          computer.drawCard();
        }
        break;
      } else {
        cout << "Error input, please enter again\n";
        continue;
      }
    }

    // Add a message when the computer stops drawing cards
    if (computer.score >= 17 && choice == 'n') {
      cout << "\nComputer stops drawing cards.\n" << endl;
    }

    cout << "Computer's hand: ";
    for (const Card& card : computer.hand) {
      cout << card.value << " ";
    }
    cout << "\nComputer's score: " << computer.score << endl;

    determineWinner();
  }

  void determineWinner() {
    if (player.score > 21) {
      if (computer.score > player.score) {
        cout << "Both players bust, but Player wins due to Computer drawing "
                "higher"
             << endl;
      } else if (computer.score == player.score) {
        cout << "It's a tie!" << endl;
      } else {
        cout << "Player busts. Computer wins!" << endl;
      }
    } else if (computer.score > 21) {
      if (player.score > computer.score) {
        cout << "Both players bust, but Computer wins due to Player drawing "
                "higher"
             << endl;
      } else if (computer.score == player.score) {
        cout << "It's a tie!" << endl;
      } else {
        cout << "Computer busts. Player wins!" << endl;
      }
    } else if (player.score > computer.score) {
      cout << "Player wins!" << endl;
    } else if (computer.score > player.score) {
      cout << "Computer wins!" << endl;
    } else {
      cout << "It's a tie!" << endl;
    }
  }
};

int main() {
  Game game;
  game.start();

  return 0;
}