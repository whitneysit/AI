#include <iostream>
#include "game.h"

using namespace std; 

int main (int argc, char *argv[]){
	cout << "hello world" << endl; 
	game newGame("test_case/input8.txt");
	newGame.makeTree();
	return 0; 
}