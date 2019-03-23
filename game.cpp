#include "game.h"
#include "node.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set> 
#include <limits>
#include <vector>

using namespace std; 

bool compareHero(hero* hero1, hero* hero2){
	return (hero1->getHeroID() < hero2->getHeroID());
}

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
		this->heroes.push_back(newHero);
	}
	
	this->heroes.sort(compareHero);		
	this->printAllHeroes();
}



void game::printAllHeroes(){
	for (hero* h : heroes){
		h->printStats(); 
	}
}


void game::findMinimax(){
	return; 
}

void game::findNext(){
	return;
}

node game::makeTreeHelper(node& rootNode, list<hero*> remaining, int& leafNodeNum, int depth){
	if (depth == this->depth){
		//leafNodeNum++;
		rootNode.advantage = rootNode.calculateAdvantage();
		return rootNode;
	}
	bool isRadiant = false; 
	double currMaxOrMinNum = numeric_limits<int>::max(); //for min
	node currMaxOrMinNode = NULL;
	if (depth%2 == 0){
		isRadiant = true; 
		currMaxOrMinNum = numeric_limits<int>::min(); //for max
	}
	//cout << "depth: " << depth << endl;
	for (list<hero*>::iterator it = remaining.begin(); it != remaining.end(); it++){
		node newNode(*it);
		list<hero*> newList(remaining);
		newList.remove(*it);

		newNode.currentRadiantLineUp=rootNode.currentRadiantLineUp;
		newNode.currentDireLineUp=rootNode.currentDireLineUp;
		newNode.addToLineUp(newNode.heroObject); //adding itself
		// cout << "depth: " << depth << " " << (*it)->getHeroID() << " " << newNode.heroObject->getHeroID() <<  endl; 
		// for (auto h : newNode.currentRadiantLineUp){
		// cout << h->getHeroID() << " ";
		// }
		// cout << endl; 
		// for (auto h : newNode.currentDireLineUp){
		// cout << h->getHeroID() << " ";
		// }
		// cout << endl;
		//(rootNode.childrenNodes).push_back(makeTreeHelper(newNode, newList, leafNodeNum, depth+1));
		newNode = makeTreeHelper(newNode, newList, leafNodeNum, depth+1);
		cout << "depth: " << depth << " " <<  newNode.advantage << " " << newNode.heroObject->getHeroID() << endl;
		if(!isRadiant){
			if(newNode.advantage > currMaxOrMinNum){
				currMaxOrMinNum = newNode.advantage;
				currMaxOrMinNode = newNode;
			}
		}
		else {
			if(newNode.advantage < currMaxOrMinNum){
				currMaxOrMinNum = newNode.advantage;
				currMaxOrMinNode = newNode;
			}

		}
	}
	rootNode.currentRadiantLineUp = currMaxOrMinNode.currentRadiantLineUp;
	rootNode.currentDireLineUp = currMaxOrMinNode.currentDireLineUp;
	rootNode.advantage = currMaxOrMinNum;
	/*for (auto h : rootNode.currentRadiantLineUp){
		cout << h->getHeroID() << " ";
	}
	for (auto h : currMaxOrMinNode.currentRadiantLineUp){
		cout << h->getHeroID() << " ";
	}
	cout << endl; */
	cout << currMaxOrMinNum << " " << rootNode.advantage << endl; 
	return rootNode; 
}

void game::makeTree(){
	node rootNode;
	list<hero*> remaining(heroes.begin(), heroes.end());
	for (auto h : heroes){
		if(h->getMembershipIndicator() == 1){
			rootNode.addToRadiantLineUp(h);
			remaining.remove(h);
		}
		else if(h->getMembershipIndicator() == 2){
			rootNode.addToDireLineUp(h);
			remaining.remove(h);
		}
	}
	this->depth = 10 - (2*rootNode.currentRadiantLineUp.size());
	int leafNodeNum = 0; 
	this->root = makeTreeHelper(rootNode, remaining, leafNodeNum, 0);
	int nextHero = 0; 
	for (list<hero*>::iterator it = this->root.currentRadiantLineUp.begin(); it != this->root.currentRadiantLineUp.end(); it++){
		cout << (*it)->getHeroID() << endl;
		if ((*it)->getMembershipIndicator() == 0 && nextHero == 0){
			nextHero = (*it)->getHeroID(); 
		}
	}
	cout << endl; 
	for (list<hero*>::iterator it = this->root.currentDireLineUp.begin(); it != this->root.currentDireLineUp.end(); it++){
		cout << (*it)->getHeroID() << endl;
	}

	cout << "next hero: " << nextHero << endl; 
	return;
}



