


#ifndef Player_h
#define Player_h

#include <iostream>
#include <limits>

using std::cout;
using std::endl;
using std::cin;
using std::string;

using std::cerr;
using std::numeric_limits;
using std::streamsize;

class Player
{
private:
    string character;
    string essence;
    int strike;
    int baseHP;
    int baseDiligence;
    int currentHP;
    int currentDiligence;
    
public:
    //  Default constructor
    Player();
    
    
    
    // Setters
    // Sets character and modifies base stats accordingly
    void setCharacter(int);
    
    //  Sets user and modifies base stats accordingly
    void setEssence(int);
    
    //  Sets user's HP to 100%
    void resetHP();
    
    //  Sets user's diligence to its base value
    void resetDiligence();
    
    //  Changes Diligence by given value
    void changeDiligence(int);
    
    //  Sets HP to 0
    void zeroHP();
    
    //  Takes a given amount of HP
    void takeDamage(int);
    
    //  Changes HP by given value
    void hpChange(int);
    
    
    
    //  Getters
    string getCharacter();
    int getCurrentHP();
    int getBaseHP();
    int getCurrentDiligence();
    int getStrike();
    
    
    
    //  Member functions
    //  Prompts user to choose their character
    int chooseCharacter();
    
    //  Shows buff and nerf to user's stats, based on character choice
    void showCharacterDebrief();
    
    //  Prompts user to choose their essence
    int chooseEssence();
    
    //  Shows buff and nerf to user's stats, based on essence choice
    void showEssenceDebrief();
    
    //  Sets player to user's choices
    void createPlayer();
    
};

#endif
