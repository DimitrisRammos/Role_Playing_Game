#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Grid.h"

//Συναρτήσεις για Grid.
Grid::Grid(int x, int y){
    this->x = x;
    this->y = y;

    x_heroes = -1;
    y_heroes = -1;

    srand(time(NULL));
    squares = new Square**[x];
    for(int i = 0; i < x; i++)
    {
        squares[i] = new Square*[y];
    }

    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            int r = rand() % 10;
            if(r == 1)
                this->squares[i][j] = new nonAccessible();
            else if(r == 3 || r == 7)
                this->squares[i][j] = new Market();
            else
                this->squares[i][j] = new Common();
        }
    }
}

Grid::~Grid(){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            delete this->squares[i][j];
        }
    }
}

//βαζω τους ηρωες σε ενα τυχαιο market τετραγωνο
void Grid::set_heroes( Hero* hero)
{   
    
    if( x_heroes == -1)
    {
        srand( time(NULL));
        bool in = false;
        while( in != true)
        {   
            x_heroes = rand()%(x);
            y_heroes = rand()%(y);
            if( (squares[x_heroes][y_heroes]->get_kind_of_square()).compare( "Market") == 0)
            {
                in = true;
            }
        }
    }

    hero->set_x( x_heroes);
    hero->set_y( y_heroes);
    squares[x_heroes][y_heroes]->add_hero( hero);
}

void Grid::set_monsters( Monster* monster)
{
    // srand(time(NULL));
    bool in = false;
    int x1;
    int y1;
    while( in != true)
    {   
        x1 = rand()%x;
        y1 = rand()%y;
        if( (squares[x1][y1]->get_kind_of_square()).compare( "Common") == 0)
        {   

            //αν ειναι common τοτε 1/10 ειναι nonaccesible 2/10 store
            //kai 7/10 common
            //αρα αποφασιζουμε τυχαια με πιθανοτητα 3/7 να ναι monster sto grid
            //αλλιως οχι
            int num_rand = rand()%7;
            if( num_rand <= 3)
            {
                squares[x1][y1]->add_monster( monster);
            }

            in = true;
        }   
    }
}




//SOSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS

//MIN ΞΕΧΑΣΟΥΜΕ ΟΤΑΝ ΕΝΑΣ ΗΡΩΑΣ ΑΝΕΒΑΙΝΕΙ LEVEL prepei analoga
//to level na αυξανονται κατα καποιο ποσο τα λεφτα του

///////////////////////

void Grid::StartGame()
{
    //οι ηρωες ειναι τοποθετιμενοι εξαρχης σε ενα τετραγωνο
    //Market πρεπει να αγορασουν τουλαχιστον ενα Weapon για την μαχη
    //εχουν καποια αρχικα λεφτα ωστε να αγορασουν


    
    vector<Hero*> vector_heroes;
    vector_heroes = squares[x_heroes][y_heroes]->get_heroes();
    

    for(unsigned int i = 0; i < vector_heroes.size(); i++)
    {   
        bool buy_weapon = false;
        Hero* hero =  vector_heroes.at(i);
        while(buy_weapon == false){
            cout << RED << "You must buy a Weapon for " << hero->get_name() << RESET << endl;
            buy_weapon = squares[x_heroes][y_heroes]->buy( hero);
            if( hero->get_money() == 0 && buy_weapon == false)
            {
                cout << RED << "YOU LOSE!!!, BECAUSE YOU HAVN'T MONEY A1ND YOU HAVN'T WEAPON FOR WAR!!!" << RESET << endl;
                quitGame();
            }
        }
    }
    
    bool level_heroes = false;
    while( level_heroes == false)
    {   
        string kind_of_square = squares[x_heroes][y_heroes]->get_kind_of_square();
        if( kind_of_square.compare( "Market") == 0)
        {   
            for(unsigned int i = 0; i < vector_heroes.size(); i++)
            {   
                Hero* hero =  vector_heroes.at(i);
                cout << "Hero: " << hero->get_hero() << " " << endl;    
                buy_sell_and_equip( hero);
            }
        }
        else if( kind_of_square.compare( "Common") == 0)
        {
            squares[x_heroes][y_heroes]->War();
        }

        move( vector_heroes);

        displayMap();

        //αν ολοι οι ηρωες εχον φτασει
        //στο max level τοτε το παιχνιδι τελειωσε
        unsigned int size_max_level = 0;
        for(unsigned int i = 0; i < vector_heroes.size(); i++)
        {
            Hero* hero =  vector_heroes.at(i);
            if( hero->get_level() == MAX_LEVEL)
            {
                size_max_level++;
            }
        }
        if( size_max_level == vector_heroes.size())
        {
            level_heroes = true;
        }
    }

    displayMap();
    
}


