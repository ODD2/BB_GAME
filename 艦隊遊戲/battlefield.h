#pragma once
#include <vector>
#include <map>
#include "VESSELHEADER.h"
#include "missile.h"
#include "Explosion.h"
#define NUM_TEAM 2

using namespace std;

class BattleField
{
	friend class MainForm;
public:
	BattleField();
	~BattleField();

	void Tick();


<<<<<<< HEAD
//Create
	//team , type , name , location
	bool addVessel(int, string, string, const _2D&);
//Modify
	//origin vessel name, new vessel name.
	bool tagVessel(string, string);

//Manipulate
	//vessel name, angle, speed
	bool moveVessel(string, double, double);

	//vessel name, destination, missile type.//type no
	bool fireMissile(string,const _2D&,int=-1);
=======
	////Create
	////team , type , name , location
	//bool addVessel(int, string, string, const _2D&);
	////Modify
	////origin vessel name, new vessel name.
	//bool tagVessel(string, string);

	////Manipulate
	////vessel name, angle, speed
	//bool moveVessel(string, double, double);

	////vessel name, destination, missile type.
	//bool fireMissile(string, const _2D&, int = -1);

	////vessel name
	//bool defenseMissile(string);
>>>>>>> STRUCTURE



protected:

	map<string, vessel*> TEAM[NUM_TEAM];
	vector<missile*> MISSILE;
	//vector<terrain*> TERRAIN;
	vector<explosion*> EXPLOSION;

	inline void vesselTick();
	inline void missileTick();
	inline void explosionTick();

	inline void missileLand();
	inline void vesselDestroyed();
	//inline void terrainBlock();


	void Log(string title, string content);

	vector<string> BattleLog_TEXT;
};