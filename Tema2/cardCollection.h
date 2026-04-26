//
// Created by FrozenMada on 19/04/2026.
//

#ifndef TEMA2_CARDCOLLECTION_H
#define TEMA2_CARDCOLLECTION_H

#include <map>
#include <iostream>
#include <string>
#include "cards.h"

class CardCompedium {
public: // make protected later
    std::map<int,Card*> allCards;
    public:

    CardCompedium();
    ~CardCompedium();

    void loadCardsFromFile(std::string& fileName);
    Card* createCard(int id);

    friend std::ostream& operator<<(std::ostream& os, const CardCompedium& x);
};

#endif //TEMA2_CARDCOLLECTION_H