// rewardObserver.h
#ifndef TEMA2_REWARDOBSERVER_H
#define TEMA2_REWARDOBSERVER_H

#include "observer.h"
#include <iostream>

// Forward declare Player to avoid circular includes
class Player;

class RewardObserver : public IObserver {
    Player& player;
    int reward;
public:
    RewardObserver(Player& p, int reward) : player(p), reward(reward) {}

    void onDeath(const std::string& entityName) override;
};

#endif // TEMA2_REWARDOBSERVER_H