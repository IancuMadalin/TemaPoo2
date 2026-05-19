//
// Created by FrozenMada on 20/05/2026.
//

#ifndef TEMA2_CARDFACTORY_H
#define TEMA2_CARDFACTORY_H

#include "cards.h"
#include <string>

class CardFactory {
public:
    // FACTORY PATTERN: single static method that centralizes all card creation
    // Default parameters handle the fact that different card types need different args
    static Card* create(char type, std::string name, int id,
                        int dmg=0, int hits=0, int cost=0, int gain=0) {
        if (type == 'A') return new Attack(name, id, dmg, hits);
        if (type == 'S') return new Spell(name, id, dmg, hits, cost);
        if (type == 'M') return new Mana(name, id, gain);
        return nullptr; // unknown type
    }
};

#endif //TEMA2_CARDFACTORY_H