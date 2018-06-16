#include <iostream>
#include "battlefield.h"
#include <time.h>
#include  <random>
#include<string>

BattleField::BattleField()
{
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		int team = rand() % 2;
		string name = "TEST" + to_string(i);
			
		TEAM[team][name] = new BB(name, _2D(rand() % 21, rand() % 21));
		TEAM[team][name]->move(rand()%360, rand()%20);
	}

	for (int i = 0; i <100; i++) {
		MISSILE.push_back(new missile(_2D(20,20), _2D(fmod(rand(),21) , fmod(rand(),21)), 30, 5));
		
	}
}

BattleField::~BattleField()
{
}

void BattleField::Tick() {
	explosionTick();
	missileLand();
	vesselDestroyed();
	vesselTick();
	missileTick();
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
	for (int i = 0; i < EXPLOSION.size(); i++) {
		EXPLOSION[i]->tick();
		if (EXPLOSION[i]->radius <= 0) {
			delete EXPLOSION[i];
			EXPLOSION.erase(EXPLOSION.begin() + i);
			i--;
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
			EXPLOSION.push_back(new explosion(ms_pt->damageRadius, ms_pt->Location.to_2D()));

	
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

inline void BattleField::vesselDestroyed() {
	//Log Vessel Destroyed
	for (int i = 0; i < NUM_TEAM; i++) {
		map<string, vessel*>::iterator it = TEAM[i].begin();

		for (; it != TEAM[i].end(); ) {
			if ( it->second->HP <= 0) {
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
bool BattleField::tagVessel(string Pname, string Nname) {

	for (int i = 0; i < NUM_TEAM;i++) {
		map<string, vessel*>::iterator it = TEAM[i].find(Pname);
		map<string, vessel*>::iterator itnew = TEAM[i].find(Nname);
		if (  it!=TEAM[i].end()   &&  itnew==TEAM[i].end()) {
			TEAM[i][Nname] = new BB();
			swap(TEAM[i][Pname],TEAM[i][Nname]);
			it= TEAM[i].find(Pname);
			delete it->second;
			TEAM[i].erase(it);
			return true;
		}
	}
	return false;
}

//vessel name, angle, speed
bool BattleField::moveVessel(string Name, double Angle, double Speed) {
	for (int i = 0; i < NUM_TEAM; i++) {
		map<string, vessel*>::iterator it = TEAM[i].find(Name);
		if (it != TEAM[i].end()) {
			it->second->angle = Angle;
			it->second->speed = Speed;
			return true;
		}
	}
	return false;
}
bool BattleField::defenseMissile(string Name,string shellNmae) {
	for (int i = 0; i < NUM_TEAM; i++){
		map<string, vessel*>::iterator it = TEAM[i].find(Name);
		if (it != TEAM[i].end()) {
			for (auto &i:MISSILE) {
				if  (i->name==shellNmae && it->second->defense(*i)) {
					return true;
				}
			}
		}
	}
	return false;
}
bool BattleField::fireMissile(string Name,  _2D&loc, int type ) {
	if (loc.x > 20.0 || loc.x<0 || loc.y>20.0 || loc.y < 0)return false;
	for(int i=0;i<NUM_TEAM;i++){ 
		for (auto T : TEAM[i]) {
			if (T.second->name == Name) {//=================================
				missile *p = new missile();
				string SN = "Shell_";
				SN.push_back(i+'A');
				SN.push_back((Num_shot[i]++)+1+'0');
				p->name = SN;
				*p = T.second->attack(loc);
				MISSILE.push_back(p);
				//
				string log = "Team";
				log.push_back(i + 'A');
				log += " " + Name + " Fire to (" + to_string(loc.x)+ ","+to_string(loc.y) +")-> "+SN;
				BattleLog_TEXT.push_back(log);
				//
				return true;
			}
		}
	}
	return false;
}