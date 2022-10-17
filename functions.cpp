


#include "functions.h"

//  Returns highest or lowest value of a given amount of random rolls,
//  determined by diligence stat
int chanceRoll(int diligence)
{
    if (diligence == 0)
        return rand() % 100;
    
    int roll = rand() % 100;
    
    if (diligence > 0)
    {
        int newRoll = chanceRoll(diligence - 1);
        if (newRoll > roll)
            return newRoll;
        return roll;
    }
    else
    {
        int newRoll = chanceRoll(diligence + 1);
        if (newRoll < roll)
            return newRoll;
        return roll;
    }
}

//  Returns 1 if random roll is in the top threshold percentile
//  Returns -1 if random roll is in the bottom threshold percentile
//  Returns 0 otherwise
int rollCheck(int diligence, int threshold)
{
    int roll = chanceRoll(diligence);
    
    if (roll >= 100 - threshold)
        return 1;
    if (roll < threshold)
        return -1;
    return 0;
}

void continuePrompt(char& choice)
{
    do
    {
        cout << "\n\nEnter 'Q' to quit,\n"
             << "Enter 'C' to continue.\n"
             << "\n*__ ";
        
        cin >> choice;
        
        if (cin.fail() || (toupper(choice) != 'Q' && toupper(choice) != 'C'))
        {
            cerr << "\nERROR: invalid input\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
    while (cin.fail() || (toupper(choice) != 'Q' && toupper(choice) != 'C'));
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void chooseMove(int& choice)
{
    do
    {
        cout << "What will you do?\n" << endl;
        
        cout << "   1) Attack\n"
             << "   2) Defend\n"
             << "   3) Concentrate\n"
             << "   4) Curse\n"
        
             << "\n*__ ";
        
        cin >> choice;
        
        if (cin.fail() || choice < 1 || choice > 4)
        {
            cerr << "\nERROR: invalid input\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
    while (cin.fail() || choice < 1 || choice > 4);
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string showMove(int choice)
{
    if (choice < 2)
        return "Attack";
    if (choice == 2)
        return "Defend";
    if (choice == 3)
        return "Concentrate";
    return "Curse";
}

int resolveAttack(int currentDiligence, int strike, int& opponentDamage)
{
    opponentDamage += strike;
    
    int diligenceRoll = rollCheck(currentDiligence, 15);
    
    if (diligenceRoll == 1)
        opponentDamage *= 1.2;
    else if (diligenceRoll == -1)
        opponentDamage *= 0.8;
    
    return diligenceRoll;
}

int resolveDefend(int currentDiligence, int& userDamage, int& opponentDamage, int opponentAction)
{
    int diligenceRoll = rollCheck(currentDiligence, 15);
    
    if (diligenceRoll == 1)
        userDamage *= 0.25;
    else if (diligenceRoll == -1)
        userDamage *= 0.75;
    else
        userDamage *= 0.5;
    
    if (opponentAction < 2)
        opponentDamage += 5;
    
    return diligenceRoll;
}

int resolveConcentrate(int currentDiligence, int& userDiligence, int& opponentDiligence)
{
    ++userDiligence;
    
    int diligenceOutcome = 0;
    
    if (rollCheck(currentDiligence, 15) == 1)
    {
        ++userDiligence;
        diligenceOutcome += 1;
    }
    
    if (rollCheck(currentDiligence, 15) == 1)
    {
        ++opponentDiligence;
        diligenceOutcome += 2;
    }
    
    return diligenceOutcome;
}

int resolveCurse(int currentDiligence, int& userDiligence, int& opponentDiligence)
{
    --opponentDiligence;
    
    int diligenceOutcome = 0;
    
    if (rollCheck(currentDiligence, 15) == 1)
    {
        --opponentDiligence;
        diligenceOutcome += 1;
    }
    
    if (rollCheck(currentDiligence, 15) == 1)
    {
        --userDiligence;
        diligenceOutcome += 2;
    }
    
    return diligenceOutcome;
}

void resolveMoves(Player& User, int playerAction, Enemy& Enemy, int enemyAction)
{
    int userConcentrateBuffer = 0;
    int enemyConcentrateBuffer = 0;
    
    //  User chooses Concentrate
    if (playerAction == 3)
    {
        int diligenceOutcome = resolveConcentrate(User.getCurrentDiligence(), userConcentrateBuffer, enemyConcentrateBuffer);
        
        cout << "You raised your Diligence!" << endl;
        cin.get();
        
        if (diligenceOutcome == 1 || diligenceOutcome == 3)
        {
            cout << "You're in luck, it was raised again!!" << endl;
            cin.get();
        }
        
        if (diligenceOutcome == 2 || diligenceOutcome == 3)
        {
            cout << "But be warned, you also raised the " << Enemy.getCharacter()
                 << "'s Diligence!!" << endl;
            cin.get();
        }
    }
    //  Enemy chooses Concentrate
    if (enemyAction == 3)
    {
        int diligenceOutcome = resolveConcentrate(Enemy.getCurrentDiligence(), enemyConcentrateBuffer, userConcentrateBuffer);
        
        cout << "The " << Enemy.getCharacter() << " raised its Diligence!" << endl;
        cin.get();
        
        if (diligenceOutcome == 1 || diligenceOutcome == 3)
        {
            cout << "Be warned, it was raised again!!" << endl;
            cin.get();
        }
        
        if (diligenceOutcome == 2 || diligenceOutcome == 3)
        {
            cout << "But you're in luck, it also raised your Diligence!!" << endl;
            cin.get();
        }
    }
    
    int userCurseBuffer = 0;
    int enemyCurseBuffer = 0;
    
    //  User chooses Curse
    if (playerAction == 4)
    {
        int diligenceOutcome = resolveCurse(User.getCurrentDiligence(), userCurseBuffer, enemyCurseBuffer);
        
        cout << "You lowered the " << Enemy.getCharacter() << "'s Diligence!" << endl;
        cin.get();
        
        if (diligenceOutcome == 1 || diligenceOutcome == 3)
        {
            cout << "You're in luck, you lowered it again!!" << endl;
            cin.get();
        }
        
        if (diligenceOutcome == 2 || diligenceOutcome == 3)
        {
            cout << "But be warned, you also lowered your own Diligence!!" << endl;
            cin.get();
        }
    }
    //  Enemy chooses Curse
    if (enemyAction == 4)
    {
        int diligenceOutcome = resolveCurse(Enemy.getCurrentDiligence(), enemyCurseBuffer, userCurseBuffer);
        
        cout << "The " << Enemy.getCharacter() << " lowered your Diligence!" << endl;
        cin.get();
        
        if (diligenceOutcome == 1 || diligenceOutcome == 3)
        {
            cout << "Be warned, it lowered it again!!" << endl;
            cin.get();
        }
        
        if (diligenceOutcome == 2 || diligenceOutcome == 3)
        {
            cout << "But you're in luck, it also lowered its own Diligence!!" << endl;
            cin.get();
        }
    }
    
    //  Applies Diligence changes, if any
    User.changeDiligence(userConcentrateBuffer + userCurseBuffer);
    Enemy.changeDiligence(enemyConcentrateBuffer + enemyCurseBuffer);
    
    int userDamageBuffer = 0;
    int enemyDamageBuffer = 0;
    
    //  User chooses Attack
    if (playerAction == 1)
    {
        int diligenceOutcome = resolveAttack(User.getCurrentDiligence(), User.getStrike(), enemyDamageBuffer);
        
        cout << "You attacked the " << Enemy.getCharacter() << "!" << endl;
        cin.get();
        
        if (diligenceOutcome == 1)
        {
            cout << "You're in luck, you landed a heavy hit!!" << endl;
            cin.get();
        }
        
        if (diligenceOutcome == -1)
        {
            cout << "But be warned, you landed a weak hit!!" << endl;
            cin.get();
        }
        
        if (enemyAction != 2)
        {
            cout << "You dealt " << enemyDamageBuffer << " damage!" << endl;
            cin.get();
        }
    }
    //  Enemy chooses Attack
    if (enemyAction < 2)
    {
        int diligenceOutcome = resolveAttack(Enemy.getCurrentDiligence(), Enemy.getStrike(), userDamageBuffer);
        
        cout << "The " << Enemy.getCharacter() << " attacked you!" << endl;
        cin.get();
        
        if (diligenceOutcome == 1)
        {
            cout << "Be warned, it landed a heavy hit!!" << endl;
            cin.get();
        }
        
        if (diligenceOutcome == -1)
        {
            cout << "But you're in luck, it landed a weak hit!!" << endl;
            cin.get();
        }
        
        if (playerAction != 2)
        {
            cout << "It dealt " << userDamageBuffer << " damage!" << endl;
            cin.get();
        }
    }
    
    //  User chooses Defend
    if (playerAction == 2)
    {
        int diligenceOutcome = resolveDefend(User.getCurrentDiligence(), userDamageBuffer, enemyDamageBuffer, enemyAction);
        
        if (enemyAction < 2)
        {
            cout << "You defended the " << Enemy.getCharacter() << "'s attack!" << endl;
            cin.get();
            
            if (diligenceOutcome == 1)
            {
                cout << "You're in luck, you absorbed the hit further!!" << endl;
                cin.get();
            }
            
            if (diligenceOutcome == -1)
            {
                cout << "But be warned, you took a harder hit!!" << endl;
                cin.get();
            }
            
            cout << "The " << Enemy.getCharacter() << " dealt " << userDamageBuffer
                 << " damage!" << endl;
            cin.get();
            
            cout << "It took 5 damage from your successful defense!" << endl;
            cin.get();
        }
        else
        {
            cout << "You defended, but there was no attack!" << endl;
            cin.get();
        }
    }
    //  Enemy chooses Defend
    if (enemyAction == 2)
    {
        int diligenceOutcome = resolveDefend(Enemy.getCurrentDiligence(), enemyDamageBuffer, userDamageBuffer, playerAction);
        
        if (playerAction == 1)
        {
            cout << "The " << Enemy.getCharacter() << " defended your attack!" << endl;
            cin.get();
            
            if (diligenceOutcome == 1)
            {
                cout << "Be warned, it absorbed the hit further!!" << endl;
                cin.get();
            }
            
            if (diligenceOutcome == -1)
            {
                cout << "But you're in luck, it took a harder hit!!" << endl;
                cin.get();
            }
            
            cout << "You dealt " << enemyDamageBuffer << " damage!" << endl;
            cin.get();
            
            cout << "You took 5 damage from its successful defense!" << endl;
            cin.get();
        }
        else
        {
            cout << "The " << Enemy.getCharacter() << " defended, but there was no attack!" << endl;
            cin.get();
        }
    }
    
    //  Applies damage, if any
    User.takeDamage(userDamageBuffer);
    Enemy.takeDamage(enemyDamageBuffer);
    
    //cout << "(Testing) User's health is now " << User.getCurrentHP() << endl;
    //cout << "(Testing) Enemy's health is now " << Enemy.getCurrentHP() << endl;
    //cin.get();
}

void resolveHPChance(Player& User, Enemy& Enemy)
{
    int userDiligenceCheck = rollCheck(User.getCurrentDiligence(), 15);
    int enemyDiligenceCheck = rollCheck(Enemy.getCurrentDiligence(), 15);
    
    if (User.getCurrentHP() != User.getBaseHP() && userDiligenceCheck == 1)
    {
        User.hpChange(10);
        
        cout << "You're in luck, you gained 10 health!!" << endl;
        cin.get();
    }
    else if (User.getCurrentHP() >= 0 && userDiligenceCheck == -1)
    {
        User.hpChange(-10);
        
        cout << "Be warned, you lost 10 health!!" << endl;
        cin.get();
    }
    
    if (Enemy.getCurrentHP() != Enemy.getBaseHP() && enemyDiligenceCheck == 1)
    {
        Enemy.hpChange(10);
        
        cout << "Be warned, the " << Enemy.getCharacter() << " gained 10 health!!" << endl;
        cin.get();
    }
    else if (Enemy.getCurrentHP() >= 0 && enemyDiligenceCheck == -1)
    {
        Enemy.hpChange(-10);
        
        cout << "You're in luck, the " << Enemy.getCharacter() << " lost 10 health!!" << endl;
        cin.get();
    }
}

void winnerCheck(Player& User, Enemy& Enemy, int& wins, char& loopFlag)
{
    if (User.getCurrentHP() == 0)
    {
        cout << "\n\nYou have been defeated. Better luck next time." << endl;
        cin.get();
        
        loopFlag = 'Q';
        return;
    }
    
    cout << "\n\nYou Win!" << endl;
    cin.get();
    
    cout << "Total wins: " << ++wins << endl;
}

void turnLoop(Player& User, Enemy& Enemy)
{
    while (User.getCurrentHP() > 0 && Enemy.getCurrentHP() > 0)
    {
        //  Shows user and enemy's HP and Diligence
        cout << User.getCharacter() << "'s HP: " << User.getCurrentHP() << "/"
             << User.getBaseHP() << ", Diligence: " << User.getCurrentDiligence() << endl;
        cout << Enemy.getCharacter() << "'s HP: " << Enemy.getCurrentHP() << "/"
             << Enemy.getBaseHP() << ", Diligence: " << Enemy.getCurrentDiligence() << endl;
        cin.get();
        
        //  User chooses move
        int playerAction = 0;
        chooseMove(playerAction);
        //  Enemy's move randomized, will introduce AI logic later
        //  2/5 chance for Attack, 1/5 everything else
        int enemyAction = rand() % 5;
        
        //  Shows user and enemy's moves
        cout << "\nYou chose " << showMove(playerAction) << ".";
        cin.get();
        cout << "The " << Enemy.getCharacter() << " chose " << showMove(enemyAction) << "." << endl;
        cin.get();
        
        resolveMoves(User, playerAction, Enemy, enemyAction);
        
        resolveHPChance(User, Enemy);
    }
}

void battleLoop(Player& User, int& wins)
{
    char loopFlag = 'C';
    
    while (toupper(loopFlag) != 'Q')
    {
        User.resetHP();
        User.resetDiligence();
        
        Enemy Enemy;
        cout << "\n\nA " << Enemy.getCharacter() << " approaches!" << endl;
        cin.get();
        
        turnLoop(User, Enemy);
        
        winnerCheck(User, Enemy, wins, loopFlag);
        
        if (loopFlag != 'Q')
            continuePrompt(loopFlag);
    }
}
