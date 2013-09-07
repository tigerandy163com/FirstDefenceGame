//
//  Tower.h
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#ifndef __MyTowerDefense2D__Tower__
#define __MyTowerDefense2D__Tower__

#include "cocos2d.h"
#include "Enemy.h"

class Tower : public cocos2d::CCNode, public cocos2d::CCTouchDelegate {
public:
	virtual ~Tower();
	virtual bool initWithFileAndRange(const char *pszFilename, int range);
    virtual bool initWithSpriteFrame(cocos2d::CCSpriteFrame* frame,int range);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	CC_SYNTHESIZE(int, _range,  Range);
//    CC_SYNTHESIZE(int, _money, Money);
    void setMoney(int val);
    int getMoney();
    CC_SYNTHESIZE(int, _level, Level);
	CC_SYNTHESIZE_RETAIN(Enemy*, _target, Target);
    virtual void towerLogic(float dt);
protected:
    cocos2d::CCSprite* actionSprite;
	cocos2d::CCSprite* sprite;
    cocos2d::CCSprite* rangeSprite;
	cocos2d::CCSprite* sprite1;
	cocos2d::CCSprite* sprite2;
	cocos2d::CCSprite* sprite3;
	cocos2d::CCSprite* sprite4;
    int _money;
    int _damge;
    int _maxDamge;
    float _interval;
    bool moneyEnough;
	virtual Enemy* getClosestTarget();
    virtual void fire(){
        
    }
    virtual void fireReady(){
        
    }
    virtual void fireNow(){
        
    }
    
    virtual  void levelUp();
	bool isShowing;
	void show();
	void unShow();
    
};

class MachineGunTower : public Tower {
public:
	bool initWithFileAndRange(const char *pszFilename, int range);
    bool initWithSpriteFrame(cocos2d::CCSpriteFrame* frame,int range);
	void fire(float dt);
     void towerLogic(float dt);
	static MachineGunTower* create();
	static MachineGunTower* create(const char *pszFilename, int range);
     static MachineGunTower* create(cocos2d::CCSpriteFrame* frame,int range);
    void fireReady();
    void fireNow();
     void levelUp();
};

class FreezeTower : public Tower {
public:
	bool initWithFileAndRange(const char *pszFilename, int range);
    bool initWithSpriteFrame(cocos2d::CCSpriteFrame* frame,int range);
	void fire(float dt);
    
	static FreezeTower* create();
	static FreezeTower* create(const char *pszFilename, int range);
     static FreezeTower* create(cocos2d::CCSpriteFrame* frame,int range);
     void levelUp();
};

class CannonTower : public Tower {
public:
	bool initWithFileAndRange(const char *pszFilename, int range);
    bool initWithSpriteFrame(cocos2d::CCSpriteFrame* frame,int range);
	void fire(float dt);

    
	static CannonTower* create();
	static CannonTower* create(const char *pszFilename, int range);
    static CannonTower* create(cocos2d::CCSpriteFrame* frame,int range);
    void levelUp();
};
class MutilTower:public Tower{
public:
	bool initWithFileAndRange(const char *pszFilename, int range);
    bool initWithSpriteFrame(cocos2d::CCSpriteFrame* frame,int range);
	void fire(float dt);
    
    CC_SYNTHESIZE(int ,fireMount, fireMount);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray*, enemys, enemys);
    
    void getMutilFireEnemys();
    void towerLogic1(float dt);
    static MutilTower* create();
	static MutilTower* create(const char *pszFilename, int range);
    static MutilTower* create(cocos2d::CCSpriteFrame* frame,int range);
     void levelUp();
};
#endif /* defined(__MyTowerDefense2D__Tower__) */
