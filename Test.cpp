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
    cout << "This is a simplified Blackjack game" << endl;

    player.drawCard();
    player.drawCard();
    computer.drawCard();
    computer.drawCard();

    player.displayHand();
    cout << "Computer's first card: " << computer.hand[0].value << endl;

    while (player.score < 21) {
      char choice;
      cout << "Do you want to draw another card? (y/n): ";
      cin >> choice;

      if (choice == 'y') {
        player.drawCard();
        player.displayHand();
      } else {
        break;
      }
    }

    while (computer.score < 17) {
      computer.drawCard();
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
      cout << "Player busts. Computer wins!" << endl;
    } else if (computer.score > 21) {
      cout << "Computer busts. Player wins!" << endl;
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