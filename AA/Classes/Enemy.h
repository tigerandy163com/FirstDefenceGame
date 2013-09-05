//
//  Enemy.h
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#ifndef __MyTowerDefense2D__Enemy__
#define __MyTowerDefense2D__Enemy__

#include "cocos2d.h"
#include "TileData.h"
class MainLayer;


class Enemy : public cocos2d::CCNode {
public:
	~Enemy();
	bool initWithMem(const char* filename, int hp, float speed,cocos2d::CCPoint pos);
    
	void attack();
    void SetDemage(float val,bool isBoom);
    void clearDemageLab();
    void startLogic();
	virtual cocos2d::CCRect getRect();
	virtual void changeSpeed(float time = 1.0f);
    int totalHP;
    HeroDirection curDir;
    char *imageName;
	CC_SYNTHESIZE(int, hp, HP);
	CC_SYNTHESIZE(float, speed, Speed);
	CC_SYNTHESIZE(cocos2d::CCPoint, startPos, StartPos);
	CC_SYNTHESIZE(cocos2d::CCPoint, endPos, EndPos);
    CC_SYNTHESIZE(bool, isAimed, IsAimed);
    cocos2d::CCArray* WayTilesArray;
    cocos2d::CCProgressTimer* healthBar;
    void IamAimed(bool aimed);
    cocos2d::CCSprite *aim;
    CC_SYNTHESIZE(bool, hasRemoved, HasRemoved);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, actionSprite, ActionSprite);
    cocos2d::CCAnimate *animate;
protected:
	cocos2d::CCSprite* sprite;
	MainLayer* mainLayer;
    int cur;
	float orgSpeed;
	float times;
    //根据方向创建动画
    cocos2d::CCAnimation *createAnimationByDirection(HeroDirection direction);
	cocos2d::CCAnimate* BoomReady();
    void boomNow();
    
	TileData* pre;
    
	void timer(float dt);
    
	void moveToTarget( );
	void insertInOpenSteps(TileData* td);
	int costToMoveFromTileToAdjacentTile(TileData* fromTile, TileData* toTile);
	int computeHScoreFromCoordToCoord(cocos2d::CCPoint fromCoord, cocos2d::CCPoint toCoord);
	void constructPathAndStartAnimationFromStep(TileData* tile);
	void popStepAndAnimate();
    
	void removeSelf();
	void enemyLogic(float dt);
    
    void StartAnimationFromStep(TileData *tile);
	cocos2d::CCArray* spOpenSteps;
	cocos2d::CCArray* spClosedSteps;
	cocos2d::CCArray* shortestPath;
    
	inline unsigned int myArrayGetIndexOfObject(cocos2d::CCArray* arr, TileData* object){
		for ( unsigned int i = 0; i < arr->count(); i++)
		{
			TileData* temp = (TileData*)arr->objectAtIndex(i);
			if (temp->getPosition().equals(object->getPosition()))
			{
				return i;
			}
		}
        
		return CC_INVALID_INDEX;
	}
    
};

class FastRedEnemy : public Enemy {
public:
	static FastRedEnemy* create(cocos2d::CCPoint);
	static FastRedEnemy* create(const char* filename, int hp, float speed,cocos2d::CCPoint pos);
};

class StrongGreenEnemy : public Enemy {
public:
	static StrongGreenEnemy* create(cocos2d::CCPoint);
	static StrongGreenEnemy* create(const char* filename, int hp, float speed,cocos2d::CCPoint pos);

};

#endif /* defined(__MyTowerDefense2D__Enemy__) */
