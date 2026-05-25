//
// Created by FrozenMada on 21/04/2026.
//

#include "entity.h"
#include <iostream>
#include <random>
#include <string>
#include "cardCollection.h"


static std::random_device r;
static std::mt19937 rng(r());

Entity::Entity() : name(""), max_hp(0), hp(0), max_mana(0), mana(0) {}

Entity::Entity(std::string name, int max_hp, int max_mana)
    : name(name), max_hp(max_hp), hp(max_hp), max_mana(max_mana), mana(0) {}
Entity::Entity(Entity &other)
    : name(other.name), max_hp(other.max_hp), hp(other.hp),
      max_mana(other.max_mana), mana(other.mana) {}
Entity::~Entity() {}

Player::Player() : Entity("Red", 10, 0), lvl(1), money(0), deck({}), hand({}) {}

Player::Player(std::string name, int max_hp, int max_mana)
    : Entity(name, max_hp, max_mana), lvl(1), money(0), deck({}), hand({}) {}

Player::Player(Player &other)
    : Entity(other), lvl(other.lvl), money(other.money) {
  for (Card *c : other.deck) {
    this->deck.push_back(c->copy());
  }
  for (Card *c : other.hand) {
    this->hand.push_back(c->copy());
  }
}

void swap(Player &first, Player &second) noexcept {
  using std::swap;
  swap(first.name, second.name);
  swap(first.hp, second.hp);
  swap(first.max_hp, second.max_hp);
  swap(first.mana, second.mana);
  swap(first.max_mana, second.max_mana);
  swap(first.lvl, second.lvl);
  swap(first.money, second.money);
  swap(first.deck, second.deck);
  swap(first.hand, second.hand);
}

Player &Player::operator=(Player other) {
  swap(*this, other);
  return *this;
}

Player::~Player() {
  for (Card *card : deck) {
    delete card;
  }
  for (Card *card : hand) {
    delete card;
  }
}

void Player::addCardToDeck(Card *cardTemplate) {
  if (cardTemplate != nullptr) {
    deck.push_back(cardTemplate->copy());
  }
}

