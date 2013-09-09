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
#include "data.h"
using namespace cocos2d;

Tower::~Tower(){
	
}

bool Tower::initWithFileAndRange(const char *pszFilename, int range){
	bool bRet = false;
	do
	{
		sprite = CCSprite::create(pszFilename);
		this->addChild(sprite);
        
        CCSpriteFrame* frame1 = button_sell_normal;
		sprite1 = CCSprite::createWithSpriteFrame(frame1);
		this->addChild(sprite1);
		sprite1->setVisible(false);
		//sprite1->setColor(ccBLUE);
        
//		sprite2 = CCSprite::create(pszFilename);
//		this->addChild(sprite2);
//		sprite2->setVisible(false);
//		sprite2->setColor(ccGREEN);
        
		sprite3 = CCSprite::createWithSpriteFrame(button_upgrade_normal);
		this->addChild(sprite3);
		sprite3->setVisible(false);
		//sprite3->setColor(ccBLACK);
        
//		sprite4 = CCSprite::create(pszFilename);
//		this->addChild(sprite4);
//		sprite4->setVisible(false);
//		sprite4->setColor(ccRED);
        
		this->setRange(range);
        
        rangeSprite = CCSprite::create("Range.png");
        float wh =rangeSprite->getContentSize().width;
        float scale = 2*range/wh;
        rangeSprite->setScale(scale);
        rangeSprite->setVisible(false);
        rangeSprite->setPosition(sprite->getPosition());
        this->addChild(rangeSprite, -1);
 
        _level =1;
		_target = NULL;
        
		isShowing =false;
        
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
        
	
        
		bRet = true;
	} while (0);
	return bRet;
}
bool Tower:: initWithSpriteFrame(cocos2d::CCSpriteFrame* frame,int range){
    bool bRet = false;
	do
	{
		sprite = CCSprite::createWithSpriteFrame(frame);
        float scalex = 32.0f/sprite->getContentSize().width;
        float scaley = 32.0f/sprite->getContentSize().height;
        sprite->setScaleX(scalex);
        sprite->setScaleY(scaley);
		this->addChild(sprite);
        
        CCSpriteFrame* frame1 = button_sell_normal;
		sprite1 = CCSprite::createWithSpriteFrame(frame1);
		this->addChild(sprite1);
        sprite1->setScale(0.75);
		sprite1->setVisible(false);
        

		//sprite1->setColor(ccBLUE);
        
        //		sprite2 = CCSprite::create(pszFilename);
        //		this->addChild(sprite2);
        //		sprite2->setVisible(false);
        //		sprite2->setColor(ccGREEN);
        
		sprite3 = CCSprite::createWithSpriteFrame(button_upgrade_normal);
		this->addChild(sprite3);
        sprite3->setScale(0.75);
		sprite3->setVisible(false);
		//sprite3->setColor(ccBLACK);
        
        //		sprite4 = CCSprite::create(pszFilename);
        //		this->addChild(sprite4);
        //		sprite4->setVisible(false);
        //		sprite4->setColor(ccRED);
        
		this->setRange(range);
        
        rangeSprite = CCSprite::create("Range.png");
        float scale = (float)2*range/rangeSprite->getContentSize().width;
        rangeSprite->setScale(scale);
        rangeSprite->setVisible(false);
        rangeSprite->setPosition(sprite->getPosition());
        this->addChild(rangeSprite, -1);
        
        
		_target = NULL;
        _level = 1;
		isShowing =false;
        
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
        
        
        
		bRet = true;
	} while (0);
	return bRet;
}
void Tower::levelUp(){
    GameHUD::sharedHUD()->updateResources(-_money);
    _money *=2;
    _damge *=1.5;
    _maxDamge*=2;
    _range *=1.5;
    _interval *=0.5;

   
    sprite->removeFromParent();
    if(_level==TowerMaxLevel){
       
        CCSprite *max = CCSprite::createWithSpriteFrame(button_max_normal);
        max->setPosition(sprite3->getPosition());
        sprite3->removeFromParent();
        sprite3->setScale(0.75);
        sprite3 = max;
       this->addChild(max);
    }else{
    CCLabelTTF *label =(CCLabelTTF*)sprite3->getChildByTag(888);
    CCLabelTTF* towerCost = CCLabelTTF::create("$", "Marker Felt", 20);
    towerCost->setPosition(label->getPosition());
    towerCost->setColor(ccRED);
    towerCost->setString(CCString::createWithFormat("%d",_money)->getCString());
    label->removeFromParent();
    towerCost->setTag(888);
    sprite3->addChild(towerCost);
    sprite3->setScale(0.75);
    }
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
        CCObject *ret = this->getClosestTarget();
        if (ret!=NULL) {
            this->setTarget((Enemy*)ret);
        }else
            this->setTarget(NULL);
            
	}
    else{
  
		double curDistance = ccpDistance(this->getPosition(), this->getTarget()->getPosition());
		if(this->getTarget()->getHP() <= 0 || curDistance > this->getRange()){
            CCObject *ret = this->getClosestTarget();
            if (ret!=NULL) {
                this->setTarget((Enemy*)ret);
               
            }else
                this->setTarget(NULL);
                
		
        }
	}

