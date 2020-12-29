#ifndef LIVING_BEING_H
#define LIVING_BEING_H

#include <string>
using namespace std;

class Living_Being{
    string name;
    int level;
    double healthPower;

    string life_being;
    bool in_life;
    
    public:

    Living_Being( string, double, string);

    virtual void level_up();

    //get
    string get_name()const;
    double get_healthPower()const;
    int get_level()const;

};


class Hero : public Living_Being{
    double magicPower; //ποσο μαγικης ενεργειας
    double strength;  //τιμη δυναμης
    double dexterity; //τιμη επιδεξιοτητας
    double agility;   //τιμης ευκυνισιας

    double money;     //ποσο χρηματων που διαθετει ο ηρωας
    double experience; //ποσο εμπειριας ηρωα

    //who hero
    string hero;

    static const double point = 1;

    public:

    Hero( string, double, double, double, double, double, double, double, string);
    void level_up();
};


class Warrior : public Hero{
    public:

    static const double point_strength = 0.8;
    static const double point_agility = 0.5;

    Warrior( string, double, double, double, double, double, double, double);;
};

class Sorcerer : public Hero{
    public:

    static const double point_dexterity = 0.7;
    static const double point_agility = 0.6;

    Sorcerer(  string, double, double, double, double, double, double, double);
};

class Paladin : public Hero{
    public:

    static const double point_strength = 0.9;
    static const double point_dexterity = 0.7;

    Paladin(  string, double, double, double, double, double, double, double);
};






#endif