void Player::showDeck() const {
  std::cout << "--- " << name << "'s Inventory ---" << std::endl;
  if (deck.size() == 0) {
    std::cout << name << " is empty" << std::endl;
  } else {
    for (auto i : deck) {
      i->print();
      std::cout << "---------------------------\n";
    }
  }
}
void Player::showHand() const {
  std::cout << "--- " << name << "'s Hand ---" << std::endl;
  if (hand.size() == 0) {
    std::cout << name << "'s hand is empty" << std::endl;
  } else {
    for (auto i : hand) {
      i->print();
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
    std::uniform_int_distribution<int> draw(0, deck.size() - 1);
    int selectedCard = draw(rng);
    hand.push_back(deck[selectedCard]);
    deck.erase(deck.begin() + selectedCard);
    cardsDrawn--;
  }
}

void Player::playCard(Monster &target, const Attack &card) {
  int hits = card.get_hits();
  int dmg = card.get_dmg();
  for (int i = 0; i < hits; i++) {
    target.takeDamage(dmg);
  }
}

void Player::playCard(Monster &target, const Spell &card) {
  int cost = card.get_cost();
  int dmg = card.get_dmg();
  int hits = card.get_hits();
  if (cost > this->mana) {
    std::cout << "Not enough mana, spell failed to cast\n";
  } else {
    this->mana -= cost;
    for (int i = 0; i < hits; i++) {
      target.takeDamage(dmg);
    }
  }
}

void Player::playCard(Monster &target, const Mana &card) {
  int gain = card.get_gain();
  this->mana += gain;
  if (this->mana > this->max_mana) {
    this->mana = this->max_mana;
  }
}

void Player::playAndReturnToDeck(Monster &target, int handIndex) {
  if (handIndex < 0 || handIndex >= hand.size()) {
    std::cout << "Not a valid index\n";
    return;
  }
  Card *card = hand[handIndex];
  std::cout << "\n>>> " << this->name << " plays " << card->get_name() << "!\n";
  if (Attack *a = dynamic_cast<Attack *>(card)) {
    playCard(target, *a);
  } else {
    if (Spell *s = dynamic_cast<Spell *>(card)) {
      playCard(target, *s);
    } else {
      if (Mana *m = dynamic_cast<Mana *>(card)) {
        playCard(target, *m);
      }
    }
  }
  if (target.hp > 0 && this->hp > 0) {
    std::cout << this->name << " HP: " << this->hp << "/" << this->max_hp << " | Mana: " << this->mana << "/" << this->max_mana << "\n";
    std::cout << target.name << " HP: " << target.hp << "/" << target.max_hp << " | Mana: " << target.mana << "/" << target.max_mana << "\n\n";
  } else {
    std::cout << "\n";
  }

  deck.push_back(card);
  hand.erase(hand.begin() + handIndex);
}

void Player::clearHand() {
  for (Card *card : hand) {
    deck.push_back(card);
  }
  hand.clear();
}

void Player::death() {
  std::cout << "--- " << name << "'s Death ---" << std::endl;
  std::cout << "ahhahahahahhaa Game over";
}

Monster::Monster() : Entity("Generic Bad Guy", 10, 0), money_reward(0) {}

Monster::Monster(std::string name, int max_hp, int max_mana, int money_reward)
    : Entity(name, max_hp, max_mana), deck({}), money_reward(money_reward) {}

Monster::~Monster() {
  for (Card *card : deck) {
    delete card;
  }
}

void Monster::takeDamage(int dmg) {
  hp -= dmg;
  if (hp <= 0) {
    death();
    notifyDeath(name);
  }
}
void Monster::death() {
  std::cout << "--- " << name << "'s Death ---" << std::endl;
  std::cout << "Monster defeated\n";
}

void Monster::startTurn(int cardsDrawn) {
  while (cardsDrawn > 0 && deck.size() > 0) {
    std::uniform_int_distribution<int> draw(0, deck.size() - 1);
    int selectedCard = draw(rng);
    hand.push_back(deck[selectedCard]);
    deck.erase(deck.begin() + selectedCard);
    cardsDrawn--;
  }
}

void Monster::showHand() const {
  std::cout << "--- " << name << "'s Hand ---" << std::endl;
  if (hand.size() == 0) {
    std::cout << name << "'s hand is empty" << std::endl;
  } else {
    for (auto i : hand) {
      i->print();
      std::cout << "---------------------------\n";
    }
  }
}

void Monster::showDeck() const {
  std::cout << "--- " << name << "'s Inventory ---" << std::endl;
  if (deck.size() == 0) {
    std::cout << name << " is empty" << std::endl;
  } else {
    for (auto i : deck) {
      i->print();
      std::cout << "---------------------------\n";
    }
  }
}

void Monster::playCard(Player &target, const Attack &card) {
  int hits = card.get_hits();
  int dmg = card.get_dmg();
  for (int i = 0; i < hits; i++) {
    target.takeDamage(dmg);
  }
}

void Monster::playCard(Player &target, const Mana &card) {
  int gain = card.get_gain();
  this->mana += gain;
  if (this->mana > this->max_mana) {
    this->mana = this->max_mana;
  }
}

void Monster::playCard(Player &target, const Spell &card) {
  int cost = card.get_cost();
  int dmg = card.get_dmg();
  int hits = card.get_hits();
  if (cost > this->mana) {
    std::cout << "Not enough mana, spell failed to cast\n";
  } else {
    this->mana -= cost;
    for (int i = 0; i < hits; i++) {
      target.takeDamage(dmg);
    }
  }
}

void Monster::playAndReturnToDeck(Player &target, int handIndex) {
  if (handIndex < 0 || handIndex >= hand.size()) {
    std::cout << "Not a valid index\n";
    return;
  }
  Card *card = hand[handIndex];
  std::cout << "\n>>> " << this->name << " plays " << card->get_name() << "!\n";
  if (Attack *a = dynamic_cast<Attack *>(card)) {
    playCard(target, *a);
  } else {
    if (Spell *s = dynamic_cast<Spell *>(card)) {
      playCard(target, *s);
    } else {
      if (Mana *m = dynamic_cast<Mana *>(card)) {
        playCard(target, *m);
      }
    }
  }
  if (target.hp > 0 && this->hp > 0) {
    std::cout << target.name << " HP: " << target.hp << "/" << target.max_hp << " | Mana: " << target.mana << "/" << target.max_mana << "\n";
    std::cout << this->name << " HP: " << this->hp << "/" << this->max_hp << " | Mana: " << this->mana << "/" << this->max_mana << "\n\n";
  } else {
    std::cout << "\n";
  }

  deck.push_back(card);
  hand.erase(hand.begin() + handIndex);
}

int Monster::chooseCard() {
  if (hand.empty()) return -1;
  std::uniform_int_distribution<int> draw(0, hand.size() - 1);
  int selectedCard = draw(rng);
  return selectedCard;
}

void Monster::addCardToDeck(Card *cardTemplate) {
  if (cardTemplate != nullptr) {
    deck.push_back(cardTemplate->copy());
  }
}

void Monster::clearHand() {
  for (Card *card : hand) {
    deck.push_back(card);
  }
  hand.clear();
}

Shop::Shop(const CardCompedium& comp) {
  // Extragem ID-uri random (in cardCollection ID-urile incep de la 1)
  std::uniform_int_distribution<int> dist(1, comp.allCards.size());
  
  // Stocam pointeri catre cartile originale din Compedium
  option1 = comp.allCards.at(dist(rng));
  option2 = comp.allCards.at(dist(rng));
  option3 = comp.allCards.at(dist(rng));
}

Shop::~Shop() {
  // Nu dăm delete la option1/2/3 pentru că ele aparțin lui CardCompedium
}

void Shop::buyCards(Player &player) {
  std::cout << "\n========== SHOP ==========\n";
  std::cout << "1: "; option1->print(); std::cout << "---------------------------\n";
  std::cout << "2: "; option2->print(); std::cout << "---------------------------\n";
  std::cout << "3: "; option3->print(); std::cout << "---------------------------\n";
  std::cout << "0: Leave\n";
  std::cout << "==========================\n";
  std::cout << "Alege o carte pe care sa o adaugi in pachet: ";
  
  int choice;
  std::cin >> choice;
  if (choice == 1) {
    player.addCardToDeck(option1);
    std::cout << ">> " << option1->get_name() << " a fost adaugata in pachet!\n";
  } else if (choice == 2) {
    player.addCardToDeck(option2);
    std::cout << ">> " << option2->get_name() << " a fost adaugata in pachet!\n";
  } else if (choice == 3) {
    player.addCardToDeck(option3);
    std::cout << ">> " << option3->get_name() << " a fost adaugata in pachet!\n";
  } else {
    std::cout << ">> Ai plecat din magazin fara sa cumperi nimic.\n";
  }
}
