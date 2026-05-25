//
// Created by FrozenMada on 21/05/2026.
//

#ifndef TEMA2_OBSERVER_H
#define TEMA2_OBSERVER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

// Abstract observer interface
class IObserver {
public:
    virtual void onDeath(const std::string& entityName) = 0;
    virtual ~IObserver() = default;
};

// Abstract subject (to be mixed into Entity)
class ISubject {
    std::vector<IObserver*> observers;
public:
    void addObserver(IObserver* obs) {
        observers.push_back(obs);
    }
    void removeObserver(IObserver* obs) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }
protected:
    void notifyDeath(const std::string& name) {
        for (auto* obs : observers)
            obs->onDeath(name);
    }
};

#endif //TEMA2_OBSERVER_H