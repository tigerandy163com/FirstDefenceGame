//
//  GameMediator.h
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#ifndef __MyTowerDefense2D__GameMediator__
#define __MyTowerDefense2D__GameMediator__

#include "cocos2d.h"
#include "MainLayer.h"
#include "GameHUD.h"

#include "DataParserBase.h"
#define maxSpeed 3
class GameMediator : public cocos2d::CCObject {
public:
	~GameMediator();
	bool init();
    void clear();
	static GameMediator* sharedMediator();
    int nowSpeed;
    CC_SYNTHESIZE_RETAIN(DataParserBase*, _parser1, Parser1);
    CC_SYNTHESIZE_RETAIN(DataParserBase*, _parser2, Parser2);
    CC_SYNTHESIZE_RETAIN(DataParserBase*, _parser3, Parser3);
    CC_SYNTHESIZE_RETAIN(DataParserBase*, _parser4, Parser4);
    CC_SYNTHESIZE_RETAIN(DataParserBase*, _parser5, Parser5);
    CC_SYNTHESIZE_RETAIN(DataParserBase*, _parser6, Parser6);
	CC_SYNTHESIZE_RETAIN(MainLayer*, _gameLayer, GameLayer);
	CC_SYNTHESIZE_RETAIN(GameHUD*, _gameHUDLayer, GameHUDLayer);
    
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, _targets, Targets);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, _waves, Waves);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, _maps, Maps);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, _towers, Towers);
    int _curMapId;
    CC_SYNTHESIZE_RETAIN(cocos2d::CCString*, _curMapName, CurMapName);
    CC_SYNTHESIZE(bool, _firstLoad, FirstLoad);
    
    void setCurMapID(int curID);
    int getCurMapID();
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, _ProjectTiles, ProjectTiles);
};


#endif /* defined(__MyTowerDefense2D__GameMediator__) */
