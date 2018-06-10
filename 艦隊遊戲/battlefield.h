#pragma once
#include <vector>
#include <map>
#include "VESSELHEADER.h"
#define NUM_TEAM 2

using namespace std;

class battlefield
{
	friend class MainForm;
public:
	battlefield();
	~battlefield();

	void Tick();


//Create
	//team , type , location
	bool addVessel(int, string, const _2D&);
//Modify
	//origin vessel name, new vessel name.
	bool tagVessel(string, string);

//Manipulate
	//vessel name , destination, speed
	bool moveVessel(string, const _2D&, double);

	//vessel name, destination, missile type.
	bool fireMissile(string,const _2D&,int=-1);

	//vessel name
	bool defenseMissile(string);

	

protected:

	map<string,vessel*> TEAM[NUM_TEAM];
	vector<missile*> MISSILE;
	//vector<terrain*> TERRAIN;

	string BattleLog_TEXT;
};

