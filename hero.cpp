#include "hero.h"
#include <iostream>

using namespace std; 

hero::hero(int heroID, double power, double teamMastery, double opponentMastery, int membershipIndicator)
{
	this->heroID = heroID;
	this->power = power; 
	this->teamMastery = teamMastery; 
	this->opponentMastery = opponentMastery; 
	this->membershipIndicator = membershipIndicator; 
}

void hero::printStats(){
	// cout << "Hero ID: " << this->heroID << endl; 
	// cout << "Power: " << this->power << endl;
	// cout << "Team Mastery: " << this->teamMastery << endl;
	// cout << "Opponent Mastery: " << this->opponentMastery << endl; 
	// cout << "Membership Indicator: " << this->membershipIndicator << endl << endl;
}