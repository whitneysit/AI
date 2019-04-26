#ifndef GAME
#define GAME

#include "hero.h"
#include "node.h"
#include <set>
#include <list>
#include <fstream>

using namespace std; 

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

#endif