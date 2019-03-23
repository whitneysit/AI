#ifndef NODE
#define NODE
#include <list>
#include <set>
#include "hero.h"
#include <iostream>

using namespace std; 

class node
{
	public:
		hero* heroObject; 
		list<hero*> currentRadiantLineUp; 
		list<hero*> currentDireLineUp;
		//list<node> childrenNodes;
		double advantage; 
		bool isRadiantUnique;
		bool isDireUnique;
		node(hero* hero){
			this->heroObject = hero; 
			this->isRadiantUnique = true; 
			this->isDireUnique = true;
		}
		node(){
			this->heroObject = nullptr;
			this->isRadiantUnique = true; 
			this->isDireUnique = true;
		}
		

		void addToLineUp(hero* hero){
			if(currentRadiantLineUp.size() == currentDireLineUp.size()){
				for (auto h : currentRadiantLineUp){
					if (hero->getHeroID()%10 == h->getHeroID()%10){
						this->isRadiantUnique = false; 	
					}
				}
				currentRadiantLineUp.push_back(hero);

			}
			else{
				for (auto h : currentDireLineUp){
					if (hero->getHeroID()%10 == h->getHeroID()%10){
						this->isDireUnique = false; 	
					}
				}
				currentDireLineUp.push_back(hero);
			}
		}

		void addToRadiantLineUp(hero* hero){
			for (auto h : currentRadiantLineUp){
				if (hero->getHeroID()%10 == h->getHeroID()%10){
					this->isRadiantUnique = false; 	
				}
			}
			currentRadiantLineUp.push_back(hero);
			return; 
		}

		void addToDireLineUp(hero* hero){
			for (auto h : currentDireLineUp){
				if (hero->getHeroID()%10 == h->getHeroID()%10){
					this->isDireUnique = false; 	
				}
			}
			currentDireLineUp.push_back(hero);
			return;
		}

		double calculateAdvantage(){
			double advantage = 0.0; 
			for (hero*& h : currentRadiantLineUp){
				advantage += (h->getPower() * h->getTeamMastery()); 
				advantage += 100.0;
			}
			if (isRadiantUnique){
				advantage += 120.0;
			}
			for (hero*& h : currentDireLineUp){
				advantage -= (h->getPower() * h->getOpponentMastery()); 
				advantage -= 100.0;
			}
			if (isDireUnique){
				advantage -= 120.0;
			}
			return advantage;
		}
};

#endif