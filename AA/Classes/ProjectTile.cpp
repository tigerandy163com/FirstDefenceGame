//
//  ProjectTile.cpp
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#include "ProjectTile.h"
#include "GameMediator.h"
#include "Enemy.h"
#include <iomanip> 

using namespace cocos2d;

bool ProjectTile::initWithFile(const char* filename){
    
	mySprite = CCSprite::create(filename);
	this->addChild(mySprite);
    
	speed = 960.0f;
	targetPos = CCPointZero;
	damage = 3;
    maxDamage = 10;
    probability = 0.6;
    isBoom = false;
	gm = GameMediator::sharedMediator();
    
	hasRemoved = false;
    
	scheduleUpdate();
    
	return true;
}

void ProjectTile::removeSelf(){
	if(hasRemoved)
		return;
    
	hasRemoved = true;
    //_streak->removeFromParentAndCleanup(true);
	unscheduleAllSelectors();
	this->stopAllActions();
	this->removeFromParentAndCleanup(true);
}
int ProjectTile::getDamage(void){
    if (CCRANDOM_0_1()<=probability ) {
        this->setIsBoom(true);
    }else
        this->setIsBoom(false);
    int temp =CCRANDOM_0_1()*maxDamage;
    if (isBoom) {
        temp =damage +( maxDamage-damage)*(2.5+CCRANDOM_0_1()*3);
    }
    if(temp<=damage)
        temp =damage;
    return temp;
}
void ProjectTile::setDamage(int val){
    damage = val;
 
}
void ProjectTile::setMaxDamge(int val){
    maxDamage = val;
}
int ProjectTile::getMaxDamge(){
    return maxDamage;
}
CCRect ProjectTile::getRect(){
	CCRect rect = CCRectMake(this->getPosition().x - mySprite->getContentSize().width * 0.5f,
                             this->getPosition().y - mySprite->getContentSize().height* 0.5f,
                             mySprite->getContentSize().width,
                             mySprite->getContentSize().height);
	return rect;
}

MachineProjectTile* MachineProjectTile::create(cocos2d:: CCPoint pos){
	MachineProjectTile* m = new MachineProjectTile;
	if(m && m->initWithTargetPos(pos)){
		m->autorelease();
		return m;
	}
	CC_SAFE_DELETE(m);
	return NULL;
}

bool MachineProjectTile::initWithTargetPos(cocos2d::CCPoint pos){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!initWithFile("buttlet_new.png"));
        setSpeed(500);
		this->setTargetPos(pos);
        
		moveToTargetPos();
        _streak = CCMotionStreak::create(0.2, 15, 15, ccBLUE, "buttlet_new.png");
        _streak->setFastMode(true);
        MainLayer* gm = GameMediator::sharedMediator()->getGameLayer();
        gm-> addChild(_streak);
		bRet = true;
	} while (0);
	return bRet;
}

void MachineProjectTile::update(float dt){
	//GameMediator* gm = GameMediator::sharedMediator();
    CCObject* temp;
     _streak->setPosition(this->getPosition());
	CCARRAY_FOREACH(gm->getTargets(), temp){
		Enemy* target = (Enemy*)temp;
        
		if(this->getRect().intersectsRect(target->getRect()) && target->getHP() > 0){
			target->setHP(target->getHP() - this->getDamage());
            float f= (float)(target->getHP())/target->totalHP;
            
            target->healthBar->setPercentage(f*100);
            target->SetDemage(this->getDamage(),this->getIsBoom());
		  removeSelf();
			break;
		}
	}
  
}

void MachineProjectTile::moveToTargetPos(){
	float distance = ccpDistance(this->getPosition(), this->getTargetPos());
	float moveDur = distance / speed;
	auto moveTo = CCMoveTo::create(moveDur, this->getTargetPos());
	auto moveDone = CCCallFunc::create(this, callfunc_selector(MachineProjectTile::removeSelf));
	this->runAction(CCSequence::create(moveTo, moveDone, NULL));
}

IceProjectTile* IceProjectTile::create(cocos2d:: CCPoint pos){
	IceProjectTile* m = new IceProjectTile;
	if(m && m->initWithTargetPos(pos)){
		m->autorelease();
		return m;
	}
	CC_SAFE_DELETE(m);
	return NULL;
}

