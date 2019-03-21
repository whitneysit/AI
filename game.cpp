#include "game.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std; 

game::game(string filename)
{
	this->filename = filename; 
	ifstream inFile;
	inFile.open(filename.c_str());

	string newLine;
	inFile >> this->numberOfHeroes;
	cout << this->numberOfHeroes << endl;
	string alg; 
	inFile >> alg; 
	if (alg == "minimax"){
		this->algorithm = MINIMAX;
	}
	else {
		this->algorithm = AB;
	}
	getline(inFile, newLine);
	while(getline(inFile, newLine)){
		//cout << newLine << endl;
		stringstream ss(newLine);
		int heroID;
		double power;
		double teamMastery;
		double opponentMastery;
		int membershipIndicator;
		char commaPlaceholder; 
		ss >> heroID >> commaPlaceholder >> power >> commaPlaceholder >> teamMastery >> commaPlaceholder >> opponentMastery >> commaPlaceholder >> membershipIndicator;
		hero* newHero = new hero(heroID, power, teamMastery, opponentMastery, membershipIndicator);
		// newHero->printStats(); 
		this->heroes.insert(newHero);
	}
	//this->printAllHeroes();			
}

void game::printAllHeroes(){
	for (hero* h : heroes){
		h->printStats(); 
	}
}



