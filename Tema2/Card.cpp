//
// Created by FrozenMada on 14/04/2026.
//
#include <iostream>
#include <string>
#include <utility>
#include "cards.h"

Card::Card(): name(""),id(0) {}
Card::Card(std::string name, int id): name(std::move(name)), id(id) {}
Card::Card(Card const & other):name(other.name),id(other.id) {}
Card::~Card() {}

int Card::get_id() const { return id;}
std::string Card::get_name() const { return name;}

void Card::set_name(std::string  const &name) { this->name=name;}
void Card::set_id(int const id) { this->id=id;}

Attack::Attack(): dmg(0),hits(0) {}
Attack::Attack(std::string name, const int id, const int dmg, const int i):Card(std::move(name),id),dmg(dmg), hits(i) {}
Attack::Attack(Attack const &other): Card(other),dmg(other.dmg),hits(other.hits) {}
Attack::~Attack(){}

int Attack::get_dmg() const {
    return dmg;
}
int Attack::get_hits() const {
    return hits;
}
void Attack::set_dmg(int dmg) {
    this->dmg=dmg;
}
void Attack::set_hits(int i) {
    this->hits=i;
}

void Attack::display() const {
    std::cout<<"Name: "<<this->get_name()<<"\n";
    std::cout<<"Id: "<<this->get_id()<<"\n";
    std::cout<<"Dmg: "<<this->get_dmg()<<" * "<<this->get_hits()<<" = "<<this->get_dmg()*this->get_hits()<<"\n";
}

Card* Attack::clone() const { return new Attack(*this); }

Spell::Spell(): dmg(0),hits(0),cost(0){}
Spell::Spell(std::string name, const int id, const int dmg, const int hits, const int cost):Card(std::move(name),id), dmg(dmg), hits(hits), cost(cost) {}
Spell::Spell(Spell const & other): Card(other),dmg(other.dmg),hits(other.hits),cost(other.cost) {}
Spell::~Spell() {}

int Spell::get_dmg() const {
    return dmg;
}
int Spell::get_hits() const {
    return hits;
}
int Spell::get_cost() const {
    return cost;
}
void Spell::set_dmg(int dmg) {
    this->dmg=dmg;
}
void Spell::set_hits(int i) {
    this->hits=i;
}
void Spell::set_cost(int cost) {
    this->cost = cost;
}

void Spell::display() const {
    std::cout<<"Name: "<<this->get_name()<<"\n";
    std::cout<<"Id: "<<this->get_id()<<"\n";
    std::cout<<"Cost: "<<this->get_cost()<<"\n";
    std::cout<<"Dmg: "<<this->get_dmg()<<" * "<<this->get_hits()<<" = "<<this->get_dmg()*this->get_hits()<<"\n";
}
Card* Spell::clone() const { return new Spell(*this); }

Mana::Mana():mana_gain(0) {}
Mana::Mana(std::string name, int id, int gain):Card(name,id),mana_gain(gain) {}
Mana::Mana(Mana const &other):Card(other),mana_gain(other.mana_gain) {}
Mana::~Mana(){}

int Mana::get_gain() const { return mana_gain; }
void Mana::set_gain(int gain) { mana_gain=gain; }

void Mana::display() const {
    std::cout<<"Name: "<<this->get_name()<<"\n";
    std::cout<<"Id: "<<this->get_id()<<"\n";
    std::cout<<"Gain: "<<this->get_gain()<<"\n";
}
Card* Mana::clone() const { return new Mana(*this); }

