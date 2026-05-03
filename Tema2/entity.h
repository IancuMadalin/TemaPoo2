//
// Created by FrozenMada on 19/04/2026.
//

#ifndef TEMA2_ENTITY_H
#define TEMA2_ENTITY_H
#include <string>
#include <vector>

#include "cards.h"


class Monster;

class Entity {
    public:
    std::string name;
    int max_hp;
    int hp;
    int max_mana;
    int mana;
    public:
    Entity();
    Entity(std::string name,int max_hp,int max_mana); //name(std::move(name)),max_hp(max_hp),hp(max_hp) {}
    Entity(Entity & other);
    virtual ~Entity();

    virtual void takeDamage(int dmg) = 0;
};

class Player: public Entity {
    public:
    int lvl;
    int money;
    std::vector<Card*> deck;
    std::vector<Card*> hand;
    public:
    Player();
    Player(std::string name,int max_hp,int max_mana);
    Player(Player & other);
    Player& operator=(const Player other);
    friend void swap(Player& first, Player& second) noexcept;

    ~Player();

    void addCardToDeck(Card * cardTemplate);
    void showDeck () const ;
    void showHand() const;
    void takeDamage(int dmg);
    void startTurn(int cardsDrawn);
    void playCard(Monster &target, const Attack& card);
    void playCard(Monster &target, const Spell& card);
    void playCard(Monster &target, const Mana& card);
    void playAndReturnToDeck(Monster &target,int handIndex);
    void clearHand();

    void death();
};

class Monster: public Entity {
protected:
    std::vector<Card*> deck;
    std::vector<Card*> hand;
    int money_reward;
    public:
    Monster();

    Monster(std::string name,int max_hp,int max_mana,int money_reward);
    ~Monster();
    void takeDamage(int dmg);
    void death();
};
#endif //TEMA2_ENTITY_H