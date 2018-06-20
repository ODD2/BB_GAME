#include <iostream>
#include <stdarg.h>
#include <time.h>
#include <random>
#include <string>
#include "battlefield.h"
#include "BB.h"

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


	//Delete effect
	for (int j = 0; j < EFFECTS::EF_END; j++) {
		for (int i = 0,k = EFFECT[j].size(); i < k; i++) {
				delete EFFECT[j][i];
		}
	}

}

void BattleField::Tick() {
	effectTick();
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

inline void BattleField::effectTick() {
	for (int j = 0; j < EFFECTS::EF_END; j++) {
		for (int i = 0; i < EFFECT[j].size(); i++) {
			EFFECT[j][i]->tick();
			if (EFFECT[j][i]->dead()) {
				delete EFFECT[j][i];
				EFFECT[j].erase(EFFECT[j].begin() + i);
				i--;
			}
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

			//Create effect
			//EFFECT[EFFECTS::EF_ROUND_SHRINK].push_back(new RoundShrink(PIC_MS_EX,ms_pt->damageRadius, ms_pt->Location.to_2D()));
			EFFECT[EFFECTS::EF_ROUND_EXPAND].push_back(new RoundExpand(PIC_MS_EX, ms_pt->damageRadius, ms_pt->Location.to_2D()));

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
	if (!TEAM[Team].count(Name)) {
		if (Loc.x > 20.0 || Loc.x<0 || Loc.y>20.0 || Loc.y < 0)return false;
		if (Type == "BB") {
			vessel* p = new BB(Name, Loc);
			TEAM[Team].insert(make_pair(Name, p));
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
	return false;
}

bool BattleField::tagVessel(int team,string Pname, string Nname) {

	int i = team;
		if ( TEAM[team].count(Pname) && !TEAM[team].count(Nname)) {
			TEAM[i][Nname] = new BB();
			TEAM[i][Pname]->name = Nname;
			swap(TEAM[i][Pname],TEAM[i][Nname]);
			delete TEAM[i][Pname];
			TEAM[i].erase(Pname);
			return true;
		}
	
	return false;
}

//vessel name, angle, speed
bool BattleField::moveVessel(int team,string Name, double Angle, double Speed) {
	
		
		if (TEAM[team].count(Name)) {
			if (!TEAM[team][Name]->move(Angle, Speed))return false;
			else return true;
		}
	
	return false;
}

bool BattleField::defenseMissile(int team, string Name, string type, ...) {
		
		if(type == DEFENSE_LAZER){

			va_list vl;
			va_start(vl, type);
			string shellName = va_arg(vl, string);
			va_end(vl);

			if (TEAM[team].count(Name)) {
				try {
					int mplace = 0;
					for (auto X : MISSILE) {
						if (X->name == shellName && TEAM[team][Name]->defense(DEFENSE_LAZER, *X)) {

							//Defense Lazer Effect Create
							EFFECT[EFFECTS::EF_LINE].push_back(new LineEffect(QColor(255, 0, 0), 2, 2, TEAM[team][Name]->Location, X->Location.to_2D()));

							delete X;
							MISSILE.erase(MISSILE.begin() + mplace);
							return true;
						}
						mplace++;
					}
				}
				catch (int e) {
					if (e == -2) {
						//unkown type.
					}
				}
				catch (...) {
					//unkown exception
				}
			}

		}
		else if (type == DEFENSE_NOVA) {
			if (TEAM[team].count(Name)) {
				try {
					if (TEAM[team][Name]->defense(type)) {
						//Create Nova Effect
						EFFECT[EFFECTS::EF_ROUND_EXPAND].push_back(new RoundExpand(PICS::PIC_DEF_NOVA, DEF_NOVA_RANGE, TEAM[team][Name]->Location));

						int mplace = 0;
						for (int i = 0; i < MISSILE.size();i++) {
							if (Distance_2D(TEAM[team][Name]->Location,   MISSILE[i]->Location.to_2D()) <= DEF_NOVA_RANGE) {
								delete MISSILE[i];
								MISSILE.erase(MISSILE.begin() + mplace);
								i -= 1;
							}
						}
						return true;
					}
				}
				catch (int e) {
					if (e == -2);//unkown def type.
				}
				catch (...){
					//unknown exception
				}
			}
		}
		else {
			return false;
		}
		
		return false;
	
}

bool BattleField::fireMissile(int team,string Name, string type, ...) {
	if (type == ATTACK_MISSILE) {

		va_list vl;
		va_start(vl, type);
		_2D& loc = va_arg(vl,_2D);
		va_end(vl);

		if (loc.x > 20.0 || loc.x<0 || loc.y>20.0 || loc.y < 0)return false;
		if (TEAM[team].count(Name)) {
			string log = "Team"; log.push_back(team + 'A');
			try {
				missile *p = nullptr;
				p = TEAM[team][Name]->attack(type,loc);


				string SN = "Shell_";
				SN.push_back(team + 'A');
				SN.push_back((Num_shot[team]++) + '1');

				p->name = SN;

				MISSILE.push_back(p);

				//SUCCESS LOG
				{
					log += " " + Name + " Fire to (" + to_string(loc.x) + "," + to_string(loc.y) + ")-> " + SN;
					BattleLog_TEXT.push_back(log);
				}
				return true;
			}
			catch (int e) {
				if (e == -1) {
					log += " " + Name + " Fire to (" + to_string(loc.x) + "," + to_string(loc.y) + ") -> Failed: Out Of Range";
					BattleLog_TEXT.push_back(log);
					return false;
				}
				else if (e == -2) {
					//ON COOLDOWN
					return false;
				}
				else if (e == -3) {
					//unknown attack type
					return false;
				}
			}
			catch (...) {
				return false;
				//UNKNOWN EXCEPTION
			}
		}

	}
	else if (type == ATTACK_TRACKER)
	{

	}
	else {
		return false;
	}
	
}

void BattleField::ULT( int team,string V_name) {

	//Location, Destination, Speed, Damage
	if (TEAM[team].count(V_name)) {	
		for (int i = 0; i < 360;i+=15) {
			missile *p = new missile(_2D(TEAM[team][V_name]->Location.x, TEAM[team][V_name]->Location.y), _2D(3*sin(i)+ TEAM[team][V_name]->Location.x,3*cos(i)+ TEAM[team][V_name]->Location.y),8, 1);
			MISSILE.push_back(p);
		}
	}

}