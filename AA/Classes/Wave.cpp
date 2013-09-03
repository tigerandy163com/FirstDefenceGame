//
//  Wave.cpp
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#include "Wave.h"

using namespace cocos2d;

Wave* Wave::create(float spawnrate, int redcreeps, int greencreeps){
	Wave* wave = new Wave;
	if(wave && wave->initWithCreepSpawnRateTotalCreeps(spawnrate, redcreeps, greencreeps)){
		wave->autorelease();
		return wave;
	}
    
	CC_SAFE_DELETE(wave);
	return NULL;
}


bool Wave::initWithCreepSpawnRateTotalCreeps( float spawnrate, int redcreeps, int greencreeps){
	this->setSpawnRate(spawnrate);
	this->setRedEnemys(redcreeps);
	this->setGreenEnemys(greencreeps);
    
	return true;
}
