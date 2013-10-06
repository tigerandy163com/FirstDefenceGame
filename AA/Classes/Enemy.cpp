//
//  Enemy.cpp
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#include "Enemy.h"
#include "GameMediator.h"
#include "MainLayer.h"

using namespace cocos2d;

Enemy::~Enemy(){
	CC_SAFE_RELEASE_NULL(spOpenSteps);
	CC_SAFE_RELEASE_NULL(spClosedSteps);
	CC_SAFE_RELEASE_NULL(shortestPath);
}

bool Enemy::initWithMem(const char* filename, int hp, float speed,int gift,CCPoint pos){
	bool bRet = false;
	do
	{
        imageName = (char *)malloc(strlen(filename));
        imageName = strcpy(imageName, filename);
		mainLayer = GameMediator::sharedMediator()->getGameLayer();
		int maxTileWidth = mainLayer->getMaxTileWidth();
		int maxTileHeight = mainLayer->getMaxTileHeight();
        
		//sprite =CCSprite::createWithSpriteFrameName(filename); //CCSprite::create(filename);
        //将图片生成纹理，保存到全局的纹理缓存取
        CCTexture2D *heroTexture=CCTextureCache::sharedTextureCache()->addImage(filename);
        //用纹理创建4幅帧动画
        CCSpriteFrame *frame0,*frame1,*frame2,*frame3;
        //第二个参数表示显示区域的x,y,width,height
        frame0=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(36*0,48*3,36,48));
        frame1=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(36*1,48*3,36,48));
        frame2=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(36*2,48*3,36,48));
        frame3=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(36*3,48*3,36,48));
        //CCMutableArray<CCSpriteFrame*> *animFramess=new CCMutableArray<CCSpriteFrame*>(4);
        
        CCArray *animFrames=CCArray::create();
        animFrames->addObject(frame0);
        animFrames->addObject(frame1);
        animFrames->addObject(frame2);
        animFrames->addObject(frame3);
        //根据4幅帧生成ＣＣＡnimation对象
        CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames);
        //创建一个CCSprite用来显示勇士，可以使用Animation中的一帧来作为勇士静止时的画面
        sprite=CCSprite::createWithSpriteFrame(frame0);
        
        addChild(sprite);
        //根据动画模板创建动画
        animation->setDelayPerUnit(0.2f);
        CCAnimate *animate=CCAnimate::create(animation);
        //animate->retain();
        //创建不断重复的动画，并让heroSprite播放
        CCRepeatForever *forever = CCRepeatForever::create(animate);
        forever->setTag(100);
        sprite->runAction(forever);
        
        animFrames->release();

		actionSprite = CCSprite::createWithSpriteFrame(frame0);
		actionSprite->retain();
		this->setHP(hp);
		this->setSpeed(speed);
        this->setGift(gift);
        this->totalHP = hp;
        isAimed = false;
		int x, y;
		x =-20;// pos.x/2;
		y=  pos.y+10 ;
		startPos = ccp(x,y);
        this->setPosition(startPos);
        
        startPos = ccp(15,pos.y+10);
		x = maxTileWidth  ;
        y = maxTileHeight;
		endPos = ccp(x, y);
        
		hasRemoved = false;
        
		spOpenSteps = CCArray::create();
		spOpenSteps->retain();
        
		spClosedSteps = CCArray::create();
		spClosedSteps->retain();
        
		shortestPath = CCArray::create();
		shortestPath->retain();
        WayTilesArray =  CCArray::create();
        WayTilesArray->retain();
		//attack();
        cur = 0;
		times = 0;
		orgSpeed = speed;
        
		pre = NULL;
        
        
		healthBar = CCProgressTimer::create(CCSprite::create("health_bar_green.png"));
        
		healthBar->setType(kCCProgressTimerTypeBar);
		healthBar->setMidpoint(ccp(0, 0));
		healthBar->setBarChangeRate(ccp(1, 0));
		healthBar->setPercentage(100);
		healthBar->setScale(0.2f);
		healthBar->setPosition(ccp(0,sprite->getContentSize().height* 0.5f));
		this->addChild(healthBar,2);
        CCSprite *redBar = CCSprite::create("health_bar_red.png");
        redBar->setPosition(healthBar->getPosition());
        redBar->setScale(0.2);
        this->addChild(redBar,1);
        scheduleOnce(schedule_selector(Enemy::attack), 0.5f);

        
		bRet = true;
	} while (0);
	return bRet;
}
CCAnimation* Enemy::createAnimationByDirection(HeroDirection direction){
    //将图片生成纹理，保存到全局的纹理缓存取
    CCTexture2D *heroTexture=CCTextureCache::sharedTextureCache()->addImage(imageName);
    //用纹理创建4幅帧动画
    CCSpriteFrame *frame0,*frame1,*frame2,*frame3;
    //第二个参数表示显示区域的x,y,width,height
    frame0=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(36*0,48*direction,36,48));
    frame1=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(36*1,48*direction,36,48));
    frame2=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(36*2,48*direction,36,48));
    frame3=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(36*3,48*direction,36,48));
    //CCMutableArray<CCSpriteFrame*> *animFramess=new CCMutableArray<CCSpriteFrame*>(4);
    
    CCArray *animFrames=CCArray::create();
    animFrames->addObject(frame0);
    animFrames->addObject(frame1);
    animFrames->addObject(frame2);
    animFrames->addObject(frame3);
    //根据4幅帧生成ＣＣＡnimation对象
    CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames);
    // animation->retain();
    //根据动画模板创建动画
    animation->setDelayPerUnit(0.2f);
    // animFrames->release();
    CCPoint pos = sprite->getPosition();
