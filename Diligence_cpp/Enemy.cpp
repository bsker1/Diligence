


#include "Enemy.h"

//  Default constructor
Enemy::Enemy()
{
    strike = 25 + (rand() % 7) - 3;
    baseHP = 100 + (rand() % 25) - 12;
    baseDiligence = (rand() % 3) - 1;
    
    int randEnemy = rand() % 6;
    if (randEnemy == 0)
    {
        character = "Skeleton";
        strike *= 1.1;
        baseHP *= 0.9;
    }
    else if (randEnemy == 1)
    {
        character = "Zombie";
        strike *= 1.1;
        --baseDiligence;
    }
    else if (randEnemy == 2)
    {
        character = "Knight";
        baseHP *= 1.1;
        strike *= 0.9;
    }
    else if (randEnemy == 3)
    {
        character = "Beast";
        baseHP *= 1.1;
        --baseDiligence;
    }
    else if (randEnemy == 4)
    {
        character = "Ghoul";
        ++baseDiligence;
        strike *= 0.9;
    }
    else
    {
        character = "Witch";
        ++baseDiligence;
        baseHP *= 0.9;
    }
    
    currentHP = baseHP;
    currentDiligence = baseDiligence;
}



void Enemy::resetHP()
{
    currentHP = baseHP;
}

void Enemy::changeDiligence(int buffer)
{
    currentDiligence += buffer;
}

void Enemy::zeroHP()
{
    currentHP = 0;
}

void Enemy::takeDamage(int damage)
{
    currentHP -= damage;
}

void Enemy::hpChange(int hp)
{
    currentHP += hp;
    
    if (currentHP > baseHP)
        this->resetHP();
    
    if (currentHP < 0)
        this->zeroHP();
}



//  Getters
string Enemy::getCharacter()
{
    return character;
}
int Enemy::getCurrentHP()
{
    if (currentHP < 0)
        return 0;
    
    return currentHP;
}
int Enemy::getBaseHP()
{
    return baseHP;
}
int Enemy::getCurrentDiligence()
{
    return currentDiligence;
}
int Enemy::getStrike()
{
    return strike;
}
