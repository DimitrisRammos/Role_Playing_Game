#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>
#include "Item.h"
#include "Spell.h"
#include "Living_Being.h"

using namespace std;

class Grid{
    //Διαστασεις πλεγματος
    int x;
    int y;
    Square*** squares;
public:    
    Grid(int, int);
    ~Grid();
};

class Square{
    vector < Hero* > heroes;
    vector < Monster* > monsters;
    string kind_of_square;
public:
    Square(string);
    void add_hero(Hero*);
    void add_monster(Monster*);
    void remove_heroes();
    string get_kind_of_square() const;
};

class nonAccessible:public Square{

public:
    nonAccessible():Square("nonAccessible"){};
};

class Market:public Square{
    
public:
    Market():Square("Market"){};
};

class Common:public Square{

public:
    Common():Square("Common"){};
};

#endif