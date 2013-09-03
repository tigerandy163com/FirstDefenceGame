//
//  Tower.cpp
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#include "Tower.h"
#include "GameMediator.h"
#include "ProjectTile.h"

using namespace cocos2d;

Tower::~Tower(){
	
}

bool Tower::initWithFileAndRange(const char *pszFilename, int range){
	bool bRet = false;
	do
	{
		sprite = CCSprite::create(pszFilename);
		this->addChild(sprite, 10);
        
		sprite1 = CCSprite::create(pszFilename);
		this->addChild(sprite1);
		sprite1->setVisible(false);
		sprite1->setColor(ccBLUE);
        
		sprite2 = CCSprite::create(pszFilename);
		this->addChild(sprite2);
		sprite2->setVisible(false);
		sprite2->setColor(ccGREEN);
        
		sprite3 = CCSprite::create(pszFilename);
		this->addChild(sprite3);
		sprite3->setVisible(false);
		sprite3->setColor(ccBLACK);
        
		sprite4 = CCSprite::create(pszFilename);
		this->addChild(sprite4);
		sprite4->setVisible(false);
		sprite4->setColor(ccRED);
        
		this->setRange(range);
        
        rangeSprite = CCSprite::create("Range.png");
        float scale = range/100.0;
        rangeSprite->setScale(scale);
        rangeSprite->setVisible(false);
        rangeSprite->setPosition(sprite->getPosition());
        this->addChild(rangeSprite, -1);
 
        
		_target = NULL;
        
		isShowing =false;
        
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
        
	
        
		bRet = true;
	} while (0);
	return bRet;
}

Enemy* Tower::getClosestTarget(){
	Enemy* closestEnemy = NULL;
	double maxDistant = 99999;
    
	GameMediator* m = GameMediator::sharedMediator();
	CCObject* temp;
	CCARRAY_FOREACH(m->getTargets(), temp){
		Enemy* enemy = (Enemy*)temp;
		if(enemy->getHP() <= 0){
			continue;
		}
		double curDistance = ccpDistance(this->getPosition(), enemy->getPosition());
		if(curDistance < maxDistant){
			closestEnemy = enemy;
			maxDistant = curDistance;
		}
	}
    
	if(maxDistant < this->getRange()){
		return closestEnemy;
	}
    
	return NULL;
}

void Tower::towerLogic(float dt){
	if(this->getTarget() == NULL ||!GameMediator::sharedMediator()->getTargets()->containsObject(this->getTarget()))
    {
		this->setTarget(this->getClosestTarget());
	}
    else{
  
		double curDistance = ccpDistance(this->getPosition(), this->getTarget()->getPosition());
		if(this->getTarget()->getHP() <= 0 || curDistance > this->getRange()){
			this->setTarget(this->getClosestTarget());
		
        }
	}

	if(this->getTarget() != NULL){
		CCPoint shootVector = ccpSub(this->getTarget()->getPosition(), this->getPosition());
		float shootAngle = ccpToAngle(shootVector);
		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);
        
		float rotateSpeed = (float)(0.25 / M_PI);
		float rotateDuration = fabs(shootAngle * rotateSpeed);
		this->runAction(CCRotateTo::create(rotateDuration, cocosAngle));
	}
}

void Tower::show(){
    CCActionInterval *fade = CCFadeIn::create(0.5f);
	sprite1->runAction(CCMoveBy::create(0.5f, ccp(- sprite->getContentSize().width -10, 0)));
	sprite1->setVisible(true);
    
	sprite2->runAction(CCMoveBy::create(0.5f, ccp(0, sprite->getContentSize().height + 10)));
	sprite2->setVisible(true);
    
	sprite3->runAction(CCMoveBy::create(0.5f, ccp(sprite->getContentSize().width +10,0)));
	sprite3->setVisible(true);
    
	sprite4->runAction(CCMoveBy::create(0.5f, ccp(0, - sprite->getContentSize().height - 10)));
	sprite4->setVisible(true);
    
    rangeSprite->setVisible(true);
    
    rangeSprite->runAction(CCSequence::create(fade, CCShow::create(),NULL));
}

