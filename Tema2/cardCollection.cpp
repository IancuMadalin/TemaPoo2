//
// Created by FrozenMada on 19/04/2026.
//

#include "cardCollection.h"
#include <iostream>
#include <fstream>
#include <iostream>

CardCompedium::CardCompedium() {
    // We leave this empty for now; we'll call loadCardsFromFile manually
}

CardCompedium::~CardCompedium() {
    // Clean up the Heap!
    // We loop through the map and delete every "Original" card
    for (auto const& [id, cardPtr] : allCards) {
        delete cardPtr;
    }
    std::cout << "Database cleaned up successfully.\n";
}

void CardCompedium::loadCardsFromFile(std::string &fileName) {
    std::ifstream file(fileName);
    char type;
    std::string name;
    int id=1,dmg,hits,cost,gain;
    while (file>>type) {
        if (type == 'A') {
            file>>name>>dmg>>hits;
            allCards[id] = new Attack(name,id,dmg,hits);
            id++;
        }
        if (type == 'S') {
            file>>name>>dmg>>hits>>cost;
            allCards[id] = new Spell(name,id,dmg,hits,cost);
            id++;
        }
        if (type == 'M') {
            file>>name>>gain;
            allCards[id] = new Mana(name,id,gain);
            id++;
        }
    }
}

Card *CardCompedium::createCard(int id) {
    if (allCards.find(id) != allCards.end()) {
        return allCards[id]->clone(); // Return a copy for the player to use
    }
    return nullptr; // Card ID not found
}

std::ostream& operator<<(std::ostream& os, const CardCompedium& x) {
    os << "=== Master Card Library ===\n";

    for (auto const& [id, cardPtr] : x.allCards) {
        if (cardPtr != nullptr) {
            // We call the virtual display() method you already wrote
            cardPtr->display();
            os << "---------------------------\n";
        }
    }
    return os; // Return the stream so you can chain: cout << db << endl;
}
