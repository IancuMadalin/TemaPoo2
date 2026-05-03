#include <iostream>
#include <string>
#include <random>
#include "cards.h"
#include "cardCollection.h"
#include "entity.h"

using namespace std;

static CardCompedium CC; //Aici se stocheaza toate cartiile
//Rand int
static random_device r;
static mt19937 rng(r());
static uniform_int_distribution<int> d10(1,10);

void fight(Player p, Monster &enemy) {
    while (p.hp > 0 && enemy.hp > 0) {
        p.startTurn(2);
        cout<<"Actiuni disponibile:\n";
        cout<<"1: Show inventory\n";
        cout<<"2: Show hand\n";
        int player_input;
        int chosen_card;
        cin>>player_input;

            if (player_input == 1) {
                p.showDeck();
            }
            if (player_input == 2) {
                p.showHand();
                cout<<"Select card to play:\n0 to end the turn early\n\n";
                cin>>chosen_card;
                while (chosen_card !=0) {
                    p.playAndReturnToDeck(enemy,chosen_card-1);
                    p.showHand();
                    cout<<"Select card to play:\n0 to end the turn early\n\n";
                    cin>>chosen_card;
                }
            }
    }
    cout<<"End of fight\n \n";
    p.clearHand();
}


void init() {
    string fileName="cards.tx";
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
    Monster LVL1("Villager",10,1,1);
    Monster LVL2("Guard",20,1,1);
    Monster LVL3("Hunter",30,1,1);
    fight(a,LVL1);
    fight(a,LVL2);
    fight(a,LVL3);


    return 0;
}