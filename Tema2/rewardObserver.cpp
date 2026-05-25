//
// Created by FrozenMada on 21/05/2026.
//

#include "rewardObserver.h"
#include "entity.h"
#include <iostream>

void RewardObserver::onDeath(const std::string& entityName) {
    player.money += reward;
    std::cout << ">> " << entityName << " defeated! You earned "
              << reward << " gold. Total: " << player.money << " gold.\n";
}