void Grid::checkInventory( Hero* hero)
{
    hero->print_item();
}

void Grid::equip( Hero* hero)
{
    cout << "Τι θελετε να αλλαξετε;" << endl;
    cout << "1) Weapon" << endl;
    cout << "2) Armor" << endl;

    //δεχομαστε 1 ή 2 απο χρηστη
    int in;
    cin >> in; 
    while( in != 1 && in != 2)
    {
        cout << RED << "Δεν ηταν εγκυρη η επιλογη σας! Προσπαθηστε ξανα." << RESET << endl;
        cin >> in;
    }
    
    if( in == 1)
    {
        cout << "What you want to take?" << endl;
        int number_Weapon = hero->print_Weapon();
        int w;
        if(number_Weapon != 0)
        {
            
            cin >> w;
            while( w <= 0 || w > number_Weapon)
            {
                cout << RED << "Δεν ηταν εγκυρη η επιλογη σας! Προσπαθηστε ξανα." << RESET << endl;
                cin >> w;
            }


            hero->set_Weapon( w - 1);
        }
    }
    else
    {
        cout << "What you want to take?" << endl;
        int number_Armor = hero->print_Armor();
        int a;
        if(number_Armor != 0)
        {
            cin >> a;
            while( a <= 0 || a > number_Armor)
            {
                cout << RED << "Δεν ηταν εγκυρη η επιλογη σας! Προσπαθηστε ξανα." << RESET << endl;
                cin >> a;
            }

            hero->set_Armor( a - 1);
        }
    }

}

void Grid::use( Hero* hero)
{
    cout << "What potion you want to use?" << endl;
    int number_Potion = hero->print_Potion();
    int p;
    if(number_Potion != 0)
    {
        cin >> p;
        while( p <= 0 || p > number_Potion)
        {
            cout << RED << "Δεν ηταν εγκυρη η επιλογη σας! Προσπαθηστε ξανα." << RESET << endl;
            cin >> p;
        }

        hero->Take_Potion( p - 1);
    }
}

void Grid::print_Hero( Hero* hero)const
{
    hero->print_hero();
}

void Grid::displayMap()const
{   

    cout << BOLDMAGENTA << "The Map" << RESET << endl;
    
    for(int i = 0; i< x;i++)
    {   
        for(int j = 0; j < y; j++)
        {
            
            cout << "\u250C";
            cout << "\u2500\u2500\u2500";
            cout << "\u2510";       
        }
        cout << endl;
        for(int j = 0; j < y; j++)
        {
            cout << "\u2502";
            if(squares[i][j]->get_kind_of_square() == "Market" )
            {   
                int k = squares[i][j]->contains();
                if( k == 0)
                {
                    cout << BLUE << "H " << RESET;
                    cout << YELLOW << "S" << RESET;
                }
                else
                {
                    cout << YELLOW << " S " << RESET;
                }
            }
            else if( squares[i][j]->get_kind_of_square() == "nonAccessible")
            {
                cout << RED << " X " << RESET;
            }
            else
            {   
                int k = squares[i][j]->contains();
                if( k == 0)
                {
                    cout << BLUE << " H " << RESET;
                }
                else if( k == 1)
                {
                    cout << MAGENTA << " M " << RESET;
                }
                else if( k == 2)
                {
                    cout << GREEN << " B " << RESET;
                }
                else
                {
                    cout << "   " << RESET;
                }
            }
            
            cout << "\u2502";      
        }
        cout << endl;

        for(int j = 0; j < y; j++)
        {
            cout << "\u2514";
            cout << "\u2500\u2500\u2500";
            cout << "\u2518";    
        }
        cout << endl;
    }
    cout << endl;
}


void Grid::quitGame()
{
    cout << BOLDRED << "YOU LOSE!" << endl;
    exit(EXIT_FAILURE);
}





///LOIPON GIOXANSO SOSSSSSSSSSSSSSSS

