#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set> 
#include <limits>
#include <vector>
#include <list>

using namespace std;

class game;
class node;

class hero
{

private:
	int heroID;
	double power;
	double teamMastery;
	double opponentMastery;
	int membershipIndicator; //you(1), opponent(2), available(0)
public:
	hero(int heroID, double power, double teamMastery, double opponentMastery, int membershipIndicator);
	~hero(){};

	
	int getHeroID(){ return this->heroID; }
	double getPower(){ return this->power; }
	double getTeamMastery(){ return this->teamMastery; }
	double getOpponentMastery(){ return this->opponentMastery; }
	void setMembershipIndicator(int membershipIndicator){ this->membershipIndicator = membershipIndicator; }
	int getMembershipIndicator(){ return this->membershipIndicator; }

	
	
};

hero::hero(int heroID, double power, double teamMastery, double opponentMastery, int membershipIndicator)
{
	this->heroID = heroID;
	this->power = power; 
	this->teamMastery = teamMastery; 
	this->opponentMastery = opponentMastery; 
	this->membershipIndicator = membershipIndicator; 
}

class node
{
	public:
		hero* heroObject; 
		vector<hero*> currentRadiantLineUp; 
		vector<hero*> currentDireLineUp;
		double alpha; 
		double beta; 
		double advantage; 
		node(hero* hero){
			this->heroObject = hero;
		}
		node(){
			this->heroObject;
		}
		void addToLineUp(hero* hero); 
		void addToRadiantLineUp(hero* hero);
		void addToDireLineUp(hero* hero);
		double calculateAdvantage(); 
				
};

void node::addToLineUp(hero* hero){
	if(currentRadiantLineUp.size() == currentDireLineUp.size()){
		currentRadiantLineUp.push_back(hero);

	}
	else{
		currentDireLineUp.push_back(hero);
	}
}

void node::addToRadiantLineUp(hero* hero){
	currentRadiantLineUp.push_back(hero);
	return; 
}

void node::addToDireLineUp(hero* hero){
	currentDireLineUp.push_back(hero);
	return;
}

double node::calculateAdvantage(){
	double advantage = 0.0; 
	bool isRadiantUnique = true; 
	bool isDireUnique = true; 
	for (int i = 0; i < currentRadiantLineUp.size(); i++){
		hero* h = currentRadiantLineUp[i];
		for (int j = (i + 1); j < currentRadiantLineUp.size(); j++)
		{
			if (currentRadiantLineUp[i]->getHeroID()%10 == currentRadiantLineUp[j]->getHeroID()%10){
				isRadiantUnique = false; 
			}
		}
		advantage += (h->getPower() * h->getTeamMastery());
		advantage += 100; 
		//cout << h->getHeroID() << " "; 
	}
	if (isRadiantUnique){
		advantage += 120; 
		//cout << "Radiant is Unique" << endl << endl; 
	}
	for (int i = 0; i < currentDireLineUp.size(); i++){
		hero* h = currentDireLineUp[i];
		for (int j = (i + 1); j < currentDireLineUp.size(); j++)
		{
			if (currentDireLineUp[i]->getHeroID()%10 == currentDireLineUp[j]->getHeroID()%10){
				isDireUnique = false; 
			}
		}
		advantage -= (h->getPower() * h->getOpponentMastery());
		advantage -= 100; 
		//cout << h->getHeroID() << " "; 
	}
	if (isDireUnique){
		advantage -= 120; 
		//cout << "Dire is Unique" << endl << endl; 
	}
	return advantage;
}



enum Algorithm { MINIMAX, AB };

class game
{

	private:
		list<hero*> heroes;
		string filename;
		int numberOfHeroes; 
		enum Algorithm algorithm;
		node makeTreeHelper(node& root, list<hero*> remaining, int& leafNodeNum, int depth, double alpha, double beta);
		node root;
		int depth; 

	public:	
		game(string filename);
		~game(){};

		void printAllHeroes();
		int makeTree();
		
};




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
	//cout << this->numberOfHeroes << endl;
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
	/*for (hero* h : heroes){
		//h->printStats(); 
	}*/
	return;
}

node game::makeTreeHelper(node& rootNode, list<hero*> remaining, int& leafNodeNum, int depth, double alpha, double beta){
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
		newNode.addToLineUp(newNode.heroObject);
		newNode = makeTreeHelper(newNode, newList, leafNodeNum, depth+1, alpha, beta);

		if(isRadiant){
			if(newNode.advantage > currMaxOrMinNum){
				currMaxOrMinNum = newNode.advantage;
				currMaxOrMinNode = newNode;
				if (this->algorithm == AB){
					alpha = max(alpha, newNode.advantage);
					//cout << alpha << " " << beta << endl;
					if (beta <= alpha){
						//cout << "Break " << endl; 
						break;
					}
				}
			}
		}
		else {
			if(newNode.advantage < currMaxOrMinNum){
				currMaxOrMinNum = newNode.advantage;
				currMaxOrMinNode = newNode;
				if (this->algorithm == AB){
					//cout << alpha << " " << beta << endl;
					beta = min(beta, newNode.advantage);
					if (beta <= alpha){
						//cout << "Break " << endl; 
						break; 
					}
				}
			}
		}
	}
	rootNode.currentRadiantLineUp = currMaxOrMinNode.currentRadiantLineUp;
	rootNode.currentDireLineUp = currMaxOrMinNode.currentDireLineUp;
	rootNode.advantage = currMaxOrMinNum;
	return rootNode; 
}

int game::makeTree(){
	node rootNode;
	list<hero*> remaining(heroes.begin(), heroes.end());
	double alpha =  numeric_limits<int>::min();
	double beta = numeric_limits<int>::max();
	int counter = 0;
	for (list<hero*>::iterator it = heroes.begin(); it != heroes.end(); it++){
		hero* h = *it; 
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
	this->root = makeTreeHelper(rootNode, remaining, leafNodeNum, 0, alpha, beta);
	int nextHero = 0; 
	//cout << endl;
	for (vector<hero*>::iterator it = this->root.currentRadiantLineUp.begin(); it != this->root.currentRadiantLineUp.end(); it++){
		//cout << (*it)->getHeroID() << endl;
		if ((*it)->getMembershipIndicator() == 0 && nextHero == 0){
			nextHero = (*it)->getHeroID(); 
		}
	}
	//cout << endl; 
	for (vector<hero*>::iterator it = this->root.currentDireLineUp.begin(); it != this->root.currentDireLineUp.end(); it++){
		//cout << (*it)->getHeroID() << endl;
	}

	//cout << "next hero: " << nextHero << endl; 
	return nextHero;
}

int main (int argc, char *argv[]){
	game newGame("input.txt");
	ofstream outFile("output.txt");
	int nextHero = newGame.makeTree();
	outFile << nextHero <<'\n';
	outFile.close();
	return 0; 
}