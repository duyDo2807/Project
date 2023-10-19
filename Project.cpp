#include <cctype>
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

  virtual void drawCard() {
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

  void displayHand(int i) {
    cout << "Player " << i << "'s hand: ";
    for (const Card& card : hand) {
      cout << card.value << " ";
    }
    cout << "\nPlayer " << i << "'s score: " << score << endl;
  }

  void displayLatestPlayerCard(int cardValue) {
    cout << "\nOther Player's newest card: " << cardValue << endl;
  }
};

class Computer : public Player {
 public:
  void drawCard() override {
    if (score < 17) {
      Card newCard;
      hand.push_back(newCard);
      score += newCard.value;
    }
  }
  void displayLatestComputerCard(int cardValue) {
    cout << "\nComputer's newest card: " << cardValue << endl;
  }
};

class AbstractGame {
 public:
  virtual void start() = 0;
  virtual void determineWinner() = 0;
};

class BlackjackGame : public AbstractGame {
 public:
  Player player;
  Computer computer;

  BlackjackGame() {
    srand(static_cast<unsigned>(
        time(nullptr)));  // Seed the random number generator
  }

  void start() override {
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
  }

  void determineWinner() override {
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

class PokerGame : public AbstractGame {
 public:
  Player player1;
  Player player2;

  PokerGame() {
    srand(static_cast<unsigned>(
        time(nullptr)));  // Seed the random number generator
  }

  void clearScreen() {
    cout << "\033[2J\033[1;1H";  // Clear the terminal screen
  }

  void start() {
    cout << "This is a simplified Blackjack game:" << endl;
    cout << "- 2 Players aim to get closer to 21 by drawing "
            "random value number card, but getting over 21 will result in "
            "player bust. If both players bust, whoever has a "
            "higher score will lose."
         << endl;
    cout << "- Both Players will start the game by getting first 2 "
            "cards, The player can know the other player's newest card, but "
            "whether it is the second or third card, it will not be known.\n"
         << endl;
    // Player 1's first turn

    player1.drawCard();
    player1.drawCard();
    player2.drawCard();  // Player 2's first card
    player2.drawCard();

    // Player 1's turn
    char choice1;
    char choice2;
    while (true) {
      cout << "Player 1's turn.\n" << endl;
      cout << "\nPlayer 2's first card: " << player2.hand[0].value << endl;
      player1.displayHand(1);
      cout << "Do you want to draw another card? (y/n): ";
      cin >> choice1;

      if (toupper(choice1) == 'Y') {
        player1.drawCard();
        break;
      } else if (toupper(choice1) == 'N') {
        break;
      } else {
        cout << "Error input, please enter again\n";
        continue;
      }
    }

    clearScreen();
    // Player 2's turn
    while (true) {
      cout << "Player 2's turn.\n" << endl;
      cout << "\nPlayer 1's first card: " << player1.hand[0].value << endl;
      player2.displayHand(2);
      cout << "Do you want to draw another card? (y/n): ";
      cin >> choice2;

      if (toupper(choice2) == 'Y') {
        player2.drawCard();
        break;
      } else if (toupper(choice2) == 'N') {
        break;
      } else {
        cout << "Error input, please enter again\n";
        continue;
      }
    }

    clearScreen();
    while (toupper(choice1) == 'Y' || toupper(choice2) == 'Y') {
      if (toupper(choice1) == 'N' && toupper(choice2) == 'Y') {
        while (true) {
          cout << "Player 2's turn.\n" << endl;
          player2.displayHand(2);
          player1.displayLatestPlayerCard(player1.hand.back().value);
          cout << "Do you want to draw another card? (y/n): ";
          cin >> choice2;

          if (toupper(choice2) == 'Y') {
            player2.drawCard();
            clearScreen();
            break;
          } else if (toupper(choice2) == 'N') {
            clearScreen();
            break;
          } else {
            cout << "Error input, please enter again\n";
            continue;
          }
        }
      } else if (toupper(choice1) == 'Y' && toupper(choice2) == 'Y') {
        while (true) {
          cout << "Player 1's turn.\n" << endl;
          player1.displayHand(1);
          player2.displayLatestPlayerCard(player2.hand.back().value);
          cout << "Do you want to draw another card? (y/n): ";
          cin >> choice1;

          if (toupper(choice1) == 'Y') {
            player1.drawCard();
            clearScreen();
            break;
          } else if (toupper(choice1) == 'N') {
            clearScreen();
            break;
          } else {
            cout << "Error input, please enter again\n";
            continue;
          }
        }
      } else if (toupper(choice2) == 'N' && toupper(choice1) == 'Y') {
        while (true) {
          cout << "Player 1's turn.\n" << endl;
          player1.displayHand(1);
          player2.displayLatestPlayerCard(player2.hand.back().value);
          cout << "Do you want to draw another card? (y/n): ";
          cin >> choice1;

          if (toupper(choice1) == 'Y') {
            player1.drawCard();
            clearScreen();
            break;
          } else if (toupper(choice1) == 'N') {
            clearScreen();
            break;
          } else {
            cout << "Error input, please enter again\n";
            continue;
          }
        }
      }
    }
    clearScreen();
  }

  void determineWinner() {
    cout << "Player 1's score: " << player1.score << endl;
    cout << "Player 2's score: " << player2.score << endl << endl;
    if (player1.score > 21) {
      if (player2.score > player1.score) {
        cout << "Both players bust, but Player 1 wins due to Player 2 drawing "
                "higher"
             << endl;
      } else if (player2.score == player1.score) {
        cout << "It's a tie!" << endl;
      } else {
        cout << "Player 1 busts. Player 2 wins!" << endl;
      }
    } else if (player2.score > 21) {
      if (player1.score > player2.score) {
        cout << "Both players bust, but Player 2 wins due to Player 1 drawing "
                "higher"
             << endl;
      } else if (player1.score == player2.score) {
        cout << "It's a tie!" << endl;
      } else {
        cout << "Player 2 busts. Player 1 wins!" << endl;
      }
    } else if (player1.score > player2.score) {
      cout << "Player 1 wins!" << endl;
    } else if (player2.score > player1.score) {
      cout << "Player 2 wins!" << endl;
    } else {
      cout << "It's a tie!" << endl;
    }
  }
};

int main() {
  AbstractGame* game;
  char gameChoice;
  bool x = true;
  cout << "Please choose your game mode: Player vs Player (press P) or Player "
          "vs Computer (press C): ";
  cin >> gameChoice;

  while (x == true) {
    if (gameChoice == 'c' || gameChoice == 'C') {
      x = false;
      game = new BlackjackGame();
      game->start();
      game->determineWinner();
      delete game;
    } else if (gameChoice == 'p' || gameChoice == 'P') {
      x = false;
      game = new PokerGame();
      game->start();
      game->determineWinner();
      delete game;
    } else {
      cout << "Error input, please enter again (P or C): ";
      cin >> gameChoice;
    }
  }
  return 0;
}