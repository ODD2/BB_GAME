#include <iostream>
#include "battlefield.h"
#include "BB.h"
#include <time.h>
#include  <random>
#include<string>

BattleField::BattleField()
{
	srand(time(NULL));

	/*for (int i = 0; i < 10; i++) {
		int team = rand() % 2;
		string name = "TEST" + to_string(i);
			
		TEAM[team][name] = new BB(name,
								  _2D(rand() % (MAP_INTERVALS + 1),rand()%(MAP_INTERVALS + 1)
								  ));

		TEAM[team][name]->move(rand()%360, rand()%20);
	}

	for (int i = 0; i <100; i++) {
		MISSILE.push_back(new missile(_2D(MAP_INTERVALS,MAP_INTERVALS), 
									  _2D(fmod(rand(),MAP_INTERVALS+1) , fmod(rand(),MAP_INTERVALS+1)),
									  30, 5));
		
	}*/

}

BattleField::~BattleField()
{
	//Delete Vessel
	for (int i = 0; i < NUM_TEAM; i++) {
		map<string, vessel*>::iterator it = TEAM[i].begin();
		for (; it != TEAM[i].end(); it++) {
			delete it->second;
		}
	}

	//Delete Missile
	for (int i = 0, j = MISSILE.size(); i < j ; i++) {
		delete MISSILE[i];
	}

	//Delete  Terrain


	//Delete Explosion
	for (int i = 0, j = EFFECT.size(); i < j; i++) {
		delete EFFECT[i];
	}

}

void BattleField::Tick() {
	explosionTick();
	missileLand();
	vesselDestroyed();
	terrainDestroyed();
	vesselTick();
	missileTick();
	terrainTick();
}

inline void BattleField::vesselTick() {
	//ship movement
	for (int i = 0; i < NUM_TEAM; i++) {
		map<string, vessel*>::iterator it = TEAM[i].begin();
		for (; it != TEAM[i].end(); it++) {
			it->second->tick();
		}
	}
}

inline void BattleField::missileTick() {
	//missile movement
	for (int i = 0; i < MISSILE.size(); i++) {
		missile * ms_pt = MISSILE[i];

		if (!ms_pt->tick()) {
			Log("MISSILE_DESTROY", "Out of Range," + ms_pt->name);
			delete ms_pt;
			MISSILE.erase(MISSILE.begin()+i);
			i -= 1;
		}
	}
}

inline void BattleField::explosionTick() {
	for (int i = 0; i < EFFECT.size(); i++) {
		EFFECT[i]->tick();
		if (EFFECT[i]->radius <= 0) {
			delete EFFECT[i];
			EFFECT.erase(EFFECT.begin() + i);
			i--;
		}
	}
}

inline void BattleField::terrainTick() {
	for (int i = 0; i < TERRAIN.size(); i++) {
		if (!TERRAIN[i]->tick()) {
			//Clear Up TERRAIN
			delete TERRAIN[i];
			TERRAIN.erase(TERRAIN.begin() + i);
			i -= 1;
		}
	}
}

inline void BattleField::missileLand() {
	//check every missile.
	for (int i = 0; i < MISSILE.size(); i++) {
		missile * ms_pt = MISSILE[i];

		if (ms_pt->land()) {//==============================================================================================fail
			

			//BattleLog
			string dmgVessels = "{";


			//Create Explosion
			EFFECT.push_back(new explosion(ms_pt->damageRadius, ms_pt->Location.to_2D()));

	
			//Check any vessel hits.
			for (int i = 0; i < NUM_TEAM; i++) {
				map<string, vessel*>::iterator it = TEAM[i].begin();
				for (; it != TEAM[i].end(); it++) {
					if ( it->second->HP > 0 && it->second->hit(*ms_pt) ) {

					


						//BattleLog 
						dmgVessels += it->second->name+
							"["+to_string(it->second->Location.x)+","+to_string(it->second->Location.y)+"]"+
							",";
					}
				}
			}

			//BattleLog Adjustment;
			if (dmgVessels == "{") {
				dmgVessels = "miss";
			}
			else {
				//remove the tailing comma.
				dmgVessels.pop_back();
				dmgVessels.push_back('}');
			}

			
		
			//Log Missile Attack
			Log(ms_pt->name, "[" + to_string(ms_pt->Location.x) + "," + to_string(ms_pt->Location.y) + "]"
							" hits," + dmgVessels);

			//Removing Missile
			delete ms_pt;
			MISSILE.erase(MISSILE.begin() + i);
			i -= 1;


			
		}
	}

}

inline void BattleField::terrainCollision() {
	for (int i = 0, j = TERRAIN.size(); i < j; i++)
	{

	}
}

