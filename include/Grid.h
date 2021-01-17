#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include "Item.h"
#include "Spell.h"
#include "Living_Being.h"
#include "information.h"

using namespace std;


class Square;

class Grid{

    //Διαστασεις πλεγματος
    int x;
    int y;
    Square*** squares;

    int x_heroes;
    int y_heroes;

    void checkInventory( Hero*);
    void equip( Hero*);
    void use( Hero*);
    void print_Hero( Hero*)const;
    void move(vector <Hero*>);
    void quitGame();

    void displayMap()const;

    void buy_sell_and_equip( Hero*);
    
public:    
    Grid( int, int);
    ~Grid();


    void set_heroes( Hero*);
    void set_monsters( Monster*);
    void StartGame();
    void provide(Item*);
    void provide(Spell*);
};

class Square{
    string kind_of_square;
    vector < Hero* > heroes;
    vector < Monster* > monsters;
public:
    Square(string);
    virtual ~Square();
    void add_hero(Hero*);
    void add_monster(Monster*);
    vector<Hero*> remove_heroes();
    string get_kind_of_square() const;
    virtual int contains();
    int alive();
    void War();
    
    virtual bool buy( Hero*);
    virtual void sell( Hero*);

    virtual void insert_item(Item*){};
    virtual void insert_spell(Spell*){};

    vector<Hero*> get_heroes();
};

class nonAccessible:public Square{

public:
    nonAccessible():Square("nonAccessible"){};
    int contains();
};

class Market:public Square{
    vector <Item*> items;
    vector <Spell*> spells;
public:
    Market():Square("Market"){};
    ~Market();
    void insert_item(Item*);
    void insert_spell(Spell*);
    bool buy(Hero*);
    void sell(Hero*);
    int contains();
};

class Common:public Square{


public:
    Common():Square("Common"){};
    int contains();
};





#endif