//	if(this->getTarget() != NULL){
//		CCPoint shootVector = ccpSub(this->getTarget()->getPosition(), this->getPosition());
//		float shootAngle = ccpToAngle(shootVector);
//		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);
//        
//		float rotateSpeed = (float)(0.25 / M_PI);
//		float rotateDuration = fabs(shootAngle * rotateSpeed);
//		sprite->runAction(CCRotateTo::create(rotateDuration, cocosAngle));
//	}
}
void Tower::setMoney(int val){
    _money = val;
    CCLabelTTF* towerCost = CCLabelTTF::create("$", "Marker Felt", 20);
    towerCost->setPosition(ccp(sprite1->getPosition().x+sprite->getContentSize().width/2, 15));
    towerCost->setColor(ccRED);
    towerCost->setTag(888);
    towerCost->setString(CCString::createWithFormat("%d",_money)->getCString());
    sprite3->addChild(towerCost);
}
int Tower::getMoney(){
    return _money;
}
void Tower::show(){
    CCActionInterval *fade = CCFadeIn::create(0.5f);
	sprite1->runAction(CCMoveBy::create(0.5f, ccp(- sprite->getContentSize().width -10, 0)));
	sprite1->setVisible(true);
    
//	sprite2->runAction(CCMoveBy::create(0.5f, ccp(0, sprite->getContentSize().height + 10)));
//	sprite2->setVisible(true);
    
	sprite3->runAction(CCMoveBy::create(0.5f, ccp(sprite->getContentSize().width +10,0)));
	sprite3->setVisible(true);
    
//	sprite4->runAction(CCMoveBy::create(0.5f, ccp(0, - sprite->getContentSize().height - 10)));
//	sprite4->setVisible(true);
    
  //  rangeSprite->setVisible(true);
    
    rangeSprite->runAction(CCSequence::create(fade, CCShow::create(),NULL));
}

void Tower::unShow(){
    CCActionInterval *fade = CCFadeOut::create(0.5f);
	sprite1->runAction(CCSequence::create(CCMoveTo::create(0.5f, sprite->getPosition()), CCHide::create(), NULL));
    
//	sprite2->runAction(CCSequence::create(CCMoveTo::create(0.5f, sprite->getPosition()), CCHide::create(), NULL));
    
	sprite3->runAction(CCSequence::create(CCMoveTo::create(0.5f, sprite->getPosition()), CCHide::create(), NULL));
    
//	sprite4->runAction(CCSequence::create(CCMoveTo::create(0.5f, sprite->getPosition()), CCHide::create(), NULL));
	
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
        GameHUD::sharedHUD()->updateResources(_money);
		return true;
	}
