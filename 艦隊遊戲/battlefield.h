#pragma once
#include <vector>
#include <map>
#include "VESSELHEADER.h"
#include "MISSILEHEADER.h"
#include "EFFECTHEADER.h"
#include "missile.h"
#include "effect.h"
#include "terrain.h"
#define NUM_TEAM 2

using namespace std;

class BattleField
{
	friend class MainForm;
public:
	BattleField();
	~BattleField();

	void Tick();


	//Create
	//team, type , name , location
	bool addVessel(int, string, string, const _2D&);

	//Modify
	//team, vessel name, new vessel name.
	bool tagVessel(int, string, string);

	//Manipulate
	//tesm, vessel name, angle, speed
	bool moveVessel(int, string, double, double);

	//team, vessel name, attack type, ...
	bool fireMissile(int, string, string, ...);

	//team, vessel name, defense type,...
	bool defenseMissile(int, string, string,...);

	//ult vessel_name  team
	bool ULT(int,string);

	bool Special(int);

protected:

	map<string, vessel*> TEAM[NUM_TEAM];//name vessel
	vector<missile*> MISSILE;
	vector<terrain*> TERRAIN;
	vector<effect*> EFFECT[EF_END];

	//Ticks
	inline void vesselTick();
	inline void missileTick();
	inline void effectTick();
	//inline void terrainTick();

	//Collisions
	inline void missileLand();
	//inline void terrainCollision();

	//Clear up
	inline void vesselDestroyed();
	inline void terrainDestroyed();
	inline void vesselCollision();





	void Log(string title, string content);
	vector<string> BattleLog_TEXT;
};