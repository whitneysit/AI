#include <iostream>
#include "game.h"
#include <fstream>

using namespace std; 

int main (int argc, char *argv[]){
	game newGame("input.txt");
	ofstream outFile("output.txt");
	int nextHero = newGame.makeTree();
	outFile << nextHero << '\n';
	outFile.close();
	return 0; 
}