//    sprite->removeFromParentAndCleanup(true);
//    sprite=CCSprite::createWithSpriteFrame(frame0);
//    sprite->setPosition(pos);
//    addChild(sprite);
    return animation;
}
void Enemy::IamAimed(bool aimed){
    if (aimed&&!isAimed) {
        aim = CCSprite::create("aim.png");
        
        aim->setScale(0.4);
        aim->setPosition(CCPointZero);
        addChild(aim);
        isAimed = true;
    }

}
void Enemy:: SetDemage(float val,bool isBoom){
    CCString *str = CCString::createWithFormat("-%.f",val);
  //  CCLog(str->getCString());
    float font = 30;
    if (isBoom) {
        font = 60;
    }
   CCLabelTTF* demageLab = CCLabelTTF::create(str->getCString(),  "Marker Felt", font);
    if (isBoom) {
         demageLab->setColor(ccYELLOW);
    }else
    demageLab->setColor(ccRED);
    float x = CCRANDOM_0_1()*40;
    float y = CCRANDOM_0_1()*40;
    demageLab->setPositionX(x);
    demageLab->setPositionY(y);
    this->addChild(demageLab);
   CCActionInterval* scale=CCScaleTo::create(10, 0.5);
//    CCActionInterval* scale1 = CCScaleTo::create(0.25, 0.2);
    CCActionInterval *fade = CCFadeOut::create(0.5);
   // CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(Enemy::clearDemageLab));
 
    //创建不断重复的动画，并让heroSprite播放
    
    demageLab->runAction(CCSpawn::create(scale,fade,NULL));
    CCAnimate * animate = BoomReady();
    if (animate==NULL) {
        return;
    }
    CCCallFunc* callfun = CCCallFunc::create(this,callfunc_selector(Enemy::boomNow));
    actionSprite->runAction(CCSequence::create(animate,callfun));
}
CCAnimate * Enemy::BoomReady(){
    if (hasRemoved) {
        return NULL;
    }
    //将图片生成纹理，保存到全局的纹理缓存取
    CCTexture2D *heroTexture=CCTextureCache::sharedTextureCache()->addImage("003-Attack01.png");
    //用纹理创建4幅帧动画
    CCSpriteFrame *frame0,*frame1,*frame2,*frame3,*frame4;
    //第二个参数表示显示区域的x,y,width,height
    frame0=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(192*0,0,192,192));
    frame1=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(192,0,192,192));
    frame2=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(192*2,0,192,192));
    frame3=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(192*3,0,192,192));
    frame4=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(192*4,0,192,192));
    //CCMutableArray<CCSpriteFrame*> *animFramess=new CCMutableArray<CCSpriteFrame*>(4);
    
    CCArray *animFrames=CCArray::create();
    animFrames->addObject(frame0);
    animFrames->addObject(frame1);
    animFrames->addObject(frame2);
    //animFrames->addObject(frame3);
    //  animFrames->addObject(frame4);
    //根据4幅帧生成ＣＣＡnimation对象
    CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames);
    //创建一个CCSprite用来显示勇士，可以使用Animation中的一帧来作为勇士静止时的画面
    setActionSprite(CCSprite::createWithSpriteFrame(frame0));
    actionSprite->setPosition(CCPointMake(0, 0));
    actionSprite->setScale(0.3);
    addChild(actionSprite);
    //根据动画模板创建动画
    animation->setDelayPerUnit(0.2f);
    CCAnimate *animate=CCAnimate::create(animation);
    return animate;
}
void Enemy::boomNow(){
    if (!hasRemoved)
    actionSprite->removeFromParentAndCleanup(true);
}

