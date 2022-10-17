


#ifndef functions_h
#define functions_h

#include "Player.h"
#include "Enemy.h"

int chanceRoll(int);
int rollCheck(int, int);
void continuePrompt(char&);
void chooseMove(int&);
string showMove(int);
int resolveAttack(int, int, int&);
int resolveDefend(int, int&, int&, int);
int resolveConcentrate(int, int&, int&);
int resolveCurse(int, int&, int&);
void resolveMoves(Player&, int, Enemy&, int);
void resolveHPChance(Player&, Enemy&);
void winnerCheck(Player&, Enemy&, int& wins, char&);
void turnLoop(Player&, Enemy&);
void battleLoop(Player&, int&);

#endif
