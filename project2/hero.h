#ifndef HERO
#define HERO

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

	void printStats();
	
};

#endif