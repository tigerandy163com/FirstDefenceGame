//
//  TileData.cpp
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#include "TileData.h"

using namespace cocos2d;

TileData* TileData::create(cocos2d::CCPoint pos){
	TileData* td = new TileData;
	if(td && td->initWithPosition(pos)){
		td->autorelease();
		return td;
	}
	CC_SAFE_DELETE(td);
	return NULL;
}

bool TileData::initWithPosition(cocos2d::CCPoint pos){
	bool bRet = false;
	do
	{
		this->setPosition(pos);
        
		parentTile = NULL;
		gScore = 0;
		hScore = 0;
        
		isUsed = false;
        direction = KUnKnow;
		isThroughing = false;
		isThroughingCount = 0;
        
		bRet = true;
	} while (0);
	return bRet;
}

int TileData::fScore(){
	return gScore + hScore;
}

bool TileData::getIsThroughing(){
	return isThroughing;
}

void TileData::setIsThroughing(bool var){
	if(var){
		isThroughingCount ++;
	}else{
		isThroughingCount --;
	}
    
	if(isThroughingCount <=0){
		isThroughing = false;
	}else{
		isThroughing = true;
	}
    
}