inline void BattleField::vesselDestroyed() {
	//Log Vessel Destroyed
	for (int i = 0; i < NUM_TEAM; i++) {
		map<string, vessel*>::iterator it = TEAM[i].begin();

		for (; it != TEAM[i].end(); ) {
			if ( it->second->HP <= 0) {
				//BattleLog 
				BattleLog_TEXT.push_back("Vessel " + it->first + " Distroyed!!");

				//Remeber to delete vessel Pointer
				delete it->second;

				//Erase MAP Object
				auto it_destroy = it++;
				TEAM[i].erase(it_destroy);


			}
			else {
				it++;
			}
		}
	}
}

inline void BattleField::terrainDestroyed() {
	
}



void BattleField::Log(string title, string content) {
	BattleLog_TEXT.push_back(title + ":" + content);
}

//team , type , name , location
bool BattleField::addVessel(int Team, string Type , string Name, const _2D& Loc) {
	for (int i = 0; i < NUM_TEAM;i++) {
		if (Team==i) {
			for (auto t:TEAM[i]) {
				if (t.second->name == Name) {
					return false;
				}
			}
		}
	}
	if (Loc.x > 20.0 || Loc.x<0 || Loc.y>20.0 || Loc.y < 0)return false;
	if (Type=="BB") {
		vessel* p = new BB(Name,Loc);
		TEAM[Team].insert(make_pair(Name,p));
	}
	else if (Type == "CG") {
		vessel* p = new CG(Name, Loc);
		TEAM[Team].insert(make_pair(Name, p));
	}
	else if (Type == "CV") {
		vessel* p = new CV(Name, Loc);
		TEAM[Team].insert(make_pair(Name, p));
	}
	else if (Type == "DD") {
		vessel* p = new DD(Name, Loc);
		TEAM[Team].insert(make_pair(Name, p));
	}
	else {
		
		return false;
	}
	return true;
}
bool BattleField::tagVessel(int team,string Pname, string Nname) {

	int i = team;
		map<string, vessel*>::iterator it = TEAM[i].find(Pname);
		map<string, vessel*>::iterator itnew = TEAM[i].find(Nname);
		if (  it!=TEAM[i].end()   &&  itnew==TEAM[i].end()) {
			TEAM[i][Nname] = new BB();
			TEAM[i][Pname]->name = Nname;
			swap(TEAM[i][Pname],TEAM[i][Nname]);
			it= TEAM[i].find(Pname);
			delete it->second;
			TEAM[i].erase(it);
			return true;
		}
	
	return false;
}

//vessel name, angle, speed
bool BattleField::moveVessel(int team,string Name, double Angle, double Speed) {
	
		map<string, vessel*>::iterator it = TEAM[team].find(Name);
		if (it != TEAM[team].end()) {
			if (!it->second->move(Angle, Speed))return false;
			else return true;
		}
	
	return false;
}
bool BattleField::defenseMissile(int team,string Name,string shellNmae) {
	
		map<string, vessel*>::iterator it = TEAM[team].find(Name);
		if (it != TEAM[team].end()) {
			int mplace = 0;
			for (auto &X:MISSILE) {
				if (X->name == shellNmae && it->second->defense(*X) ) {
					delete X;
					MISSILE.erase(MISSILE.begin()+ mplace);
					return true;
				}
				mplace++;
			}
			
		}
	
	return false;
}
bool BattleField::fireMissile(int team,string Name,  _2D&loc , int type) {
	if (loc.x > 20.0 || loc.x<0 || loc.y>20.0 || loc.y < 0)return false;
	
	for (auto T : TEAM[team]) {
			if (T.second->name == Name) {//=================================
				missile *p = new missile();
				string SN = "Shell_";
				SN.push_back(team+'A');
				SN.push_back((Num_shot[team]++)+1+'0');
				*p = T.second->attack(loc);
				p->name = SN;
				MISSILE.push_back(p);
				//
				string log = "Team";
				log.push_back(team + 'A');
				log += " " + Name + " Fire to (" + to_string(loc.x)+ ","+to_string(loc.y) +")-> "+SN;
				BattleLog_TEXT.push_back(log);
				//
				return true;
			}
		}
	
	return false;
}

void BattleField::ULT( int team,string V_name) {


	//Location, Destination, Speed, Damage
	map<string, vessel*>::iterator it = TEAM[team].find(V_name);
	if (it != TEAM->end()) {
		for (int i = 0; i < 360;i+=15) {
	
			missile*p = new missile(_2D(it->second->Location.x, it->second->Location.y), _2D(3*sin(i)+ it->second->Location.x,3*cos(i)+ it->second->Location.y),8, 1);
			MISSILE.push_back(p);
		}
	}
	
	

}