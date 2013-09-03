//
//  Wave.h
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#ifndef __MyTowerDefense2D__Wave__
#define __MyTowerDefense2D__Wave__

#include "cocos2d.h"
#include "Enemy.h"

class Wave : public cocos2d::CCNode {
public:
	bool initWithCreepSpawnRateTotalCreeps(float spawnrate, int redcreeps, int greencreeps);
    
	static Wave* create(float spawnrate, int redcreeps, int greencreeps);
    
	CC_SYNTHESIZE(float, _spawnRate, SpawnRate);
    
	CC_SYNTHESIZE(int, _redEnemys, RedEnemys);
	CC_SYNTHESIZE(int, _greenEnemys, GreenEnemys);
};


#endif /* defined(__MyTowerDefense2D__Wave__) */
