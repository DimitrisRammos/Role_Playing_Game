#include "Living_Being.h";


Living_Being::Living_Being( string name, double healthPower, string life_being)
{
    this->name = name;
    this->level = 1;
    this->healthPower = healthPower;

    this->life_being = life_being;

    in_life = false;
}

//get

string Living_Being::get_name()const
{
    return name;
}

double Living_Being::get_healthPower()const
{
    return healthPower;
}

int Living_Being::get_level()const
{
    return level;
}



void Living_Being::level_up()
{
    level++;
}
/////////////////////////////////








//HERO

Hero::Hero( string name, double healthPower, double magicPower, double strenght, double dexterity, double agility, double money, string hero) 
            : Living_Being( name, healthPower, "Hero")
{
    this->magicPower = magicPower;
    this->strength = strenght;
    this->dexterity = dexterity;
    this->agility = agility;
    this->hero = hero;

    this->money = money;

    //η εμπειρια αρχικοποειται 0 και μεγαλωνει αναλογα με τις ενεργειες
    //του ηρωα
    this->experience = 0;
}



double Hero::get_magicPower()const
{
    return magicPower;
}

double Hero::get_strength()const
{
    return strength;
}

double Hero::get_dexterity()const
{
    return dexterity;
}

double Hero::get_agility()const
{
    return agility;
}

double Hero::get_money()const
{
    return money;
}

double Hero::get_experience()const
{
    return experience;
}

//SET

void Hero::set_strength( double strength)
{
    this->strength = strength;
}

void Hero::set_dexterity( double dexterity)
{
    this->dexterity = dexterity; 
}

void Hero::set_agility( double agility)
{
    this->agility = agility;
}

void Hero::set_money( double money)
{
    this->money = money;
}

void Hero::set_experience( double experience)
{
    this->experience = experience;
}


//ανεβαινει επιπεδο
void Hero::level_up()
{

    strength = strength + strength*point;
    dexterity = dexterity + dexterity*point;
    agility = agility + agility*point;
    

    Living_Being::level_up();
}



//for buy spell and item
void Hero::buy_Item( Item item)
{
    item_vector.push_back( item);
}

void Hero::buy_Spell( Spell spell)
{
    spell_vector.push_back( spell);
}


//for sell spell and item

//επιστρεφω  true αν υπαρχει το στοιχειο και τοτε αφαιρειται
//αλλιως false
bool Hero::sell_Item( int position)
{   
    int size = item_vector.size(); 

    if( position >= 0 && position < size)
    {
        Item item_in = item_vector.at(position);
        Item it = item_vector.at( size - 1);
    
        item_vector.assign( position, it);
        item_vector.assign( size -1, item_in);

        item_vector.pop_back();
        return true;
    }

    return false;
}

//επιστρεφω  true αν υπαρχει το στοιχειο και τοτε αφαιρειται
//αλλιως false
bool Hero::sell_Spell( int position)
{
    int size = spell_vector.size(); 
    if( position >= 0 && position < size )
    {
        Spell spell_in = spell_vector.at(position);
        Spell sp = spell_vector.at( size - 1);
        
        spell_vector.assign( position, sp);
        spell_vector.assign( size -1, spell_in);

        spell_vector.pop_back();
        return true;
    }

    return false;
}


//print list for spell and item
void Hero::print_spell()const
{   
    int size = spell_vector.size();
    for( int i =0; i < size; i++ )
    {
        Spell spell = spell_vector.at(i);
        spell.print();
    }
}

void Hero::print_item()const
{
    int size = item_vector.size();
    for( int i =0; i < size; i++ )
    {
        Item item = item_vector.at(i);
        item.print();
    }
}




////////////////////////////////////







//WARRIOR
Warrior::Warrior( string name, double healthPower, double magicPower, double strenght, double dexterity, double agility, double money)
        : Hero( name, healthPower, magicPower, strenght, dexterity, agility, money, "Warrior"){}

void Warrior::level_up()
{
    double strength = get_strength();
    strength = strength + strength*point_strength;
    set_strength( strength);

    double agility = get_agility();
    agility = agility + agility*point_agility;
    set_agility( agility);
    
    Hero::level_up();
}
/////////////////////////////////


//SORCERER
Sorcerer::Sorcerer( string name, double healthPower, double magicPower, double strenght, double dexterity, double agility, double money)
        : Hero( name, healthPower, magicPower, strenght, dexterity, agility, money, "Sorcerer"){}

void Sorcerer::level_up()
{
    double dexterity = get_dexterity();
    dexterity = dexterity + dexterity*point_dexterity;
    set_dexterity( dexterity);

    double agility = get_agility();
    agility = agility + agility*point_agility;
    set_agility( agility);
    
    Hero::level_up();
}

//////////////////////////


//PALADIN
Paladin::Paladin( string name, double healthPower, double magicPower, double strenght, double dexterity, double agility, double money)
        : Hero( name, healthPower, magicPower, strenght, dexterity, agility, money, "Paladin"){}

void Paladin::level_up()
{
    double strength = get_strength();
    strength = strength + strength*point_strength;
    set_strength( strength);

    double dexterity = get_dexterity();
    dexterity = dexterity + dexterity*point_dexterity;
    set_dexterity( dexterity);

    Hero::level_up();
}

////////////////////////////




//MONSTER

Monster::Monster( string name, double healthPower, double attack, double defence, double probability_of_escape, string monster)
        : Living_Being( name, healthPower, "Monster")
{
    this->attack = attack;
    this->defence = defence;
    this->probability_οf_escape = probability_of_escape;

    this->monster = monster;

}


double Monster::get_attack()const
{
    return attack;
}

double Monster::get_defence()const
{
    return defence;
}

double Monster::get_probability_of_escape()const
{
    return probability_οf_escape;
}

///////////////////////////////////////




//DRAGON
Dragon::Dragon( string name, double healthPower, double attack, double defence, double probability_of_escape)
        : Monster( name, healthPower, attack + point_attack*attack, defence, probability_of_escape, "Dragon"){}
///////////////////////////////////////

//EXOSKELETION
Exoskeleton::Exoskeleton( string name, double healthPower, double attack, double defence, double probability_of_escape)
        : Monster( name, healthPower, attack, defence + defence*point_defence, probability_of_escape, "Exoskeletion"){}

//////////////////////////////////////

//SPIRIT
Spirit::Spirit( string name, double healthPower, double attack, double defence, double probability_of_escape)
        : Monster( name, healthPower, attack , defence, probability_of_escape + point_probability_οf_escape*probability_of_escape, "Spirit"){}

//////////////////////////////////////