void Tower::unShow(){
    CCActionInterval *fade = CCFadeOut::create(0.5f);
	sprite1->runAction(CCSequence::create(CCMoveTo::create(0.5f, sprite->getPosition()), CCHide::create(), NULL));
    
	sprite2->runAction(CCSequence::create(CCMoveTo::create(0.5f, sprite->getPosition()), CCHide::create(), NULL));
    
	sprite3->runAction(CCSequence::create(CCMoveTo::create(0.5f, sprite->getPosition()), CCHide::create(), NULL));
    
	sprite4->runAction(CCSequence::create(CCMoveTo::create(0.5f, sprite->getPosition()), CCHide::create(), NULL));
	
    //rangeSprite->setVisible(false);
    
    rangeSprite->runAction(CCSequence::create(fade, CCHide::create(), NULL));
}

bool Tower::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	CCPoint touchLocation = this->convertTouchToNodeSpace(pTouch);
	if(sprite->boundingBox().containsPoint(touchLocation)){
		if(isShowing == false){
			isShowing = true;
			show();
		}else{
			isShowing = false;
			unShow();
		}
		return true;
	}
	if(isShowing && sprite1->boundingBox().containsPoint(touchLocation)){
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		GameMediator::sharedMediator()->getGameLayer()->removeTower(this);
		return true;
	}
	if(isShowing && sprite2->boundingBox().containsPoint(touchLocation)){
		sprite2->runAction(CCBlink::create(1.0f, 5));
		return true;
	}
	if(isShowing && sprite3->boundingBox().containsPoint(touchLocation)){
		sprite3->runAction(CCSequence::create(CCFadeOut::create(0.5), CCFadeIn::create(0.5f), NULL));
		return true;
	}
	if(isShowing && sprite4->boundingBox().containsPoint(touchLocation)){
		sprite4->runAction(CCRotateBy::create(1.0f, 360.0f));
		return true;
	}
    
	return false;
}

MachineGunTower* MachineGunTower::create(const char *pszFilename, int range){
	MachineGunTower* t = new MachineGunTower;
	if(t && t->initWithFileAndRange(pszFilename, range)){
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return NULL;
}

MachineGunTower* MachineGunTower::create(){
	return MachineGunTower::create("MachineGunTurret.png", 100);
}

bool MachineGunTower::initWithFileAndRange(const char *pszFilename, int range){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Tower::initWithFileAndRange(pszFilename, range));
        
		schedule(schedule_selector(MachineGunTower::fire), 1.0f);
        this->schedule(schedule_selector(Tower::towerLogic), 0.2f);
		bRet = true;
	} while (0);
	return bRet;
}
void MachineGunTower::fireNow(){
    actionSprite->removeFromParentAndCleanup(true);
    GameMediator* m = GameMediator::sharedMediator();
    if (!m->getTargets()->containsObject(this->getTarget())) {
        return;
    }
    
    //
    CCPoint shootVector = ccpSub(this->getTarget()->getPosition(), this->getPosition());
    CCPoint normalizedShootVector = ccpNormalize(shootVector);
    CCPoint overshotVector = ccpMult(normalizedShootVector, this->getRange());
    CCPoint offscreenPoint = ccpAdd(this->getPosition(), overshotVector);
    
    MachineProjectTile* ProjectTile = MachineProjectTile::create(offscreenPoint);
    ProjectTile->setPosition(this->getPosition());
    ProjectTile->setRotation(this->getRotation());
    
    m->getGameLayer()->addChild(ProjectTile);
}
void MachineGunTower::fireReady(){
    //将图片生成纹理，保存到全局的纹理缓存取
    CCTexture2D *heroTexture=CCTextureCache::sharedTextureCache()->addImage("attac.png");
    //用纹理创建4幅帧动画
    CCSpriteFrame *frame0,*frame1,*frame2,*frame3,*frame4;
    //第二个参数表示显示区域的x,y,width,height
    frame0=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(60*0,0,60,66));
    frame1=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(60,0,60,66));
    frame2=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(120,0,65,66));
    frame3=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(200,0,60,66));
    frame4=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(260,0,40,66));
    //CCMutableArray<CCSpriteFrame*> *animFramess=new CCMutableArray<CCSpriteFrame*>(4);

    CCArray *animFrames=CCArray::create();
    animFrames->addObject(frame0);
    animFrames->addObject(frame1);
    animFrames->addObject(frame2);
    animFrames->addObject(frame3);
    //  animFrames->addObject(frame4);
    //根据4幅帧生成ＣＣＡnimation对象
    CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames);
    //创建一个CCSprite用来显示勇士，可以使用Animation中的一帧来作为勇士静止时的画面
    actionSprite=CCSprite::createWithSpriteFrame(frame0);
    actionSprite->setPosition(CCPointMake(30, 0));
   
    addChild(actionSprite);
    //根据动画模板创建动画
    animation->setDelayPerUnit(0.2f);
    CCAnimate *animate=CCAnimate::create(animation);
    
    auto callfun = CCCallFunc::create(this,callfunc_selector(MachineGunTower::fireNow));
    //创建不断重复的动画，并让heroSprite播放
    actionSprite->runAction(CCSequence::create(animate,callfun,NULL));
    
    animFrames->release();
    
}
void MachineGunTower::fire(float dt){
	if(this->getTarget() != NULL){
        fireReady();
//		GameMediator* m = GameMediator::sharedMediator();
//        
//		CCPoint shootVector = ccpSub(this->getTarget()->getPosition(), this->getPosition());
//		CCPoint normalizedShootVector = ccpNormalize(shootVector);
//		CCPoint overshotVector = ccpMult(normalizedShootVector, this->getRange());
//		CCPoint offscreenPoint = ccpAdd(this->getPosition(), overshotVector);
//        
//		MachineProjectTile* ProjectTile = MachineProjectTile::create(offscreenPoint);
//		ProjectTile->setPosition(this->getPosition());
//		m->getGameLayer()->addChild(ProjectTile);
	}
}

