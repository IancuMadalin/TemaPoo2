//
// Created by FrozenMada on 21/04/2026.
//

#include "entity.h"
#include <string>
#include <iostream>
#include <random>

static std::random_device r;
static std::mt19937 rng(r());

Entity::Entity(): name(""),max_hp(0),hp(0),max_mana(0),mana(0) {}

Entity::Entity(std::string name, int max_hp, int max_mana): name(name),max_hp(max_hp),hp(max_hp),max_mana(max_mana),mana(0) {}
Entity::Entity(Entity &other):name(other.name),max_hp(other.max_hp),hp(other.hp),
                                max_mana(other.max_mana),mana(other.mana){}
Entity::~Entity() {

}

Player::Player():Entity("Red",10,0),lvl(1),money(0),deck({}),hand({}){}

Player::Player(std::string name, int max_hp, int max_mana): Entity(name,max_hp,max_mana),lvl(1),money(0),deck({}),hand({}) {}

Player::~Player() {
    for (Card* card : deck) {
        delete card;
    }
}

void Player::addCardToDeck(Card *cardTemplate) {
    if (cardTemplate != nullptr) {
        deck.push_back(cardTemplate->clone());
    }
}

void Player::showDeck() const {
    std::cout << "--- " << name << "'s Inventory ---" << std::endl;
    if (deck.size() == 0) {
        std::cout << name << " is empty" << std::endl;
    }
    else {
        for (auto i : deck)
            {
        i->display();
            std::cout << "---------------------------\n";
            }
    }
}
void Player::showHand() const {
    std::cout << "--- " << name << "'s Hand ---" << std::endl;
    if (hand.size() == 0) {
        std::cout << name << "'s hand is empty" << std::endl;
    }
    else {
        for (auto i : hand) {
            i->display();
            std::cout << "---------------------------\n";
        }
    }
}

void Player::takeDamage(int dmg) {
    hp -= dmg;
    if (hp <= 0) {
        death();
    }
}

void Player::startTurn(int cardsDrawn) {
    while (cardsDrawn > 0 && deck.size() > 0) {
        std::uniform_int_distribution<int> draw(0,deck.size()-1);
        int selectedCard = draw(rng);
        hand.push_back(deck[selectedCard]);
        deck.erase(deck.begin()+selectedCard);
        cardsDrawn--;
    }
}
void Player::death() {
    std::cout << "--- " << name << "'s Death ---" << std::endl;
    std::cout << "ahhahahahahhaa Game over";
}

Monster::Monster():Entity("Generic Bad Guy",10,0),money_reward(0){}

Monster::Monster(std::string name, int max_hp, int max_mana, int money_reward):Entity(name,max_hp,max_mana),deck({}),money_reward(money_reward) {}

Monster::~Monster() {
    for (Card* card : deck) {
        delete card;
    }
}

void Monster::takeDamage(int dmg) {
    hp -= dmg;
    if (hp <= 0) {
        death();
    }
}
void Monster::death() {
    std::cout << "--- " << name << "'s Death ---" << std::endl;
    std::cout << "ahhahahahahahaa he ded";
}