//EMFANIZE TOY POY NA PAEI MONOOOOOOOOOOOOOOO EKEI POY BOREI DILADI AN EINAI APAGOREYSIMO TETRAGONO
//(PX EINAI X) NA ELEGXEIII KAI AN EINAI APAGOREYSIMO NA MI  TOY EMFANIZEI AYTI TI KATEYTHINSIIIIIIIIII
//EPISIS OPOS EINAI TORA AN EINAI NONACCESIBLE DN PAEI PANO KAI DN KSANAKALEITAI I MOVE MENEI EKEI POY 
//EINAI

void Grid::move(vector <Hero*> heroes){
    displayMap();
    int a;
    int f1 = 1;
    if(heroes.at(0)->get_x() == 0){
        a = this->x-1;
    }
    else{
        a = heroes.at(0)->get_x() - 1;
    }
    if(squares[a][heroes.at(0)->get_y()]->get_kind_of_square().compare("nonAccessible") == 0){
        f1 = 0;
    }

    int f2 = 2;
    if(heroes.at(0)->get_x() == this->x-1){
        a = 0;
    }
    else{
        a = heroes.at(0)->get_x() + 1;
    }
    if(squares[a][heroes.at(0)->get_y()]->get_kind_of_square().compare("nonAccessible") == 0){
        f2 = 0;
    }

    int f3 = 3;
    if(heroes.at(0)->get_y() == 0){
        a = this->y-1;
    }
    else{
        a = heroes.at(0)->get_y() - 1;
    }
    if(squares[heroes.at(0)->get_x()][a]->get_kind_of_square().compare("nonAccessible") == 0){
        f3 = 0; 
    }

    int f4 = 4;
    if(heroes.at(0)->get_y() == this->y-1){
        a = 0;
    }
    else{
        a = heroes.at(0)->get_y() + 1;
    }
    if(squares[heroes.at(0)->get_x()][a]->get_kind_of_square().compare("nonAccessible") == 0){
        f4 = 0;
    }
    cout<<"Where do you want to go?"<<endl;
    if(f1 == 1)
        cout<<"Press 1 for up."<<endl;
    if(f2 == 2)
        cout<<"Press 2 for down."<<endl;
    if(f3 == 3)
        cout<<"Press 3 for left."<<endl;
    if(f4 == 4)
        cout<<"Press 4 for right."<<endl;
    int answer;
    cin>>answer;
    while(answer == 0 && answer != f1 && answer != f2 && answer != f3 && answer != f4){
        cout << RED << "Invalid number, try again!" << RESET << endl;
        cin >> answer;
    }
    if(answer == 1){
        int a;
        if(heroes.at(0)->get_x() == 0){
            a = this->x-1;
        }
        else{
            a = heroes.at(0)->get_x() - 1;
        }
        squares[heroes.at(0)->get_x()][heroes.at(0)->get_y()]->remove_heroes();
        for(unsigned int i = 0; i < heroes.size(); i++){
            squares[a][heroes.at(0)->get_y()]->add_hero(heroes.at(i));
            heroes.at(i)->set_x(a);
            x_heroes = a;
        }
    }
    else if(answer == 2){
        int a;
        if(heroes.at(0)->get_x() == this->x-1){
            a = 0;
        }
        else{
            a = heroes.at(0)->get_x() + 1;
        }
        squares[heroes.at(0)->get_x()][heroes.at(0)->get_y()]->remove_heroes();
        for(unsigned int i = 0; i < heroes.size(); i++){
            squares[a][heroes.at(0)->get_y()]->add_hero(heroes.at(i));
            heroes.at(i)->set_x(a);
            x_heroes = a;
        }
    }
    else if(answer == 3){
        int a;
        if(heroes.at(0)->get_y() == 0){
            a = this->y-1;
        }
        else{
            a = heroes.at(0)->get_y() - 1;
        }
        squares[heroes.at(0)->get_x()][heroes.at(0)->get_y()]->remove_heroes();
        for(unsigned int i = 0; i < heroes.size(); i++){
            squares[heroes.at(0)->get_x()][a]->add_hero(heroes.at(i));
            heroes.at(i)->set_y(a);
            y_heroes = a;
        }
    }
    else{
        int a;
        if(heroes.at(0)->get_y() == this->y-1){
            a = 0;
        }
        else{
            a = heroes.at(0)->get_y() + 1;
        }
        squares[heroes.at(0)->get_x()][heroes.at(0)->get_y()]->remove_heroes();
        for(unsigned int i = 0; i < heroes.size(); i++){
            squares[heroes.at(0)->get_x()][a]->add_hero(heroes.at(i));
            heroes.at(i)->set_y(a);
            y_heroes = a;
        }
    }
}


