//
// Created by FrozenMada on 14/04/2026.
//

#ifndef TEMA2_CARDS_H
#define TEMA2_CARDS_H
#include <string>
class Card {
    std::string name;
    int id;
    public:
        Card();
        Card(std::string name, int id);
        Card(Card const & other);
        virtual ~Card();

    std::string get_name() const;
    int get_id() const;

    void set_name(std::string const &name);
    void set_id(int id);
    // --- NVI: PUBLIC NON-VIRTUAL INTERFACE ---
    void print() const;
    Card* copy() const;

    protected:
    // --- NVI: PROTECTED VIRTUAL IMPLEMENTATION ---
    virtual void display() const = 0;
    virtual Card* clone() const = 0;
};

class Attack: public Card{
    int dmg;
    int hits;

    public:
    Attack();
    Attack(std::string name,int id, int dmg, int i);
    Attack(Attack const & other);
    ~Attack();

    int get_dmg() const;
    int get_hits() const;

    void set_dmg(int dmg);
    void set_hits(int i);

protected:
    void display() const override;
    Card* clone() const override;
};

class Spell: public Card {
    int dmg;
    int hits;
    int cost;
    public:
    Spell();
    Spell(std::string name,int id, int dmg, int hits,int cost);
    Spell(Spell const & other);
    ~Spell();

    int get_dmg() const;
    int get_hits() const;
    int get_cost() const;

    void set_dmg(int dmg);
    void set_hits(int i);
    void set_cost(int cost);
protected:
    void display() const override;
    Card* clone() const override;
};

class Mana: public Card {
    int mana_gain;
public:
    Mana();
    Mana(std::string name,int id, int gain);
    Mana(Mana const & other);
    ~Mana();

    int get_gain() const;

    void set_gain(int gain);
protected:
    void display() const override;
    Card* clone() const override;

};
#endif //TEMA2_CARDS_H