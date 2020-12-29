#include <iostream>
#include "Spell.h"

using namespace std;

//Συναρτήσεις για Spell.
Spell::Spell(string n, double p, int l, double low, double high, double e){
    this->name.assign(n);
    this->price = p;
    this->level = l;
    this->damage_low = low;
    this->damage_high = high;
    this->energy = e;
}

Spell::~Spell(){
    this->name.clear();
}

string Spell::get_name() const{
    return this->name;
}

double Spell::get_price() const{
    return this->price;
}

int Spell::get_level() const{
    return this->level;
}

double Spell::get_low_damage() const{
    return this->damage_low;
}

double Spell::get_high_damage() const{
    return this->damage_high;
}

double Spell::get_energy() const{
    return this->energy;
}

void Spell::set_low_damage(double d){
    this->damage_low = d;
}

//Συναρτήσεις για IceSpell.
IceSpell::IceSpell(string n, double p, int l, double dl, double dh, double e, double nl, int r):Spell(n, p, l, dl, dh, e){
    this->damage_low_new = nl;
    this->rounds = r;
    cout<<"New icespell has been created"<<endl;
}

IceSpell::~IceSpell(){
    cout<<"Icespell to be destroyed"<<endl;
}

double IceSpell::get_new_low() const{
    this->damage_low_new;
}

int IceSpell::get_rounds() const{
    this->rounds;
}

//Συναρτήσεις για FireSpell.
FireSpell::FireSpell(string n, double p, int l, double dl, double dh, double e, double dr, int r):Spell(n, p, l, dl, dh, e){
    this->defense_reduce = dr;
    this->rounds = r;
    cout<<"A new firespell has been created"<<endl;
}

FireSpell::~FireSpell(){
    cout<<"Firespell to be destroyed"<<endl;
}

double FireSpell::get_defense_reduce() const{
    return this->defense_reduce;
}

int FireSpell::get_rounds() const{
    return this->rounds;
}

//Συναρτήσεις για LightingSpell.
LightingSpell::LightingSpell(string n, double p, int l, double dl, double dh, double e, double dpr, int r):Spell(n, p, l, dl, dh, e){
    this->defense_prob_reduce = dpr;
    this->rounds = r;
    cout<<"A new lightingspellhas been created"<<endl;
}

LightingSpell::~LightingSpell(){
    cout<<"Lightingspell to be destroyed"<<endl;
}

double LightingSpell::get_defense_prob_reduce() const{
    return this->defense_prob_reduce;
}

int LightingSpell::get_rounds() const{
    return this->rounds;
}
