//
// Created by FrozenMada on 19/04/2026.
//

#include "cardCollection.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "cardFactory.h"

// NOTE: constructor and destructor are now defined inside the header (private)
// This file only contains the method implementations

void CardCompedium::loadCardsFromFile(std::string& fileName) {
    try {
        std::ifstream file(fileName);

        if (!file.is_open()) {
            throw std::runtime_error("Error: Could not open file " + fileName);
        }

        char type;
        std::string name;
        int id = 1, dmg, hits, cost, gain;

        while (file >> type) {
            if (type == 'A') {
                file >> name >> dmg >> hits;
                // FACTORY: centralized card creation
                allCards[id] = CardFactory::create(type, name, id, dmg, hits);
                id++;
            }
            else if (type == 'S') {
                file >> name >> dmg >> hits >> cost;
                // FACTORY: centralized card creation
                allCards[id] = CardFactory::create(type, name, id, dmg, hits, cost);
                id++;
            }
            else if (type == 'M') {
                file >> name >> gain;
                // FACTORY: centralized card creation
                allCards[id] = CardFactory::create(type, name, id, 0, 0, 0, gain);
                id++;
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "[CardCompedium Warning] " << e.what() << "\n";
        std::cout << "Continuing execution with an empty compendium.\n\n";
    }
}

std::ostream& operator<<(std::ostream& os, const CardCompedium& x) {
    os << "=== Master Card Library ===\n";
    for (auto const& [id, cardPtr] : x.allCards) {
        if (cardPtr != nullptr) {
            cardPtr->print();
            os << "---------------------------\n";
        }
    }
    return os;
}