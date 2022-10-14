


#ifndef Enemy_h
#define Enemy_h

#include <iostream>

using std::string;

class Enemy
{
private:
    string character;
    int strike;
    int baseHP;
    int baseDiligence;
    int currentHP;
    int currentDiligence;
    
public:
    //  Default constructor
    Enemy();
    
    //  Setters
    //  Sets user's HP to 100%
    void resetHP();
    
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
};

#endif
