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
private:
    // SINGLETON: private constructor
    CardCompedium() {}
    ~CardCompedium() {
        for (auto const& [id, cardPtr] : allCards) {
            delete cardPtr;
        }
        std::cout << "Database cleaned up successfully.\n";
    }

public:
    // SINGLETON: delete copy constructor and assignment operator
    CardCompedium(CardCompedium const&) = delete;
    void operator=(CardCompedium const&) = delete;

    // SINGLETON: the one and only way to get the instance
    static CardCompedium& getInstance() {
        static CardCompedium instance;
        return instance;
    }

    std::map<int, Card*> allCards;

    void loadCardsFromFile(std::string& fileName);

    friend std::ostream& operator<<(std::ostream& os, const CardCompedium& x);
};

#endif //TEMA2_CARDCOLLECTION_H