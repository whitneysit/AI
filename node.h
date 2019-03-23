#ifndef NODE
#define NODE
#include <list>
#include <set>
#include "hero.h"
#include <iostream>
#include <vector>
#include <limits>


using namespace std; 

class node
{
	public:
		hero* heroObject; 
		vector<hero*> currentRadiantLineUp; 
		vector<hero*> currentDireLineUp;
		//list<node> childrenNodes;
		double alpha; 
		double beta; 
		double advantage; 
		node(hero* hero){
			this->heroObject = hero;
			this->alpha =  numeric_limits<int>::min();
			this->beta = numeric_limits<int>::max();
		}
		node(){
			this->heroObject = nullptr;
			this->alpha =  numeric_limits<int>::min();
			this->beta = numeric_limits<int>::max();
		}
		

		void addToLineUp(hero* hero){
			if(currentRadiantLineUp.size() == currentDireLineUp.size()){
				currentRadiantLineUp.push_back(hero);

			}
			else{
				currentDireLineUp.push_back(hero);
			}
		}

		void addToRadiantLineUp(hero* hero){
			currentRadiantLineUp.push_back(hero);
			return; 
		}

		void addToDireLineUp(hero* hero){
			currentDireLineUp.push_back(hero);
			return;
		}

		double calculateAdvantage(){
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
				cout << h->getHeroID() << " "; 
			}
			cout << endl << endl;
			if (isRadiantUnique){
				advantage += 120; 
				cout << "Radiant is Unique" << endl << endl; 
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
				cout << h->getHeroID() << " "; 
			}
			cout << endl;
			if (isDireUnique){
				advantage -= 120; 
				cout << "Dire is Unique" << endl << endl; 
			}
			return advantage;
		}
};

#endif