void Enemy::changeSpeed(float time){
	times = time * 5;//time / 0.2;
	if(speed < 30)
		return;
	speed = speed * 0.5f;
	
}

void Enemy::timer(float dt){
	if(times <=0 ){
		if(speed != orgSpeed)
			speed = orgSpeed;
		return;
	}
    
	times --;
}

void Enemy::enemyLogic(float dt){
	GameMediator* gm = GameMediator::sharedMediator();
    
	if(mainLayer->isOutOfMap(this->getPosition())){
		unscheduleAllSelectors();
        
		gm->getGameHUDLayer()->updateBaseHp(-10);
		removeSelf();
		return;
	}
    
	if(this->getHP() <= 0){
		
        
		gm->getGameHUDLayer()->updateResources(gift);
        stopAllActions();
	//	unscheduleAllSelectors();
		CCBlink* deadAction = CCBlink::create(0.3f, 3);
		CCCallFunc* deadDone = CCCallFunc::create(this, callfunc_selector(Enemy::removeSelf));
        
		this->runAction(CCSequence::create(deadAction, deadDone, NULL));
        return;
	}

}

CCRect Enemy::getRect(){
	CCRect rect = CCRectMake(this->getPosition().x - sprite->getContentSize().width * 0.5f,
                             this->getPosition().y - sprite->getContentSize().height* 0.5f,
                             sprite->getContentSize().width,
                             sprite->getContentSize().height);
	return rect;
}