FreezeTower* FreezeTower::create(const char *pszFilename, int range){
	FreezeTower* t = new FreezeTower;
	if(t && t->initWithFileAndRange(pszFilename, range)){
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return NULL;
}

FreezeTower* FreezeTower::create(){
	return FreezeTower::create("FreezeTurret.png", 150);
}

bool FreezeTower::initWithFileAndRange(const char *pszFilename, int range){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Tower::initWithFileAndRange(pszFilename, range));
        
		schedule(schedule_selector(FreezeTower::fire), 1.0f);
         this->schedule(schedule_selector(Tower::towerLogic), 0.2f);
		bRet = true;
	} while (0);
	return bRet;
}

void FreezeTower::fire(float dt){
	if(this->getTarget() != NULL){
		GameMediator* m = GameMediator::sharedMediator();
        
		CCPoint shootVector = ccpSub(this->getTarget()->getPosition(), this->getPosition());
		CCPoint normalizedShootVector = ccpNormalize(shootVector);
		CCPoint overshotVector = ccpMult(normalizedShootVector, this->getRange());
		CCPoint offscreenPoint = ccpAdd(this->getPosition(), overshotVector);
        
		IceProjectTile* ProjectTile = IceProjectTile::create(offscreenPoint);
		ProjectTile->setPosition(this->getPosition());
		ProjectTile->setRotation(this->getRotation());
		m->getGameLayer()->addChild(ProjectTile);
	}
}

CannonTower* CannonTower::create(const char *pszFilename, int range){
	CannonTower* t = new CannonTower;
	if(t && t->initWithFileAndRange(pszFilename, range)){
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return NULL;
}

CannonTower* CannonTower::create(){
	return CannonTower::create("CannonTurret.png", 200);
}

bool CannonTower::initWithFileAndRange(const char *pszFilename, int range){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Tower::initWithFileAndRange(pszFilename, range));
        
		this->setRange(400);
        
		schedule(schedule_selector(CannonTower::fire), 2.0f);
         this->schedule(schedule_selector(Tower::towerLogic), 0.1f);
		bRet = true;
	} while (0);
	return bRet;
}

void CannonTower::fire(float dt){
	if(this->getTarget() != NULL){
        
		GameMediator* m = GameMediator::sharedMediator();
        
		CannonProjectTile* ProjectTile = CannonProjectTile::create(this->getTarget());
        CCLOG("target pos is:%f,%f",this->getTarget()->getPosition().x,this->getTarget()->getPosition().y);
		ProjectTile->setPosition(this->getPosition());
		ProjectTile->setRotation(this->getRotation());
		m->getGameLayer()->addChild(ProjectTile,1);
	}
}