//	if(isShowing && sprite2->boundingBox().containsPoint(touchLocation)){
//		sprite2->runAction(CCBlink::create(1.0f, 5));
//		return true;
//	}
	if(isShowing && sprite3->boundingBox().containsPoint(touchLocation)){
		//sprite3->runAction(CCSequence::create(CCFadeOut::create(0.5), CCFadeIn::create(0.5f), NULL));
        if (GameHUD::sharedHUD()->getResources()<getMoney()) {
            moneyEnough = false;
        }else
            moneyEnough = true;
        if (moneyEnough) {
            if (_level<TowerMaxLevel) {
                _level++;
                levelUp();
            }
        }
		return true;
	}
//	if(isShowing && sprite4->boundingBox().containsPoint(touchLocation)){
//		sprite4->runAction(CCRotateBy::create(1.0f, 360.0f));
//		return true;
//	}
    
	return false;
}
void MachineGunTower::towerLogic(float dt){
    Tower::towerLogic(dt);
//    	if(this->getTarget() != NULL){
//    		CCPoint shootVector = ccpSub(this->getTarget()->getPosition(), this->getPosition());
//    		float shootAngle = ccpToAngle(shootVector);
//    		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);
//    
//    		float rotateSpeed = (float)(0.25 / M_PI);
//    		float rotateDuration = fabs(shootAngle * rotateSpeed);
//    		sprite->runAction(CCRotateTo::create(rotateDuration, cocosAngle));
//    	}
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
MachineGunTower* MachineGunTower::create(cocos2d::CCSpriteFrame *frame, int range){
    MachineGunTower* t = new MachineGunTower;
	if(t && t->initWithSpriteFrame(frame, range)){
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return NULL;
}
MachineGunTower* MachineGunTower::create(){
	return //MachineGunTower::create("MachineGunTurret.png", 100);
    MachineGunTower::create(Tower1_1, T1Range);
}
bool MachineGunTower::initWithSpriteFrame(cocos2d::CCSpriteFrame *frame, int range){
    bool bRet = false;
	do
	{
		CC_BREAK_IF(!Tower::initWithSpriteFrame(frame, range));
        setMoney(25);
        _damge = T1Damage;
        _maxDamge = T1MaxDamage;
        _range = range;
		schedule(schedule_selector(MachineGunTower::fire), 1.0f);
        this->schedule(schedule_selector(MachineGunTower::towerLogic), 0.2f);
		bRet = true;
	} while (0);
	return bRet;
}
bool MachineGunTower::initWithFileAndRange(const char *pszFilename, int range){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Tower::initWithFileAndRange(pszFilename, range));
        setMoney(Tower1Cost);
        _damge = T1Damage;
        _maxDamge = T1MaxDamage;
        _range = range;
		schedule(schedule_selector(MachineGunTower::fire), T1Interval);
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
    
    
    ProjectTile->setDamage(_damge);
    ProjectTile->setMaxDamge(_maxDamge);
    m->getGameLayer()->addChild(ProjectTile);
}
void MachineGunTower::fireReady(){
//    //将图片生成纹理，保存到全局的纹理缓存取
//    CCTexture2D *heroTexture=CCTextureCache::sharedTextureCache()->addImage("attac.png");
//    //用纹理创建4幅帧动画
//    CCSpriteFrame *frame0,*frame1,*frame2,*frame3,*frame4;
//    //第二个参数表示显示区域的x,y,width,height
//    frame0=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(60*0,0,60,66));
//    frame1=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(60,0,60,66));
//    frame2=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(120,0,65,66));
//    frame3=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(200,0,60,66));
//    frame4=CCSpriteFrame::createWithTexture(heroTexture, cocos2d::CCRectMake(260,0,40,66));
//    //CCMutableArray<CCSpriteFrame*> *animFramess=new CCMutableArray<CCSpriteFrame*>(4);
//
//    CCArray *animFrames=CCArray::create();
//    animFrames->addObject(frame0);
//    animFrames->addObject(frame1);
//    animFrames->addObject(frame2);
//    animFrames->addObject(frame3);
//    //  animFrames->addObject(frame4);
//    //根据4幅帧生成ＣＣＡnimation对象
    GameMediator*gm = GameMediator::sharedMediator();
    DataParserBase* parser = gm->getParser3();
    CCAnimation *animation=parser->animateFromFile("ani", "tower1Attack", "frame1");//CCAnimation::createWithSpriteFrames(animFrames);
    //创建一个CCSprite用来显示勇士，可以使用Animation中的一帧来作为勇士静止时的画面
    actionSprite=parser->FrameSpriteFromFile("frame1", 223);
    actionSprite->setPosition(CCPointZero);
    actionSprite->setAnchorPoint(CCPointMake(0.25,0));
    
    sprite->addChild(actionSprite);
    //根据动画模板创建动画
    animation->setDelayPerUnit(0.05f);
    CCAnimate *animate=CCAnimate::create(animation);
    
    auto callfun = CCCallFunc::create(this,callfunc_selector(MachineGunTower::fireNow));
    		CCPoint shootVector = ccpSub(this->getTarget()->getPosition(), this->getPosition());
    		float shootAngle = ccpToAngle(shootVector);
    		float cocosAngle = 90-CC_RADIANS_TO_DEGREES(shootAngle);
    
    		float rotateSpeed = (float)(0.25 / M_PI);
    		float rotateDuration = fabs(shootAngle * rotateSpeed);
    		actionSprite->runAction(CCRotateTo::create(rotateDuration, cocosAngle));
    //创建不断重复的动画，并让heroSprite播放
    actionSprite->runAction(CCSequence::create(animate,callfun,NULL));
    
   // animFrames->release();
    
}
void MachineGunTower::fire(float dt){
	if(this->getTarget() != NULL){
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tower1.wav");
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
void MachineGunTower::levelUp(){
    Tower::levelUp();
    CCSpriteFrame *frame = NULL;
    
    switch (getLevel()) {
        case 2:
            frame = Tower1_2;
            break;
        case 3:
            frame = Tower1_3;
            break;
        case 4:
            frame = Tower1_4;
            break;
            
        default:
            break;
    }
    sprite = CCSprite::createWithSpriteFrame(frame);
    float scalex = 32.0f/sprite->getContentSize().width;
    float scaley = 32.0f/sprite->getContentSize().height;
    sprite->setScaleX(scalex);
    sprite->setScaleY(scaley);
    this->addChild(sprite);
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
FreezeTower* FreezeTower::create(CCSpriteFrame* frame, int range){
	FreezeTower* t = new FreezeTower;
	if(t && t->initWithSpriteFrame(frame, range)){
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return NULL;
}
FreezeTower* FreezeTower::create(){
	return //FreezeTower::create("FreezeTurret.png", 150);
    FreezeTower::create(Tower2_1, T2Range);
}
bool FreezeTower::initWithSpriteFrame(cocos2d::CCSpriteFrame *frame, int range){
    bool bret = false;
    do {
        CC_BREAK_IF(!Tower::initWithSpriteFrame(frame, range));
        setMoney(Tower2Cost);
        _damge = T2Damage;
        _maxDamge = T2MaxDamage;
        _range = range;
        schedule(schedule_selector(FreezeTower::fire), T2Interval);
        this->schedule(schedule_selector(Tower::towerLogic), 0.2f);
        bret = true;
    } while (0);
    return bret;
}
bool FreezeTower::initWithFileAndRange(const char *pszFilename, int range){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Tower::initWithFileAndRange(pszFilename, range));
        setMoney(Tower2Cost);
        _damge = T2Damage;
        _maxDamge = T2MaxDamage;
        _range = range;
		schedule(schedule_selector(FreezeTower::fire), 1.0f);
         this->schedule(schedule_selector(Tower::towerLogic), 0.2f);
		bRet = true;
	} while (0);
	return bRet;
}

void FreezeTower::fire(float dt){
	if(this->getTarget() != NULL){
          CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tower2.wav");
		GameMediator* m = GameMediator::sharedMediator();
        
		CCPoint shootVector = ccpSub(this->getTarget()->getPosition(), this->getPosition());
		CCPoint normalizedShootVector = ccpNormalize(shootVector);
		CCPoint overshotVector = ccpMult(normalizedShootVector, this->getRange());
		CCPoint offscreenPoint = ccpAdd(this->getPosition(), overshotVector);
        
		IceProjectTile* ProjectTile = IceProjectTile::create(offscreenPoint);
		ProjectTile->setPosition(this->getPosition());
		ProjectTile->setRotation(this->getRotation());
        ProjectTile->setDamage(_damge);
        ProjectTile->setMaxDamge(_maxDamge);
        ProjectTile->setRange(_range);
		m->getGameLayer()->addChild(ProjectTile);
	}
}
void FreezeTower::levelUp(){
    Tower::levelUp();
    CCSpriteFrame *frame = NULL;
    
    switch (getLevel()) {
        case 2:
            frame = Tower2_2;
            break;
        case 3:
            frame = Tower2_3;
            break;
        case 4:
            frame = Tower2_4;
            break;
            
        default:
            break;
    }
    sprite = CCSprite::createWithSpriteFrame(frame);
    float scalex = 32.0f/sprite->getContentSize().width;
    float scaley = 32.0f/sprite->getContentSize().height;
    sprite->setScaleX(scalex);
    sprite->setScaleY(scaley);
    this->addChild(sprite);
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
CannonTower* CannonTower::create(CCSpriteFrame* frame, int range){
	CannonTower* t = new CannonTower;
	if(t && t->initWithSpriteFrame(frame, range)){
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return NULL;
}
CannonTower* CannonTower::create(){
	return //CannonTower::create("CannonTurret.png", 400);
    CannonTower::create(Tower3_1, T4Range);
}
bool CannonTower::initWithSpriteFrame(cocos2d::CCSpriteFrame *frame, int range){
    bool bret = false;
    do {
        CC_BREAK_IF(!Tower::initWithSpriteFrame(frame, range));
        setMoney(Tower3Cost);
        _damge = T3Damage;
        _maxDamge = T3MaxDamage;
        _range = range;
        schedule(schedule_selector(CannonTower::fire), T3Interval);
        this->schedule(schedule_selector(Tower::towerLogic), 0.1f);
        bret = true;
    } while (0);
    return bret;
}
bool CannonTower::initWithFileAndRange(const char *pszFilename, int range){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Tower::initWithFileAndRange(pszFilename, range));
        setMoney(Tower3Cost);
        _damge = T3Damage;
        _maxDamge = T3MaxDamage;
        _range = range;
		schedule(schedule_selector(CannonTower::fire), T3Interval);
         this->schedule(schedule_selector(Tower::towerLogic), 0.1f);
		bRet = true;
	} while (0);
	return bRet;
}

void CannonTower::fire(float dt){
	if(this->getTarget() != NULL){
          CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tower3.wav");
		GameMediator* m = GameMediator::sharedMediator();
        
		CannonProjectTile* ProjectTile = CannonProjectTile::create(this->getTarget());
        CCLOG("target pos is:%f,%f",this->getTarget()->getPosition().x,this->getTarget()->getPosition().y);
		ProjectTile->setPosition(this->getPosition());
		ProjectTile->setRotation(this->getRotation());
        ProjectTile->setDamage(_damge);
        ProjectTile->setMaxDamge(_maxDamge);
		m->getGameLayer()->addChild(ProjectTile,1);
	}
}


void CannonTower::levelUp(){
    Tower::levelUp();
    CCSpriteFrame *frame = NULL;
    
    switch (getLevel()) {
        case 2:
            frame = Tower3_2;
            break;
        case 3:
            frame = Tower3_3;
            break;
        case 4:
            frame = Tower3_4;
            break;
            
        default:
            break;
    }
    sprite = CCSprite::createWithSpriteFrame(frame);
    float scalex = 32.0f/sprite->getContentSize().width;
    float scaley = 32.0f/sprite->getContentSize().height;
    sprite->setScaleX(scalex);
    sprite->setScaleY(scaley);
    this->addChild(sprite);
}
MutilTower* MutilTower::create(){
    return  //MutilTower::create("CannonTurret.png", 200);
    MutilTower::create(Tower4_1, T4Range);
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
MutilTower* MutilTower::create(CCSpriteFrame *frame, int range){
    MutilTower *t = new MutilTower;
    if (t&&t->initWithSpriteFrame(frame, range)) {
        t->autorelease();
        return t;
    }
    CC_SAFE_DELETE(t);
    return NULL;
}
bool MutilTower::initWithSpriteFrame(CCSpriteFrame* frame, int range){
    bool bRet = false;
    do {
        CC_BREAK_IF(!Tower::initWithSpriteFrame(frame, range));
        setMoney(Tower4Cost);
        _damge = T4Damage;
        _maxDamge = T4MaxDamage;
        _range = range;
        enemys = CCArray::create();
        enemys->retain();
		schedule(schedule_selector(MutilTower::fire), 2.0f);
        this->schedule(schedule_selector(MutilTower::towerLogic1), 0.2f);
		bRet = true;
    } while (0);
    return bRet;
}
bool MutilTower::initWithFileAndRange(const char *pszFilename, int range){
    bool bRet = false;
    do {
        CC_BREAK_IF(!Tower::initWithFileAndRange(pszFilename, range));
        setMoney(60);
        enemys = CCArray::create();
        enemys->retain();
		schedule(schedule_selector(MutilTower::fire), T4Interval );
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
//        if (count<=3) {
//            enemys->removeAllObjects();
//            enemys->addObjectsFromArray(arr);
//            return;
//   
//        }else
        {
            
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
	if(this->getenemys()->count()!=0){
          CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tower4.wav");
		GameMediator* m = GameMediator::sharedMediator();
        CCObject *obj;
        CCARRAY_FOREACH(this->getenemys(), obj){
            Enemy* target = (Enemy*)obj;
            CannonProjectTile* ProjectTile = CannonProjectTile::create(target);
            ProjectTile->setSpeed(300);
            ProjectTile->setDamage(_damge);
            ProjectTile->setMaxDamge(_maxDamge);
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
    
//	if(enemyArr->count()!=0){
//        {
//        Enemy* enemy =(Enemy *) enemyArr->lastObject();
//		CCPoint shootVector = ccpSub(enemy->getPosition(), this->getPosition());
//		float shootAngle = ccpToAngle(shootVector);
//		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);
//        
//		float rotateSpeed = (float)(0.25 / M_PI);
//		float rotateDuration = fabs(shootAngle * rotateSpeed);
//		sprite->runAction(CCRotateTo::create(rotateDuration, cocosAngle));
//        }
//	}
}

void MutilTower::levelUp(){
    Tower::levelUp();
    CCSpriteFrame *frame = NULL;
    
    switch (getLevel()) {
        case 2:
            frame = Tower4_2;
            break;
        case 3:
            frame = Tower4_3;
            break;
        case 4:
            frame = Tower4_4;
            break;
            
        default:
            break;
    }
    sprite = CCSprite::createWithSpriteFrame(frame);
    float scalex = 32.0f/sprite->getContentSize().width;
    float scaley = 32.0f/sprite->getContentSize().height;
    sprite->setScaleX(scalex);
    sprite->setScaleY(scaley);
    this->addChild(sprite);
}