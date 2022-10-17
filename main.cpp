


#include "functions.h"
#include "Player.h"

#include <iostream>
#include <ctime>

using std::cout;
using std::endl;
using std::cin;

int main()
{
    //  Sets random number generator seed
    srand(time(NULL));
    
    Player User;
    User.createPlayer();
    
    int wins = 0;
    battleLoop(User, wins);
    
    cout << "\n\nTotal wins this run: " << wins << endl;
    cin.get();
    
    cout << "Thank you for playing Diligence!" << endl;
    cin.get();
    
    return 0;
}