void Enemy::attack(){
    float moveTime = 32 / speed;
	CCMoveTo* moveby = CCMoveTo::create(moveTime, startPos);
	CCCallFunc* moveDone = CCCallFunc::create(this, callfunc_selector(Enemy::startLogic));
	this->runAction(CCSequence::create(moveby,moveDone,NULL));
    
}
void Enemy::startLogic(){
    schedule(schedule_selector(Enemy::enemyLogic), 0.5f);
    schedule(schedule_selector(Enemy::timer), 0.2f);
    moveToTarget();
}
void Enemy::moveToTarget( ){
   bool lasttile = false;
    cur++;
    if (cur==WayTilesArray->count()) {
        lasttile = true;
    }
    TileData *toTile;
    CCPoint WalktoPosition;
    
    if (!lasttile) {
   toTile = (TileData *)WayTilesArray->objectAtIndex(cur);

    CCPoint _currentTileCoord = toTile->getPosition();
    if (_currentTileCoord.equals(endPos)) {
     //   this->removeSelf();
        return;
    }
   
    
	//CCPoint startPosition = this->getPosition();
    
   WalktoPosition =  mainLayer->positionForTileCoord(_currentTileCoord);

    }else{
        WalktoPosition = getPosition();
        if (curDir==kRight)
            WalktoPosition.x = mainLayer->gameMap->getContentSize().width + mainLayer->gameMap->getTileSize().width/2;
        else if (curDir==kUp)
            WalktoPosition.y=mainLayer->gameMap->getContentSize().height+ mainLayer->gameMap->getTileSize().height/2;
        else if(curDir == kDown)
            WalktoPosition.y=mainLayer->gameMap->getContentSize().height-mainLayer->gameMap->getTileSize().height/2;
        else if (curDir == kLeft)
            WalktoPosition.x = mainLayer->gameMap->getContentSize().width - mainLayer->gameMap->getTileSize().width/2;
    }
    WalktoPosition.y+=10;
    CCMoveTo* moveAction;
    CCCallFunc* moveCallback;
    float moveTime = 32 / speed;
	moveAction = CCMoveTo::create(moveTime, WalktoPosition);
    moveCallback = CCCallFunc::create(this, callfunc_selector(Enemy::moveToTarget));
    if (!lasttile){


    if (toTile->getDirection()!=KUnKnow&&!hasRemoved) {
        curDir = toTile->getDirection();
        CCAnimation *animation = this->createAnimationByDirection(toTile->getDirection());
        CCAnimate *animate = CCAnimate::create(animation);

        CCRepeatForever* forever = CCRepeatForever::create(animate);
        sprite->stopActionByTag(100);
        forever->setTag(100);
        sprite->runAction(forever);
    }
    }
    if (lasttile) {
       // auto doneCallback = CCCallFunc::create(this, callfunc_selector(Enemy::removeSelf));
        this->runAction(CCSequence::create(moveAction, NULL));
    }else
	this->runAction(CCSequence::create(moveAction, moveCallback, NULL));

}
/***
void Enemy::moveToTarget(){
	CCPoint startPosition = mainLayer->tileCoordinateFromPosition(this->getPosition());
	TileData* startTd = mainLayer->getTileData(startPosition);
	startTd->setParentTile(NULL);
	this->insertInOpenSteps(startTd);
	do
	{
		TileData* _currentTile = (TileData*)spOpenSteps->objectAtIndex(0);
		CCPoint _currentTileCoord = _currentTile->getPosition();
		spClosedSteps->addObject(_currentTile);
		spOpenSteps->removeObjectAtIndex(0);
		if(CCPoint::CCPointEqualToPoint(_currentTileCoord, endPos)){
			constructPathAndStartAnimationFromStep(_currentTile);
			spOpenSteps->removeAllObjects();
			spClosedSteps->removeAllObjects();
			break;
		}
        
		CCArray* tiles = mainLayer->getTilesNextToTile(_currentTileCoord);
		CCObject* temp;
		CCARRAY_FOREACH(tiles, temp){
			CCString* string = (CCString*)temp;
			CCPoint tileCoord = CCPointFromString(string->getCString());
			TileData* _neighbourTile = mainLayer->getTileData(tileCoord);
			if(myArrayGetIndexOfObject(spClosedSteps, _neighbourTile) != CC_INVALID_INDEX){
				continue;
			}
            
			if(_neighbourTile->getIsUsed()&&!_neighbourTile->getisWay()){
				continue;
			}
            
			int moveCost = costToMoveFromTileToAdjacentTile(_currentTile, _neighbourTile);
			int index = myArrayGetIndexOfObject(spOpenSteps, _neighbourTile);
			if(index == CC_INVALID_INDEX){
				_neighbourTile->setParentTile(NULL);
				_neighbourTile->setParentTile(_currentTile);
				_neighbourTile->setGScore(_currentTile->getGScore() + moveCost);
				_neighbourTile->setHScore(computeHScoreFromCoordToCoord(_neighbourTile->getPosition(), endPos));
				insertInOpenSteps(_neighbourTile);
			}else{
				_neighbourTile = (TileData*)spOpenSteps->objectAtIndex(index);
				if(_currentTile->getGScore() + moveCost < _neighbourTile->getGScore()){
					_neighbourTile->setGScore(_currentTile->getGScore() + moveCost);
                    
					_neighbourTile->retain();
					spOpenSteps->removeObjectAtIndex(index);
					this->insertInOpenSteps(_neighbourTile);
					_neighbourTile->release();
				}
			}
            
		}
        
	} while (spOpenSteps->count() > 0);
}
 */
void Enemy::removeSelf(){
	if(hasRemoved)
		return;
    unscheduleAllSelectors();
    this->stopAllActions();
    this->removeFromParentAndCleanup(true);
	hasRemoved = true;
	GameMediator* gm = GameMediator::sharedMediator();
	gm->getTargets()->removeObject(this);
}

FastRedEnemy* FastRedEnemy::create(const char* filename, int hp, float speed,int gift,CCPoint pos){
	FastRedEnemy* fre = new FastRedEnemy;
	if(fre && fre->initWithMem(filename, hp, speed, gift,pos)){
		fre->autorelease();
		return fre;
	}
	CC_SAFE_DELETE(fre);
	return NULL;
}

FastRedEnemy* FastRedEnemy::create(cocos2d::CCPoint pos){
   // CCSprite *sp =CCSprite::createWithSpriteFrameName("Obss9_9-41.png");
 
	return FastRedEnemy::create("hero_fast.png", 100, 64.0f,10,pos);
}

StrongGreenEnemy* StrongGreenEnemy::create(const char* filename, int hp, float speed,int gift,cocos2d::CCPoint pos){
	StrongGreenEnemy* sge = new StrongGreenEnemy;
	if(sge && sge->initWithMem(filename, hp,speed,gift,pos)){
		sge->autorelease();
		return sge;
	}
	CC_SAFE_DELETE(sge);
	return NULL;
}

StrongGreenEnemy* StrongGreenEnemy::create(cocos2d::CCPoint pos){
	return StrongGreenEnemy::create("hero_phy.png", 200, 32.0f,8,pos);
}
