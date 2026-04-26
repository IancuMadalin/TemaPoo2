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


void init() {
    string fileName="cards.txt";
    CC.loadCardsFromFile(fileName);
}

int main() {
    init();
    Player a("guy",10,0);
    a.addCardToDeck(CC.allCards[1]);
    a.addCardToDeck(CC.allCards[2]);
    a.addCardToDeck(CC.allCards[3]);
    a.addCardToDeck(CC.allCards[4]);
    cout<<"Before \n";
    a.showDeck();
    a.showHand();
    a.startTurn(3);
    cout<<"After \n";
    a.showDeck();
    a.showHand();


    return 0;
}