void Grid::buy_sell_and_equip( Hero* hero)
{
    string answer;
    do{
        cout << "Do you want to buy anything else?" << endl;
        cin >> answer;

        while( answer != "Yes" && answer != "No"){
            cout << RED << "Invalid answer, try again!" << RESET << endl;
            cin >> answer;
        }

        if( answer.compare( "Yes") == 0)
        {
            squares[x_heroes][y_heroes]->buy( hero);
        }

    }while(  answer.compare( "Yes") == 0 && hero->get_money() > 0);

    //sell
    int count_item_and_spell;
    do{
        cout << "You want sell?" << endl;
        cin >> answer;

        while( answer != "Yes" && answer != "No"){
            cout << RED << "Invalid answer, try again!" << RESET << endl;
            cin >> answer;
        }

        if( answer.compare( "Yes") == 0)
        {
            squares[x_heroes][y_heroes]->sell( hero);
        }

        count_item_and_spell = hero->get_count_item_and_spell();

    }while(  answer.compare( "Yes") == 0 && count_item_and_spell > 0);

    //αν θελει κατι απο αυτα που αγορασε να αλλαξει καλω την equip
    string in;
    do{
        cout << "You want change Item?" << endl;
        cin >> in;
        while( in.compare("Yes") != 0 && in.compare("No") != 0){
            cout << RED << "Invalid answer, try again!" << RESET << endl;
            cin >> in;
        }

        if( in.compare("Yes") == 0)
        {
            equip( hero);
        }

    }while( in.compare("Yes") == 0);
        
}


void Grid::provide(Item* item){
    for(int i = 0; i < this->x; i++){
        for(int j = 0; j < this->y; j++){
            if(this->squares[i][j]->get_kind_of_square().compare("Market") == 0){
                this->squares[i][j]->insert_item(item);
            }
        }
    }
}

void Grid::provide(Spell* spell){
    for(int i = 0; i < this->x; i++){
        for(int j = 0; j < this->y; j++){
            if(this->squares[i][j]->get_kind_of_square().compare("Market") == 0){
                this->squares[i][j]->insert_spell(spell);
            }
        }
    }
}




//////////////////////////////////////////

//Συναρτήσεις για Square.
Square::Square(string s){
    this->kind_of_square.assign(s);
}

Square::~Square(){
    this->heroes.clear();
    this->monsters.clear();
}

void Square::add_hero(Hero* h){
    this->heroes.push_back(h);
}

void Square::add_monster(Monster* m){
    this->monsters.push_back(m);
}

vector <Hero*> Square::remove_heroes(){
    vector <Hero*> vec;
    for(unsigned int i = 0; i < this->heroes.size(); i++){
        vec.push_back(this->heroes.at(i));
    }
    this->heroes.clear();
    return vec;
}

string Square::get_kind_of_square() const{
    return this->kind_of_square;
}

int Square::contains(){
  if(this->heroes.size() > 0 && this->monsters.size() > 0)
        return 2;
    else if(this->monsters.size() > 0)
        return 1;
    else if(this->heroes.size() > 0)
        return 0;
    else
        return 3;  
}

int Square::alive(){
    int h = 0;
    for(unsigned int i = 0; i < this->heroes.size(); i++){
        if(this->heroes.at(i)->get_healthPower() != 0.0)
            h++;
    }
    int m = 0;
    for(unsigned int i = 0; i < this->monsters.size(); i++){
        if(this->monsters.at(i)->get_healthPower() != 0.0)
            m++;
    }
    if(m != 0 && h != 0)
        return 0;
    else if(m > 0)
        return 1;
    else
        return 2;
}

