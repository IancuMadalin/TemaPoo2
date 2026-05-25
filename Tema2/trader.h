//
// Created by FrozenMada on 22/05/2026.
//

#ifndef TEMA2_TRADER_H
#define TEMA2_TRADER_H

#include "cards.h"
#include "cardCollection.h"
#include "entity.h"
#include <random>
#include <vector>
#include <iostream>

template <typename T>
class Trader {
    std::string traderName;
    std::mt19937& rng;

public:
    Trader(std::string name, std::mt19937& rng)
        : traderName(name), rng(rng) {}
    // Player gives a card index from their deck, gets a random T back
    void trade(Player& player, int deckIndex, const CardCompedium& comp) {
        // Guard: check the chosen card is actually of type T
        if (dynamic_cast<T*>(player.deck[deckIndex]) == nullptr) {
            std::cout << traderName << " can't trade that type of card.\n";
            return;
        }

        std::vector<T*> available;
        for (auto const& [id, cardPtr] : comp.allCards) {
            if (T* typed = dynamic_cast<T*>(cardPtr)) {
                available.push_back(typed);
            }
        }

        if (available.empty()) {
            std::cout << traderName << " has no cards of that type to offer.\n";
            return;
        }


        Card* given = player.deck[deckIndex];
        std::cout << traderName << " takes your " << given->get_name() << ".\n";
        delete given;
        player.deck.erase(player.deck.begin() + deckIndex);

        // Step 3 — give back a random T from compendium
        std::uniform_int_distribution<int> dist(0, available.size() - 1);
        T* received = available[dist(rng)];
        player.deck.push_back(received->copy());
        std::cout << traderName << " gives you " << received->get_name() << "!\n";
    }

    void greet() const {
        std::cout << "=== " << traderName << " the Trader ===\n";
        std::cout << "Give me a card, I'll give you one of the same type back.\n";
    }
};

template <typename T>
void traderInteraction(Trader<T>& trader, Player& player, const CardCompedium& comp) {
    trader.greet();
    player.showDeck();
    std::cout << "Choose a card index to trade: ";
    int tradeIndex;
    std::cin >> tradeIndex;

    while (tradeIndex < 1 || tradeIndex > (int)player.deck.size()) {
        std::cout << "Not a valid index, please choose a valid card\n";
        std::cin >> tradeIndex;
    }
    trader.trade(player, tradeIndex - 1, comp);
}


template <typename T>
void describeTrader(const Trader<T>& trader) {
    trader.greet();
}

#endif //TEMA2_TRADER_H