Enemy* CannonTower::getClosestTarget(){
	//Enemy* nearestEnemy = NULL;
    
	GameMediator* m = GameMediator::sharedMediator();
	CCObject* temp;
    if (m->getTargets()->count()==0) {
        return NULL;
    }
    Enemy *first = (Enemy*)m->getTargets()->objectAtIndex(0);
    float dis = ccpDistance(this->getPosition(),first->getPosition());
	CCARRAY_FOREACH(m->getTargets(), temp){
		Enemy* enemy = (Enemy*)temp;
		if(enemy->getHP() <= 0){
			continue;
		}
		float curDistance = ccpDistance(this->getPosition(), enemy->getPosition());
		if(curDistance < this->getRange()){
			if (curDistance<=dis) {
                dis = curDistance;
            }
			//break;
		}
	}
    CCARRAY_FOREACH(m->getTargets(), temp){
        
        Enemy* enemy = (Enemy*)temp;
		if(enemy->getHP() <= 0){
			continue;
		}
		float curDistance = ccpDistance(this->getPosition(), enemy->getPosition());
		if(curDistance < this->getRange()){
			if (curDistance==dis)
            {
                nearestEnemy = enemy;
                break;
            }

		}

    }

	return nearestEnemy;
}

MutilTower* MutilTower::create(){
    return  MutilTower::create("CannonTurret.png", 200);
}
MutilTower* MutilTower::create(const char *pszFilename, int range){
    MutilTower *t = new MutilTower;
    if (t&&t->initWithFileAndRange(pszFilename, range)) {
        t->autorelease();
        return t;
    }
    CC_SAFE_DELETE(t);
    return NULL;
    
}
bool MutilTower::initWithFileAndRange(const char *pszFilename, int range){
    bool bRet = false;
    do {
        CC_BREAK_IF(!Tower::initWithFileAndRange(pszFilename, range));
        this->setRange(200);
        enemys = CCArray::create();
        enemys->retain();
		schedule(schedule_selector(MutilTower::fire), 2.0f);
        this->schedule(schedule_selector(MutilTower::towerLogic1), 0.2f);
		bRet = true;
    } while (0);
    return bRet;
}
void MutilTower::getMutilFireEnemys(){
    
    GameMediator *mediator = GameMediator::sharedMediator();
    CCArray *arr = mediator->getTargets();
    if (arr->count()==0) {
        return;
    }else
    {
        int count =arr->count();
        if (count<=3) {
            enemys->removeAllObjects();
            enemys->addObjectsFromArray(arr);
            return;
   
        }else{
            
            CCObject* temp;
            int num= 0;
            enemys->removeAllObjects();
            CCARRAY_FOREACH(mediator->getTargets(), temp){
                Enemy* enemy = (Enemy*)temp;
                float distance = ccpDistance(enemy->getPosition(), this->getPosition());
        
                if (distance<=this->getRange()&&enemy->getHP()>0) {
                enemys->addObject(enemy);
                num++;
                if (num==3) {
                    break;
                }
                }
            }
            return;
        }
    }
}
void MutilTower::fire(float dt){
	if(this->getenemys() != NULL){
		GameMediator* m = GameMediator::sharedMediator();
        CCObject *obj;
        CCARRAY_FOREACH(this->getenemys(), obj){
            Enemy* target = (Enemy*)obj;
            CannonProjectTile* ProjectTile = CannonProjectTile::create(target);
            ProjectTile->setSpeed(300);
            ProjectTile->setDamage(50);
            ProjectTile->setMaxDamge(80);
            ProjectTile->setProbability(0.25);
            ProjectTile->setPosition(this->getPosition());
            ProjectTile->setRotation(this->getRotation());
            m->getGameLayer()->addChild(ProjectTile);
        }

	}
}
void MutilTower::towerLogic1(float dt){
        CCArray *enemyArr = this->getenemys();
    if (enemyArr->count()==0) {
        this->getMutilFireEnemys();
    }
        CCObject *obj1=NULL;
        bool shouldChange = false;
        CCARRAY_FOREACH(enemyArr, obj1){
            Enemy* enemy = (Enemy*)obj1;
            double curDis = ccpDistance(this->getPosition(), enemy->getPosition());
            if (enemy->getHP()<=0||curDis>this->getRange()) {
                shouldChange = true;
                break;
            }
        }
        if (shouldChange)
        {
            this->getMutilFireEnemys();
    
        }

    
    enemyArr = this->getenemys();
    
	if(enemyArr->count()!=0){
        {
        Enemy* enemy =(Enemy *) enemyArr->lastObject();
		CCPoint shootVector = ccpSub(enemy->getPosition(), this->getPosition());
		float shootAngle = ccpToAngle(shootVector);
		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);
        
		float rotateSpeed = (float)(0.25 / M_PI);
		float rotateDuration = fabs(shootAngle * rotateSpeed);
		this->runAction(CCRotateTo::create(rotateDuration, cocosAngle));
        }
	}
}