void Square::War(){   

    if(this->monsters.size() == 0)return;
    int r = rand()%3;
    if(r)return;

    cout<< MAGENTA << "You are on a war with "<<this->monsters.size()<<" monsters"<< RESET << endl;
    if(this->heroes.at(0)->get_level() > this->monsters.at(0)->get_level()){
        for(unsigned int i = 0; i < this->monsters.size(); i++){
            this->monsters.at(i)->level_up();
        }
    }
    while(this->alive() == 0){
        for(unsigned int i = 0; i < this->heroes.size(); i++){
            cout << endl << endl <<this->heroes.at(i)->get_name()<<":"<<endl;
            if(this->heroes.at(i)->get_healthPower() == 0.0)
                continue;
            cout << BLUE <<"How do you want to attack your oponents?" << RESET << endl; 
            cout << "Press 1 for Attack" << endl;
            cout << "Press 2 for CastSpell" << endl;
            cout << "Press 3 for Potion" << endl;

            int w;
            cin >> w;
            while( w <=0 || w > 3){
                cout << RED << "Invalid number, try again!" << RESET << endl;
                cin >> w;
            }

            if( w == 3){
                int p = this->heroes.at(i)->print_Potion();
                if(p == 0){
                    cout<< MAGENTA << "Select another way of attack" << RESET << endl;
                    cin>>w;
                    while(w != 1 && w != 2){
                        cout<< RED <<"Invalid number, try again!"<< RESET << endl;
                        cin>>w;
                    }
                    //Monster* monster;
                    cout << MAGENTA << "Which monster do you want to fight against?" << RESET << endl << endl;
                    for(unsigned int j = 0; j < this->monsters.size(); j++){
                        if(this->monsters.at(j)->get_healthPower() > 0){
                            cout<<j+1<<")";
                            this->monsters.at(j)->print_monster();
                            cout<<endl;
                        }
                    }
                    if(this->alive() == 2)
                        break;
                    cout<<"Press the number of the monster you want to fight against"<<endl;
                    unsigned int a1;
                    cin>>a1;
                    while(a1 <= 0 || a1 > this->monsters.size()){
                        cout<<RED<<"Invalid number, try again!"<<RESET<<endl;
                        cin>>a1;
                    }
                    while(this->monsters.at(a1-1)->get_healthPower() <= 0){
                        cout<<RED<<"Invalid number, try again!"<<RESET<<endl;
                        cin>>a1;
                    }
                    if(w == 1){
                        this->heroes.at(i)->attack(this->monsters.at(a1-1));
                    }
                    else{
                        bool f = this->heroes.at(i)->castSpell(this->monsters.at(a1-1));
                        if(f == false){
                            cout<<"The only way to attack is by a simple attack"<<endl;
                            this->heroes.at(i)->attack(this->monsters.at(a1-1));
                        }
                    }
                }
                else{
                    cout<< MAGENTA << "Please press the number of the Potion you want to take" << RESET <<endl;
                    int a;
                    cin>>a;
                    while(a <= 0 || a > p){
                        cout<< RED << "Invalid number, try again!" << RESET << endl;
                        cin>>a;
                    }
                    this->heroes.at(i)->Take_Potion(a-1);
                }
            }
            else{   
                //Monster* monster;
                cout << MAGENTA <<"Which monster do you want to fight against?" << RESET << endl;
                for(unsigned int j = 0; j < this->monsters.size(); j++){
                    if(this->monsters.at(j)->get_healthPower() > 0){
                        cout<<j+1<<")";
                        this->monsters.at(j)->print_monster();
                        cout<<endl;
                    }
                }
                if(this->alive() == 2)
                    break;
                cout << endl << MAGENTA <<"Press the number of the monster you want to fight against" << RESET <<endl;
                unsigned int a1;
                cin>>a1;
                while(a1 <= 0 || a1 > this->monsters.size()){
                    cout<<RED<<"Invalid number, try again!"<<RESET<<endl;
                    cin>>a1;
                }
                while(this->monsters.at(a1-1)->get_healthPower() <= 0){
                    cout<<RED<<"Invalid number, try again!"<<RESET<<endl;
                    cin>>a1;
                }
                if(w == 1){
                    this->heroes.at(i)->attack(this->monsters.at(a1-1));
                }
                else{
                    bool f = this->heroes.at(i)->castSpell(this->monsters.at(a1-1));
                    if(f == false){
                        cout<< BLUE <<"Select another way of attack"<< RESET <<endl;
                        cin>>w;
                        while(w != 1 && w != 3){
                            cout<<RED<<"Invalid number, try again!"<<RESET<<endl;
                            cin>>w;
                        }
                        if(w == 1){
                            this->heroes.at(i)->attack(this->monsters.at(a1-1));
                        }
                        else{
                            int p = this->heroes.at(i)->print_Potion();
                            if(p == 0){
                                cout<<"The only way to attack is by a simple attack"<<endl;
                                this->heroes.at(i)->attack(this->monsters.at(a1-1));
                            }
                            else{
                                cout<<"Please press the number of the Potion you want to take"<<endl;
                                int a;
                                cin>>a;
                                while(a <= 0 || a > p){
                                    cout<< RED << "Invalid number, try again!" << RESET << endl;
                                    cin>>a;
                                }
                                this->heroes.at(i)->Take_Potion(a-1);
                            }
                        }
                    }
                }
            }
        }
        for(unsigned int i = 0;  i < this->monsters.size(); i++){
            if(this->monsters.at(i)->get_healthPower() == 0.0)
                continue;
            int j = 0;
            while(this->heroes.at(j)->get_healthPower() == 0.0){
                j++;
            }
            this->monsters.at(i)->attack(this->heroes.at(j));
            this->monsters.at(i)->reset_fields();
        }
        for(unsigned int i = 0; i < this->heroes.size(); i++){
            if(this->heroes.at(i)->get_healthPower() != 0.0){
                this->heroes.at(i)->add_healthPower(0.1 * this->heroes.at(i)->get_healthPower());
                this->heroes.at(i)->add_magicPower(0.1 * this->heroes.at(i)->get_magicPower());
            }
        }
        for(unsigned int i = 0; i < this->monsters.size(); i++){
            if(this->monsters.at(i)->get_healthPower() != 0.0)
                this->monsters.at(i)->add_healthPower(0.1 * this->heroes.at(i)->get_healthPower());
        }
        cout<< endl << endl << YELLOW << "Do you want to view Statistics?"<< RESET << endl;
        cout<<"Yes or No"<<endl;
        
        string answer;
        cin >> answer;
        while( answer.compare("Yes") != 0 && answer.compare("No") != 0){
            cout<<"Invalid answer, try again!"<<endl;
            cin >> answer;
        }
        
        if(answer.compare("Yes") == 0){
            for(unsigned int i = 0; i < this->heroes.size(); i++){
                this->heroes.at(i)->displayStats();
            }
            for(unsigned int i = 0; i < this->monsters.size(); i++){
                this->monsters.at(i)->displayStats();
            }
        }
    }
    if(this->alive() == 1){
        cout << endl << endl <<BOLDRED <<"You lost the war"<< RESET << endl;
        for(unsigned int i = 0; i < this->heroes.size(); i++){
            this->heroes.at(i)->set_money(this->heroes.at(i)->get_money() / 2.0);
        }
    }
    else{
        cout<< endl << endl << BOLDGREEN<<"You won the war. Congratulations!"<< RESET<<endl;
        for(unsigned int i = 0; i < this->heroes.size(); i++){
            this->heroes.at(i)->add_experience((this->heroes.at(i)->get_level() + EXPERIENCE) * this->monsters.size());
            this->heroes.at(i)->add_money((this->heroes.at(i)->get_level() + MONEY) * this->monsters.size());
        }
    }
    for(unsigned int i = 0; i < this->monsters.size(); i++){
        this->monsters.at(i)->set_rounds(1);
        this->monsters.at(i)->reset_fields();
        if(this->monsters.at(i)->get_healthPower() == 0.0)
            this->monsters.at(i)->set_healthPower(HEALTH_POWER/2.0);
    }
    for(unsigned int i = 0; i < this->heroes.size(); i++){
        if(this->heroes.at(i)->get_healthPower() == 0.0)
            this->heroes.at(i)->set_healthPower(HEALTH_POWER/2.0);
    }
    double exp = NEEDED_EXPERIENCE;
    for(int i = 0; i < this->heroes.at(0)->get_level(); i++){
        exp *= 2.0;
    }
    if(this->heroes.at(0)->get_experience() >= exp){
        for(unsigned int i = 0; i < this->heroes.size(); i++){
            this->heroes.at(i)->level_up();
        }
        for(unsigned int i = 0; i < this->monsters.size(); i++){
            this->monsters.at(i)->level_up();
        }
    }
}


