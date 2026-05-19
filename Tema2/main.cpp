#include "cardCollection.h"
#include "cards.h"
#include "entity.h"
#include <iostream>
#include <random>
#include <string>

using namespace std;

static CardCompedium& CC = CardCompedium::getInstance(); // Aici se stocheaza toate cartiile
// Rand int
static random_device r;
static mt19937 rng(r());
static uniform_int_distribution<int> d10(1, 10);

void fight(Player &p, Monster &enemy) {
  int turn = 1;
  while (p.hp > 0 && enemy.hp > 0) {
    cout << "\n=== TURN " << turn << " ===\n";
    cout << p.name << " HP: " << p.hp << "/" << p.max_hp << " | Mana: " << p.mana << "/" << p.max_mana << "\n";
    cout << enemy.name << " HP: " << enemy.hp << "/" << enemy.max_hp << " | Mana: " << enemy.mana << "/" << enemy.max_mana << "\n";
    
    // Player Turn
    p.startTurn(2);
    bool playerTurnEnded = false;
    int player_input;
    int chosen_card;
    
    while (!playerTurnEnded && p.hp > 0 && enemy.hp > 0) {
      cout << "\nActiuni disponibile:\n";
      cout << "1: Show inventory\n";
      cout << "2: Show hand and play cards\n";
      cout << "0: End turn\n";
      cin >> player_input;

      if (player_input == 1) {
        p.showDeck();
      } else if (player_input == 2) {
        p.showHand();
        cout << "Select card to play (1 to N):\n0 to go back\n\n";
        cin >> chosen_card;
        while (chosen_card != 0) {
          p.playAndReturnToDeck(enemy, chosen_card - 1);
          if (enemy.hp <= 0) {
            playerTurnEnded = true;
            break;
          }
          p.showHand();
          cout << "Select card to play:\n0 to go back\n\n";
          cin >> chosen_card;
        }
      } else if (player_input == 0) {
        playerTurnEnded = true;
      }
    }
    // p.clearHand(); // Păstrăm cărțile pentru tura viitoare

    if (enemy.hp <= 0) {
      break;
    }

    // Monster Turn
    cout << "\n--- " << enemy.name << "'s Turn ---\n";
    enemy.startTurn(2);
    int monsterChoice = enemy.chooseCard();
    if (monsterChoice != -1) {
      enemy.playAndReturnToDeck(p, monsterChoice);
    } else {
      cout << enemy.name << " has no cards to play.\n";
    }
    turn++;
  }
  p.clearHand(); // Curatam mana jucatorului doar la finalul luptei
  cout << "\nEnd of fight\n\n";
}

void init() {
  string fileName = "cards.txt";
  CC.loadCardsFromFile(fileName);
}

int main() {
  init();
  Player a;
  a.addCardToDeck(CC.allCards[1]);
  a.addCardToDeck(CC.allCards[1]);
  a.addCardToDeck(CC.allCards[1]);
  a.addCardToDeck(CC.allCards[2]);
  a.addCardToDeck(CC.allCards[6]);
  a.showDeck();
  
  Monster LVL1("Villager", 10, 1, 10);
  LVL1.addCardToDeck(CC.allCards[1]);
  LVL1.addCardToDeck(CC.allCards[1]);

  Monster LVL2("Guard", 20, 1, 10);
  LVL2.addCardToDeck(CC.allCards[1]);
  LVL2.addCardToDeck(CC.allCards[2]);

  Monster LVL3("Hunter", 30, 1, 10);
  LVL3.addCardToDeck(CC.allCards[2]);
  LVL3.addCardToDeck(CC.allCards[2]);
  LVL3.addCardToDeck(CC.allCards[3]);
  
  fight(a, LVL1);
  if (a.hp > 0) {
    Shop shop1(CC);
    shop1.buyCards(a);
  }
  if (a.hp > 0)
    fight(a, LVL2);
  if (a.hp > 0) {
    Shop shop2(CC);
    shop2.buyCards(a);
  }
  if (a.hp > 0)
    fight(a, LVL3);
  return 0;
}