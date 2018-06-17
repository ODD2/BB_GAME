#include <iostream>
#include "battlefield.h"
#include "BB.h"
#include <time.h>
#include  <random>


BattleField::BattleField()
{
	srand(time(NULL));

	for (int i = 0; i < 10; i++) {
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
		
	}
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

		if (ms_pt->land()) {
			

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