//βοηθητικη συναρτηση-μελος
bool Square::buy( Hero* hero)
{
    return true;
}

void Square::sell( Hero* hero)
{

}

vector<Hero*> Square::get_heroes()
{
    return heroes;
}

//Συναρτήσεις για Market.
Market::~Market(){
    this->items.clear();
    this->spells.clear();
}

void Market::insert_item(Item* item){
    this->items.push_back(item);
}

void Market::insert_spell(Spell* spell){
    this->spells.push_back(spell);
}

bool Market::buy(Hero* hero){
    cout<<"What would you like to buy?"<<endl;
    cout<<"Press 1 for Items"<<endl;
    cout<<"Press 2 for Spells"<<endl;
    int a;
    cin>>a;

    while(a != 1 && a != 2){
        cout<<"Invalid number, try again!"<<endl;
        cin>>a;
    }
    //ελεγχουμε αν αγορασε οπλο
    bool back = false;

    if(a == 1){
        cout<<"The items available in the market are:"<<endl;
        for(unsigned int i = 0; i < this->items.size(); i++){
            cout<<i+1<<") ";
            this->items.at(i)->print();
        }
        cout<<"Press the number of the item you would like to purchase"<<endl;
        unsigned int a1;
        cin>>a1;

        while(a1 > this->items.size() || a1 <= 0 || this->items.at(a1-1)->get_level() > hero->get_level()){
            if(this->items.at(a1-1)->get_level() > hero->get_level())
                cout << RED << "You must choose an item you have the needed level to buy, try again!"<< RESET << endl;
            else
                cout << RED << "Invalid number, try again!" << RESET << endl;
            cin>>a1;
        }
        Item* item = this->items.at(a1-1);
        if( item->get_price() <= hero->get_money())
        {
            if( (item->get_kind_of_item()).compare("Weapon") == 0)
            {
                back = true;
            }

            hero->sub_money( item->get_price());
            hero->buy_Item(item);
        }
        else
        {
            cout << RED << "You havn't money for this Item!" << RESET << endl;
        }
        
    }
    else{
        cout<<"The spells available in the market are:"<<endl;
        for(unsigned int i = 0; i < this->spells.size(); i++){
            cout<<i+1<<") ";
            this->spells.at(i)->print();
        }
        cout<<"Press the number of the spell you would like to purchase"<<endl;
        unsigned int a1;
        cin>>a1;
        while(a1 > this->spells.size() || a1 <= 0 || this->spells.at(a1-1)->get_level() > hero->get_level()){
            if(this->spells.at(a1-1)->get_level() > hero->get_level())
                cout << RED << "You must choose an item you have the needed level to buy, try again!"<<endl;
            else
                cout << RED << "Invalid number, try again!" << RESET << endl;
            cin>>a1;
        }
        Spell* spell = this->spells.at(a1-1);

        if( spell->get_price() <= hero->get_money())
        {
            hero->sub_money( spell->get_price());
            hero->buy_Spell(spell);
        }
        else
        {
            cout << RED << "You havn't money for this Spell!" << RESET << endl;
        }
    }

    return back;
}

void Market::sell(Hero* hero){
    cout<<"What would you like to sell?"<<endl;
    cout<<"Press 1 for Items"<<endl;
    cout<<"Press 2 for Spells"<<endl;
    int a;
    cin>>a;
    if(a == 1){
        unsigned int number = hero->print_item();
        cout<<"Press the number of the item you would like to sell"<<endl;
        unsigned int a1;
        cin>>a1;
        while(a1 <= 0 || a1> number){
            cout << RED << "Invalid number, try again!" << RESET << endl;
            cin>>a1;
        }
        hero->sell_Item(a1-1);
    }
    else{
        int number = hero->print_spell();
        cout<<"Press the number of the spell you would like to sell"<<endl;
        int a1;
        cin>>a1;
        while(a1 <= 0 || a1> number){
            cout << RED << "Invalid number, try again!" << RESET << endl;
            cin>>a1;
        }
        hero->sell_Spell(a1-1);
    }
}

int Market::contains(){
    return Square::contains();
}

//Συναρτήσεις για Common.
int Common::contains(){
    return Square::contains();
}

//Συναρτήσεις για nonAccessible.
int nonAccessible::contains(){
    return Square::contains();
}
