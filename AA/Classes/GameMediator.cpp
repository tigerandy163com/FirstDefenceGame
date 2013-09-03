//
//  GameMediator.cpp
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#include "GameMediator.h"
#include "Enemy.h"
#include "Tower.h"
#include "ProjectTile.h"
using namespace cocos2d;

static GameMediator* _sharedContext;

GameMediator* GameMediator::sharedMediator(){
	if (_sharedContext==NULL) {
        _sharedContext = new GameMediator();
        _sharedContext->init();
    }
    return _sharedContext;
}

GameMediator::~GameMediator(){
	CC_SAFE_RELEASE_NULL(_gameLayer);
	CC_SAFE_RELEASE_NULL(_targets);
	CC_SAFE_RELEASE_NULL(_maps);
	CC_SAFE_RELEASE_NULL(_waves);
	CC_SAFE_RELEASE_NULL(_towers);
	CC_SAFE_RELEASE_NULL(_ProjectTiles);
}

bool GameMediator::init(){
	bool bRet = false;
	do
	{
        setCurMapID(0);
        nowSpeed = 1;
		_gameLayer = NULL;
		_gameHUDLayer = NULL;
        
		_targets = CCArray::create();
		_targets->retain();
        
		_waves = CCArray::create();
		_waves->retain();
        
		_towers = CCArray::create();
		_towers->retain();
        _maps = CCArray::create();
        _maps->retain();
        
		_ProjectTiles = CCArray::create();
		_ProjectTiles->retain();
        
		bRet = true;
	} while (0);
	return bRet;
}
void GameMediator::setCurMapID(int curID){
    _curMapId = curID;
    setCurMapName(CCString::createWithFormat("TileMap%d.tmx",curID));
}
int GameMediator::getCurMapID(){
    return _curMapId;
}
void GameMediator:: clear(){
    _gameLayer->stopAllActions();
    _gameLayer->unscheduleAllSelectors();
    CCObject *obj1;
    CCARRAY_FOREACH(_targets, obj1){
        Enemy *enemy = (Enemy*)obj1;
        enemy->stopAllActions();
        enemy->unscheduleAllSelectors();
    }
    CCObject *obj2;
    CCARRAY_FOREACH(_towers, obj2){
        Tower *tower = (Tower*)obj2;
        tower->stopAllActions();
        tower->unscheduleAllSelectors();
    }
    CCObject *obj3;
    CCARRAY_FOREACH(_ProjectTiles, obj3){
        ProjectTile *tile = (ProjectTile *)obj3;
        tile->stopAllActions();
        tile->unscheduleAllSelectors();
    }
//    _gameLayer = NULL;
//    _gameHUDLayer = NULL;
    _targets->removeAllObjects();
    _waves->removeAllObjects();
    _towers->removeAllObjects();
    _ProjectTiles->removeAllObjects();
}