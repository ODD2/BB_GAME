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
	//team, type , name , location
	bool addVessel(int, string, string, const _2D&);

	//Modify
	//team, vessel name, new vessel name.
	bool tagVessel(int, string, string);

	//Manipulate
	//tesm, vessel name, angle, speed
	bool moveVessel(int, string, double, double);

	//team, vessel name, destination,  missile type
	bool fireMissile(int,  string, _2D&, int = -1);

	//team, vessel name shell name
	bool defenseMissile(int, string, string);

	//ult vessel_name  team
	void ULT(int,string);

protected:

	map<string, vessel*> TEAM[NUM_TEAM];//name vessel
	vector<missile*> MISSILE;
	vector<terrain*> TERRAIN;
	vector<explosion*> EFFECT;


	//Ticks
	//發射過的飛彈數量
	int Num_shot[NUM_TEAM] = { 0 };

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
	inline void vesselCollision();

	void Log(string title, string content);
	vector<string> BattleLog_TEXT;
};