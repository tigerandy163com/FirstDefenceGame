//
//  MainLayer.h
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#ifndef __MyTowerDefense2D__MainLayer__
#define __MyTowerDefense2D__MainLayer__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
#include "Enemy.h"
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class TileData;
class GameHUD;
class Wave;
class Tower;

class MainLayer : public cocos2d::CCLayer
{
public:
	~MainLayer();
//   virtual  void onEnter();
    virtual void onExit();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    
	cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint position);
	cocos2d::CCPoint positionForTileCoord(cocos2d::CCPoint position);
    
	bool canBuildOnTilePosition(cocos2d::CCPoint pos);
    
	TileData* getTileData(cocos2d::CCPoint tileCoord);
    TileData* getTileDataForPositon(cocos2d::CCPoint tileCoord);
	void addTower(cocos2d::CCPoint pos, int towerTag);
    
	cocos2d::CCDictionary* getTilesNextToTile(cocos2d::CCPoint tileCoord);
    
	bool isOutOfMap(cocos2d::CCPoint pos);
    
	void removeTower(Tower* tower);
 
	void strikeLight(float dt);
    HeroDirection directionFor(cocos2d::CCString *cstr);
    cocos2d:: CCPoint tileCoordinateFromPosition(cocos2d:: CCPoint pos);
    int tileIDFromPosition(cocos2d:: CCPoint pos);
    cocos2d:: CCPoint objectPosition(cocos2d::CCTMXObjectGroup *group,const char *object);
    CREATE_FUNC(MainLayer);
    
	CC_SYNTHESIZE(cocos2d::CCArray*, tileDataArray, TileDataArray);
    
	CC_SYNTHESIZE(int, maxTileWidth, MaxTileWidth);
	CC_SYNTHESIZE(int, maxTileHeight, MaxTileHeight);
    cocos2d::CCTMXObjectGroup *_objects;
    cocos2d:: CCTMXTiledMap *gameMap;
     cocos2d::CCTMXLayer* _bg1layer;
    cocos2d::CCSize mapsize;
    cocos2d::CCRect mapRect;
    cocos2d::CCSize tileSize;
    cocos2d::CCArray* totolWays;
    cocos2d::CCArray* wayTilesArr;
    cocos2d::CCArray* dirChangeArr;
    
private:

    void getWayTiles();
    bool isexit(TileData *tile);
    
	long millisecondNow(){
        
		cocos2d::cc_timeval now;
		cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);
		return (now.tv_sec * 1000 + now.tv_usec / 1000);
	}
    
	cocos2d::CCSprite* background;
	GameHUD* gameHUD;
    
	cocos2d::CCParticleSystem*    m_emitter;
    
	//int maxTileWidth;
	//int maxTileHeight;
    
	float maxWidth;
	float maxHeight;
    
	int currentLevel;
    
	void createTileMap();
    
	cocos2d::CCPoint boundLayerPos(cocos2d::CCPoint newPos);
    
	Wave* getCurrentWave();
	Wave* getNextWave();
    
	void addWaves();
	void addTarget();
    
	void gameLogic(float dt);
    
    
};


#endif /* defined(__MyTowerDefense2D__MainLayer__) */
