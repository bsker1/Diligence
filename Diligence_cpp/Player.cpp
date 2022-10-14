


#include "Player.h"

//  Default constructor
Player::Player()
{
    character = "[empty]";
    essence = "[empty]";
    strike = 25;
    baseHP = 100;
    baseDiligence = 0;
    currentHP = 0;
    currentDiligence = 0;
}



//  Setters
void Player::setCharacter(int choice)
{
    if (choice == 1)
    {
        character = "Lich";
        ++baseDiligence;
        baseHP *= 0.9;
    }
    else if (choice == 2)
    {
        character = "Solea";
        strike *= 1.1;
        --baseDiligence;
    }
    else
    {
        character = "Puck";
        baseHP *= 1.1;
        strike *= 0.9;
    }
}

void Player::setEssence(int choice)
{
    if (choice == 1)
    {
        essence = "Dangerous";
        strike *= 1.1;
        baseHP *= 0.9;
    }
    else if (choice == 2)
    {
        essence = "Cynical";
        strike *= 1.1;
        --baseDiligence;
    }
    else if (choice == 3)
    {
        essence = "Wise";
        baseHP *= 1.1;
        strike *= 0.9;
    }
    else if (choice == 4)
    {
        essence = "Greedy";
        baseHP *= 1.1;
        --baseDiligence;
    }
    else if (choice == 5)
    {
        essence = "Precious";
        ++baseDiligence;
        strike *= 0.9;
    }
    else
    {
        essence = "Illustrious";
        ++baseDiligence;
        baseHP *= 0.9;
    }
}

void Player::resetHP()
{
    currentHP = baseHP;
}

void Player::resetDiligence()
{
    currentDiligence = baseDiligence;
}

void Player::changeDiligence(int buffer)
{
    currentDiligence += buffer;
}

void Player::zeroHP()
{
    currentHP = 0;
}

void Player::takeDamage(int damage)
{
    currentHP -= damage;
}

void Player::hpChange(int hp)
{
    currentHP += hp;
    
    if (currentHP > baseHP)
        this->resetHP();
    
    if (currentHP < 0)
        this->zeroHP();
}



//  Getters
string Player::getCharacter()
{
    return character;
}
int Player::getCurrentHP()
{
    if (currentHP < 0)
        return 0;
    
    return currentHP;
}
int Player::getBaseHP()
{
    return baseHP;
}
int Player::getCurrentDiligence()
{
    return currentDiligence;
}
int Player::getStrike()
{
    return strike;
}



//  Member functoins
//  User chooses character from 3 options
int Player::chooseCharacter()
{
    int input = 0;
    do
    {
        cout << "Who are you?\n" << endl;
        
        cout << "   1) Lich, the Necromancer\n"
             << "   2) Solea, the Pyromancer\n"
             << "   3) Puck, the Cryomancer\n"
             << "   4) Random\n"
        
             << "\n*__ ";
        
        cin >> input;
        
        if (cin.fail() || input < 1 || input > 4)
        {
            cerr << "\nERROR: invalid input\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
    while (cin.fail() || input < 1 || input > 4);
    
    if (input == 4)
        input = (rand() % 3) + 1;
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return input;
}

//  User is shown their strength and weakness
void Player::showCharacterDebrief()
{
    cout << "\nSo, you're " << character << "." << endl;
    cin.get();
    
    //  Lich: +Diligence, -HP
    if (baseDiligence > 0)
    {
        cout << "It seems you excel in your Diligence..." << endl;
        cin.get();
        
        cout << "...But you may get hurt easily." << endl;
        cin.get();
    }
    //  Solea: +Strike, -Diligence
    else if (baseDiligence < 0)
    {
        cout << "It seems you strike with passion..." << endl;
        cin.get();
        
        cout << "...But a diligent foe will stand strong." << endl;
        cin.get();
    }
    //  Puck: +HP, -Strike
    else
    {
        cout << "It seems you stand as tough as any..." << endl;
        cin.get();
        
        cout << "...But your strike is lacking." << endl;
        cin.get();
    }
}

//  User chooses essence from 6 options
int Player::chooseEssence()
{
    int input = 0;
    
    do
    {
        cout << "\n\nAnd which essence do you encompass?\n" << endl;
        
        cout << "   1) Dangerous\n"
             << "   2) Cynical\n"
             << "   3) Wise\n"
             << "   4) Greedy\n"
             << "   5) Precious\n"
             << "   6) Illustrious\n"
             << "   7) Random\n"
        
             << "\n*__ ";
        
        cin >> input;
        
        if (cin.fail() || input < 1 || input > 7)
        {
            cerr << "\nERROR: invalid input\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
    while (cin.fail() || input < 1 || input > 7);
    
    if (input == 7)
        input = (rand() % 6) + 1;
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    return input;
}

void Player::showEssenceDebrief()
{
    cout << "\nSo, " << character << ", it seems you are very "
         << essence << "." << endl;
    cin.get();
    
    if (essence == "Dangerous")
    {
        cout << "You must have worked on your strike..." << endl;
        cin.get();
        
        cout << "...But you seem to have neglected your toughness." << endl;
        cin.get();
    }
    else if (essence == "Cynical")
    {
        cout << "You must have worked on your strike..." << endl;
        cin.get();
        
        cout << "...But you seem to have neglected your diligence." << endl;
        cin.get();
    }
    else if (essence == "Wise")
    {
        cout << "You must have worked on your toughness..." << endl;
        cin.get();
        
        cout << "...But you seem to have neglected your strike." << endl;
        cin.get();
    }
    else if (essence == "Greedy")
    {
        cout << "You must have worked on your toughness..." << endl;
        cin.get();
        
        cout << "...But you seem to have neglected your diligence." << endl;
        cin.get();
    }
    else if (essence == "Precious")
    {
        cout << "You must have worked on your diligence..." << endl;
        cin.get();
        
        cout << "...But you seem to have neglected your strike." << endl;
        cin.get();
    }
    else
    {
        cout << "You must have worked on your diligence..." << endl;
        cin.get();
        
        cout << "...But you seem to have neglected your toughness." << endl;
        cin.get();
    }
    
    return;
}

void Player::createPlayer()
{
    cout << "Hello, diligent one!" << endl;
    cin.get();
    
    int characterChoice = this->chooseCharacter();
    this->setCharacter(characterChoice);
    
    this->showCharacterDebrief();
    
    int essenceChoice = this->chooseEssence();
    this->setEssence(essenceChoice);
    
    this->showEssenceDebrief();
    
    cout << "\n\nIt seems you are ready to fight, "
         << character << "." << endl;
    cin.get();
    
    cout << "Welcome to Diligence!" << endl;
    cin.get();
}
