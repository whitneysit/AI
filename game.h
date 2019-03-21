#ifndef GAME
#define GAME

#include "hero.h"
#include <set>
#include <fstream>

using namespace std; 

enum Algorithm { MINIMAX, AB };

class game
{

	private:
		set<hero*> heroes;
		string filename;
		int numberOfHeroes; 
		enum Algorithm algorithm;

	public:	
		game(string filename);
		~game(){};

		void printAllHeroes();
		
};

#endif