bool IceProjectTile::initWithTargetPos(cocos2d::CCPoint pos){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!initWithFile("buttlet_new.png"));
        
		this->setTargetPos(pos);
        
		moveToTargetPos();
        
		bRet = true;
	} while (0);
	return bRet;
}

void IceProjectTile::update(float dt){
	//GameMediator* gm = GameMediator::sharedMediator();
  
    
	CCObject* temp;
    bool needRemove = false;
	CCARRAY_FOREACH(gm->getTargets(), temp){
		Enemy* target = (Enemy*)temp;
        
		if(this->getRect().intersectsRect(target->getRect())){
		//	target->changeSpeed();
            needRemove = true;
            break;
		}
	}
    CCARRAY_FOREACH(gm->getTargets(), temp){
		Enemy* target = (Enemy*)temp;
        float dis =  ccpDistance(this->getPosition(), target->getPosition());
		if(dis<=getRange() ){
            target->changeSpeed();
		}
	}
    if (needRemove) {
        removeSelf();

    }
}

void IceProjectTile::moveToTargetPos(){
	float distance = ccpDistance(this->getPosition(), this->getTargetPos());
	float moveDur = distance / speed;
	auto moveTo = CCMoveTo::create(moveDur, this->getTargetPos());
	auto moveDone = CCCallFunc::create(this, callfunc_selector(IceProjectTile::removeSelf));
	this->runAction(CCSequence::create(moveTo, moveDone, NULL));
}

CannonProjectTile* CannonProjectTile::create(Enemy* enemy){
	CannonProjectTile* cp = new CannonProjectTile;
	if(cp && cp->initWithTarget(enemy)){
		cp->autorelease();
		return cp;
	}
	CC_SAFE_DELETE(cp);
	return NULL;
}

bool CannonProjectTile::initWithTarget(Enemy* enemy){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!initWithFile("rocket.png"));
        
		myEnemy = enemy;
        enemy->IamAimed(true);
		this->setDamage(10);
        this->setMaxDamge(30);
		this->setSpeed(120);
        
		angularVelocity = 5.0f;
        _streak = CCMotionStreak::create(0.4, 5, 5, ccYELLOW, "rocket.png");
        _streak->setFastMode(true);
        MainLayer* gm = GameMediator::sharedMediator()->getGameLayer();
        gm-> addChild(_streak);
		bRet = true;
	} while (0);
	return bRet;
}

void CannonProjectTile::update(float dt){
	//GameMediator* gm = GameMediator::sharedMediator();
    if (!gm->getTargets()->containsObject(myEnemy)) {
       removeSelf();
       return;
    }
	CCPoint targetPos = myEnemy->getPosition();
	CCPoint myPos = this->getPosition();
    
	if(gm->getGameLayer()->isOutOfMap(myPos) || myEnemy->getHP() <=0){
		removeSelf();
	}
     
	if(this->getRect().intersectsRect(myEnemy->getRect())&& myEnemy->getHP() > 0){
		myEnemy->setHP(myEnemy->getHP() - this->getDamage());
        
		float f= (float)(myEnemy->getHP())/myEnemy->totalHP;
        
        myEnemy->healthBar->setPercentage(f*100);
         myEnemy->SetDemage(this->getDamage(),this->getIsBoom());
		removeSelf();
	}

    
	float radian = atan2f(targetPos.y - myPos.y, targetPos.x - myPos.x);
	float angle = -CC_RADIANS_TO_DEGREES(radian);
	angle = to360Angle(angle);
    
	float myAngle = to360Angle(this->getRotation());
	float tempAngle;
	if(myAngle < angle){
		tempAngle = angularVelocity;
	}else if(myAngle >angle){
		tempAngle = -angularVelocity;
	}else{
		tempAngle = 0;
	}
    
	if(360 - (angle - myAngle) < (angle - myAngle)){
		tempAngle *= -1;
	}
    
	this->setRotation(this->getRotation() + tempAngle);
	float myRadian = CC_DEGREES_TO_RADIANS(this->getRotation());
    
	float x = cosf(myRadian) * this->getSpeed() * dt;
	float y = -sinf(myRadian) * this->getSpeed() * dt;
    
	this->setPosition(ccp(myPos.x + x, myPos.y + y));
   
    _streak->setPosition(ccp(myPos.x, myPos.y));
   
}

