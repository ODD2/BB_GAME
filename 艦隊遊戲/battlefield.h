#pragma once
#include <vector>
#include <map>
#include "VESSELHEADER.h"
#include "missile.h"
#include "explosion.h"
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
	//team , type , name , location
	bool addVessel(int, string, string, const _2D&);
	//Modify
	//origin vessel name, new vessel name.
	bool tagVessel(string, string);

	//Manipulate
	//vessel name, angle, speed
	bool moveVessel(string, double, double);

	//vessel name, destination, . team   missile type
	bool fireMissile(string, _2D&, int, int = -1);

	//vessel name shell name
	bool defenseMissile(string,string);

	//ult vessel_name  team
	void ULT(string,int);

protected:

	map<string, vessel*> TEAM[NUM_TEAM];//name vessel
	vector<missile*> MISSILE;
	vector<terrain*> TERRAIN;
	vector<explosion*> EFFECT;

<<<<<<< HEAD
	//Ticks
=======
	//發射過的飛彈數量
	int Num_shot[NUM_TEAM] = { 0 };

>>>>>>> ERICE
	inline void vesselTick();
	inline void missileTick();
	inline void explosionTick();
	inline void terrainTick();

	//Collisions
	inline void missileLand();
	inline void terrainCollision();

	//Clear up
	inline void vesselDestroyed();
	inline void terrainDestroyed();


	void Log(string title, string content);
	vector<string> BattleLog_TEXT;
};