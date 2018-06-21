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

	/*for (int i = 0; i < 50; i++) {
		int team = rand() % 2;
		string name = "TEST" + to_string(i);
			
		TEAM[team][name] = new BB(name,
								  _2D(rand() % (MAP_INTERVALS + 1),rand()%(MAP_INTERVALS + 1)));

		TEAM[team][name]->move(rand()%360, 5);
	}*/

/*for (int i = 0; i <100; i++) {
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
	//terrainTick();
	vesselCollision();
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

//inline void BattleField::terrainTick() {
//	for (int i = 0; i < TERRAIN.size(); i++) {
//		if (!TERRAIN[i]->tick()) {
//			//Clear Up TERRAIN
//			delete TERRAIN[i];
//			TERRAIN.erase(TERRAIN.begin() + i);
//			i -= 1;
//		}
//	}
//}

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

//inline void BattleField::terrainCollision() {
//	for (int i = 0, j = TERRAIN.size(); i < j; i++)
//	{
//
//	}
//}

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

inline void BattleField::vesselCollision() {
	for (int i = 0; i < NUM_TEAM;i++) {
		for (auto &V1 : TEAM[i]) {
			for (int j = i + 1; j < NUM_TEAM;j++) {
				for (auto  &V2:TEAM[j]) {
					if (Distance_2D((V1.second->Location),(V2.second->Location))<0.1 && (V1.second->speed!=0||V2.second->speed!=0 )) {
						string v1Name=V1.second->name, v2Name=V2.second->name;
						v1Name += " crash into " + v2Name + "!(HP-1)";
						BattleLog_TEXT.push_back(v1Name);
						V1.second->speed = 0;
						V1.second->HP -= 1;
						V2.second->speed = 0;
						V2.second->HP -= 1;
					}
				}
			}
		}
	}
}


void BattleField::Log(string title, string content) {
	BattleLog_TEXT.push_back(title + ":" + content);
}

bool BattleField::addVessel(int Team, string Type , string Name, const _2D& Loc) {
	try {
		bool b = true;

		if (!TEAM[Team].count(Name) && Name != "" && Type != "") {
			if (Loc.x > 20.0 || Loc.x<0 || Loc.y>20.0 || Loc.y < 0) {
				b = false;
			}
			else if (Type == "BB") {
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
				b = false;
			}
		}
		else
		{
			b = false;
		}
		string log = "Team";
		log.push_back(Team + 'A');
		if (b) {
			log += " SET " + Name + " with " + Type + " at(" + to_string(Loc.x) + "," + to_string(Loc.y) + ")->Success";
		}
		else {
			log += " SET " + Name + " with " + Type + " at(" + to_string(Loc.x) + "," + to_string(Loc.y) + ")->Fail";
		}
		BattleLog_TEXT.push_back(log);
		return b;
	}
	catch (...) {
		return false;
	}
	
}

bool BattleField::tagVessel(int team,string Pname, string Nname) {
	try {
		string log = "Team";
		log.push_back(team + 'A');

		if (Pname == "" || Nname == "") {
		}
		else if (TEAM[team].count(Pname) && !TEAM[team].count(Nname)) {
			TEAM[team][Nname] = new BB();
			TEAM[team][Pname]->name = Nname;
			swap(TEAM[team][Pname], TEAM[team][Nname]);
			delete TEAM[team][Pname];
			TEAM[team].erase(Pname);
			log += " RENAME " + Pname + " to " + Nname + " -> Success";
			BattleLog_TEXT.push_back(log);
			return true;
		}
		
		log += " RENAME " + Pname + " to " + Nname + " -> Fail";
		BattleLog_TEXT.push_back(log);
		return false;
	}
	catch (...) {
		return false;
	}	
}

bool BattleField::moveVessel(int team,string Name, double Angle, double Speed) {
	try {
		string log = "Team"; log.push_back(team + 'A');

		if (TEAM[team].count(Name)) {
			if (TEAM[team][Name]->move(Angle, Speed)) {
				log += " " + Name + " MOVE to " + to_string(Angle) + " as " + to_string(Speed) + "-> Success";
				BattleLog_TEXT.push_back(log);
				return true;
			}
		}

		log += " " + Name + " MOVE to " + to_string(Angle) + " as " + to_string(Speed) + "->Fail";
		BattleLog_TEXT.push_back(log);
		return false;
	}
	catch (...) {
		return false;
	}	
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

							//Battle Log
							{
								string log = Name + " DEFENSE " + shellName + " -> Hit";
								BattleLog_TEXT.push_back(log);
							}
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

			//Battle Log
			{
				string log = Name + " DEFENSE " + shellName + " -> Fail";
				BattleLog_TEXT.push_back(log);
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
						//Battle Log
						{
							string log = Name + " ACTIVATE NOVA -> Success";
							BattleLog_TEXT.push_back(log);
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

			//Battle Log
			{
				string log = Name + " ACTIVATE NOVA -> Fail";
				BattleLog_TEXT.push_back(log);
			}
			
		}
		else {
			return false;
		}
}

bool BattleField::fireMissile(int team,string Name, string type, ...) {
	static unsigned int MISSILE_ID[2] = { 1,1 };
	string log = "Team"; log.push_back(team + 'A');
	
	try {
		if (type == ATTACK_MISSILE) {

			va_list vl;
			va_start(vl, type);
			_2D& loc = va_arg(vl, _2D);
			va_end(vl);

			if (loc.x > 20.0 || loc.x<0 || loc.y>20.0 || loc.y < 0)throw loc;

			if (TEAM[team].count(Name)) {


				missile *p = nullptr;
				p = TEAM[team][Name]->attack(type, loc);


				string SN = "Shell_";
				SN.push_back(team + 'A');
				SN += to_string(MISSILE_ID[team]++);

				p->name = SN;

				MISSILE.push_back(p);

				//SUCCESS LOG
				{
					log += " " + Name + " Fire to (" + to_string(loc.x) + "," + to_string(loc.y) + ")-> " + SN;
					BattleLog_TEXT.push_back(log);
				}
				return true;


			}
			else {
				throw - 4;
			}
		}
		else if (type == ATTACK_TRACKER)
		{
			va_list vl;
			va_start(vl, type);
			string target = va_arg(vl, string);
			va_end(vl);
			if (TEAM[team].count(Name)) {
				if (TEAM[!team].count(target)) {
					missile *p = nullptr;
					p = TEAM[team][Name]->attack(type, TEAM[!team][target]);

					string SN = "Shell_";
					SN.push_back(team + 'A');
					SN += to_string(MISSILE_ID[team]++);

					p->name = SN;

					MISSILE.push_back(p);

					//SUCCESS LOG
					{
						log += " " + Name + " Fire to " +target + " -> " + SN;
						BattleLog_TEXT.push_back(log);
					}
					return true;
				}
			}
			else {
				throw - 4;
			}

			////Battle Log
			//{
			//	log = log + " " + Name + " Failed to Fire Tracker Missle -> " + target;
			//	BattleLog_TEXT.push_back(log);
			//}
			return false;

		}
		else {
			throw -3;
		}
	}
	catch (int e) {
		if (e == -2) {
			//ON COOLDOWN
			log += " " + Name + " CoolDown = " + to_string(TEAM[team][Name]->atkCD);
			BattleLog_TEXT.push_back(log);
			return false;
		}
		else if (e == -3) {
			//unknown attack type
			log += " " + type + " is not in " + Name +"'s Weapon List!" ;
			BattleLog_TEXT.push_back(log);
			return false;
		}
		else if (e == -4) {
			log += " " + Name + " not exist!!! -> Fail";
			BattleLog_TEXT.push_back(log);
			return false;
		}
	}
	catch (_2D& e) {
		//out of distance
		log += " " + Name + " Fire to (" + to_string(e.x) + "," + to_string(e.y) + ") -> Failed: Out Of Range";
		BattleLog_TEXT.push_back(log);
		return false;
	}
	catch (vessel *) {
		//target is nullptr;
		return false;
	}
	catch (...) {
		return false;
		//UNKNOWN EXCEPTION
	}
	
}

bool BattleField::ULT( int team,string V_name) {

	//Location, Destination, Speed, Damage
	if (TEAM[team].count(V_name)) {	
		for (int i = 0; i < 360;i+=15) {
			missile *p = new missile(_2D(TEAM[team][V_name]->Location.x, TEAM[team][V_name]->Location.y), _2D(3*sin(i)+ TEAM[team][V_name]->Location.x,3*cos(i)+ TEAM[team][V_name]->Location.y),8, 1);
			MISSILE.push_back(p);
		}
	}
	string log = V_name + " use ULT";
	BattleLog_TEXT.push_back(log);
	return true;
}

bool BattleField::Special(int team) {
	static unsigned int LIMIT[2] = { 3,3 };
	if (team==0) {

		if (LIMIT[team]) {
			LIMIT[team] -= 1;
			for (auto it = TEAM[1].begin(); it != TEAM[1].end(); it++){
				MISSILE.push_back(new TrackerMissile(_2D(MAP_INTERVALS/2,0), it->second, 5, 3));
			}
			string log = "TeamA Special Attack -> CABOOM , Success";
			BattleLog_TEXT.push_back(log);
			return true;
		}
		else {
			string log = "TeamA Special Attack -> CABOOM , Fail";
			BattleLog_TEXT.push_back(log);
		}

	}
	else if (team==1) {

		if (LIMIT[team]) {
			LIMIT[team] -= 1;
			for (auto it = TEAM[0].begin(); it != TEAM[0].end(); it++) {
				it->second->HP -= 2;
				EFFECT[EF_LINE].push_back(new LineEffect(QColor(0,255,0), 4, 7, _2D(MAP_INTERVALS / 2, MAP_INTERVALS), it->second->Location));
			}
			string log = "TeamB Special Attack -> SHALALA , Success";
			BattleLog_TEXT.push_back(log);
			return true;
		}
		else {
			string log = "TeamB Special Attack -> SHALALA , Fail";
			BattleLog_TEXT.push_back(log);
		}
		
	}
	return false;
}