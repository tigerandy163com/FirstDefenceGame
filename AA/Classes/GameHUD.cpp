//
//  GameHUD.cpp
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#include "GameHUD.h"
#include "GameMediator.h"
#include "StartScene.h"
#include "data.h"
using namespace cocos2d;
USING_NS_CC_EXT;
int waveCount;
static GameHUD* _sharedHUD;

GameHUD* GameHUD::sharedHUD(){
	if (_sharedHUD==NULL) {
        _sharedHUD = new GameHUD();
        _sharedHUD->init();
    }
    return  _sharedHUD;
}

GameHUD::~GameHUD(){
	CC_SAFE_RELEASE_NULL(movableSprites);
}

bool GameHUD::init(){
	bool bRet = false;
	do
	{
		//CC_BREAK_IF(!CCLayer::init());
        
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
		CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565);
		background = CCSprite::create("hud.png");
		background->setAnchorPoint(CCPointZero);
		this->addChild(background);
       // background->setVisible(false);
		CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default);
        
		movableSprites = CCArray::create();
		movableSprites->retain();
        
		selSprite = NULL;
		selSpriteRange = NULL;
        //这里是在容器层testScrollView里创建scrollView的实例
        tScrollView=CCScrollView::create(background->getContentSize());
        //设定scrollView的内容尺寸，比如说这里面只是要放一个100x100尺寸的图片，就按下面这样设定
        tScrollView->setContentSize(CCSize(480,background->getContentSize().height));
        // 设置滚屏属性，这里设置的是两个方向随便拉，其它参数自己看源码
        tScrollView->setDirection(kCCScrollViewDirectionHorizontal);
        //这位置我是随便设定的，需要的自己改
        tScrollView->setPosition(CCPointZero);
        //tScrollView->setContainer(this);
        this->addChild(tScrollView);
       // CCTexture2D *towers =CCTextureCache::sharedTextureCache()->addImage("enemy.png");
        CCSpriteFrame *tower1 =TowerIcon1; //CCSpriteFrame::createWithTexture(towers, CCRectMake(520, 156 ,40, 59));
        CCSpriteFrame *tower2 =TowerIcon2; //CCSpriteFrame::createWithTexture(towers, CCRectMake(58 ,225, 45, 62));
        CCSpriteFrame *tower3 =TowerIcon3; //CCSpriteFrame::createWithTexture(towers, CCRectMake(904, 366, 60, 55));
        CCSpriteFrame *tower4 =TowerIcon4; //CCSpriteFrame::createWithTexture(towers, CCRectMake(409 ,333, 43 ,62));
		//CCArray* images = CCArray::create(CCString::create("MachineGunTurret.png"), CCString::create("FreezeTurret.png"),
                                         // CCString::create("CannonTurret.png"),CCString::create("CannonTurret.png"), NULL);
        CCArray* frameArr = CCArray::create(tower1,tower2,tower3,tower4,NULL);
        towersFrameArr = CCArray::create(Tower1_1,Tower2_1,Tower3_1,Tower4_1,NULL);
        CCArray* costArr = CCArray::create(CCString::create("25"),CCString::create("30"),CCString::create("40"),CCString::create("60"),NULL);
        towersFrameArr->retain();
        orignArr_L1 = CCPointArray::create(frameArr->count());
        orignArr_L1->retain();
        float offsetFraction =15; //((float)(CCDirector::sharedDirector()->getWinSize().width))/(frameArr->count()+1);
		for(unsigned int i = 0; i < frameArr->count(); i++){
			CCSpriteFrame* image = (CCSpriteFrame*)frameArr->objectAtIndex(i);
			CCSprite* sprite = CCSprite::createWithSpriteFrame(image);
            
			//float offsetFraction = ((float)(i+1))/(images->count()+1);
			sprite->setPosition(ccp((i+1)*(sprite->getContentSize().width+offsetFraction), 20));
			sprite->setTag(i + 1);
			tScrollView->addChild(sprite);
			movableSprites->addObject(sprite);
            orignArr_L1->addControlPoint(sprite->getPosition());
			CCLabelTTF* towerCost = CCLabelTTF::create("$", "Marker Felt",25);
			towerCost->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/4));
			towerCost->setColor(ccRED);
			sprite->addChild(towerCost);
            CCString *cost = (CCString*)costArr->objectAtIndex(i);
			towerCost->setString(cost->getCString());
		}
        
		resources = 300;
		resourceLabel = CCLabelTTF::create("Money 300", "Marker Felt", 20, CCSizeMake(150, 25), kCCTextAlignmentRight);
		resourceLabel->setPosition(ccp(30, winSize.height -15));
		resourceLabel->setColor(ccYELLOW);
		this->addChild(resourceLabel, 1);
        
		CCLabelTTF* baseHpLabel = CCLabelTTF::create("Base Health", "Marker Felt", 20, CCSizeMake(150, 25), kCCTextAlignmentRight);
		baseHpLabel->setPosition(ccp(winSize.width - 185, winSize.height -15));
		resourceLabel->setColor(ccc3(255, 80, 20));
		this->addChild(baseHpLabel, 1);
        
		waveCount = 1;
		waveCountLabel = CCLabelTTF::create("Wave 1", "Marker Felt", 20, CCSizeMake(150, 25), kCCTextAlignmentRight);
		waveCountLabel->setPosition(ccp(winSize.width * 0.5f - 80, winSize.height - 15));
		waveCountLabel->setColor(ccRED);
		this->addChild(waveCountLabel, 1);
        
		baseHpPercentage = 100;
		healthBar = CCProgressTimer::create(CCSprite::create("health_bar_green.png"));
		healthBar->setType(kCCProgressTimerTypeBar);
		healthBar->setMidpoint(ccp(0, 0));
		healthBar->setBarChangeRate(ccp(1, 0));
		healthBar->setPercentage(baseHpPercentage);
		healthBar->setScale(0.5f);
		healthBar->setPosition(ccp(winSize.width -55, winSize.height -15));
		this->addChild(healthBar);

        CCMenuItemFont *back = CCMenuItemFont::create("back", this, menu_selector(GameHUD::backToMain));
        
        back->setPosition(CCPointZero);
        back->setFontSizeObj(20);
        CCMenuItemFont *pause = CCMenuItemFont::create("stop", this, menu_selector(GameHUD::pauseGame));
       
        pause->setPosition(CCPointZero);
        pause->setFontSizeObj(20);
        
        CCMenuItemFont *speed = CCMenuItemFont::create("x1", this, menu_selector(GameHUD::speedUp));
        
        speed->setPosition(CCPointZero);
        speed->setFontSizeObj(20);
        
        CCMenu *menu1 = CCMenu::create(back,NULL);
        menu1->setColor(ccRED);
        menu1->setPosition(ccp(winSize.width -150, winSize.height -35));
        this->addChild(menu1);
        
        CCMenu* menu2 = CCMenu::create(pause,NULL);
        menu2->setColor(ccBLUE);
        menu2->setPosition(ccp(winSize.width - 100,winSize.height-35));
        menu2->setTag(100);
        this->addChild(menu2);
        
        CCMenu* menu3 = CCMenu::create(speed,NULL);
        menu3->setColor(ccGREEN);
        menu3->setPosition(ccp(winSize.width - 50,winSize.height-35));
        menu3->setTag(101);
        this->addChild(menu3);
        
        CCMenuItemSprite *lev1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrame(ui_lv1_normal), CCSprite::createWithSpriteFrame(ui_lv1_press),this,menu_selector(GameHUD::lev_1_buttonPress));
        
        lev1->setPosition(CCPointZero);
        CCMenu* menuL1 = CCMenu::create(lev1,NULL);
        menuL1->setPosition(ccp(30,40));
          menuL1->setTag(10);
        tScrollView->addChild(menuL1);
      
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0 , true);
        
		bRet = true;
	} while (0);
	return bRet;
}
void GameHUD::lev_1_buttonPress(){
    CCObject *ot = NULL;
    static bool show = true;
    show = !show;

    CCARRAY_FOREACH(movableSprites, ot){
        CCSprite* sprite = (CCSprite*)ot;
        if (!show) {
        CCPoint pos = sprite->getPosition();
        CCMoveTo *move = CCMoveTo::create(0.25, CCPointZero);
        sprite->runAction(CCSequence::create(move,CCHide::create(),NULL));
        }else
        {
            int index = movableSprites->indexOfObject(ot);
            CCMoveTo *move = CCMoveTo::create(0.25, orignArr_L1->getControlPointAtIndex(index));
            sprite->runAction(CCSequence::create(CCShow::create(),move,NULL));
        }
    }
}
void GameHUD::pauseGame(cocos2d::CCObject* psender){
    if (getIsPause()) {
        return;
    }
    setIsPause(true);
       CCMenu* menu =  (CCMenu*)this->getChildByTag(100);
    
    CCMenuItemFont *pause = CCMenuItemFont::create("resume", this, menu_selector(GameHUD::resumeGame));
    
    pause->setPosition(CCPointZero);
    pause->setFontSizeObj(20);
    CCMenu* menu2 = CCMenu::create(pause,NULL);
    menu2->setColor(ccBLUE);
    menu2->setPosition(menu->getPosition());
    menu2->setTag(100);
    
    menu->removeFromParent();
    this->addChild(menu2);
    CCDirector::sharedDirector()->pause();
    
}
void GameHUD::resumeGame(cocos2d::CCObject* psender){
    if (!getIsPause()) {
        return;
    }
    setIsPause(false);
    CCMenu* menu =  (CCMenu*)this->getChildByTag(100);
    
    CCMenuItemFont *pause = CCMenuItemFont::create("stop", this, menu_selector(GameHUD::pauseGame));
    
    pause->setPosition(CCPointZero);
    pause->setFontSizeObj(20);
    CCMenu* menu2 = CCMenu::create(pause,NULL);
    menu2->setColor(ccBLUE);
    menu2->setPosition(menu->getPosition());
    menu2->setTag(100);
    
    menu->removeFromParent();
    this->addChild(menu2);
    CCDirector::sharedDirector()->resume();
}
void GameHUD::speedUp(cocos2d::CCObject *psender){
    static bool isshouldup = false;
    
    GameMediator* gm = GameMediator::sharedMediator();
    if (gm->nowSpeed==1){
        isshouldup = true;
    }
    if (gm->nowSpeed==maxSpeed) {
        gm->nowSpeed=1;
        isshouldup = false;
    }
    if (gm->nowSpeed<maxSpeed&&isshouldup) {
       gm->nowSpeed+=1;
//    }else if ( gm->nowSpeed>1&&!isshouldup){
//        gm->nowSpeed-=1;
    }
    setSpeed(gm->nowSpeed);
}
void GameHUD::setSpeed(int val){
    CCMenu* menu = (CCMenu*)getChildByTag(101);
    CCString *str = CCString::createWithFormat("x%d",val);
    CCMenuItemFont *speed = CCMenuItemFont::create(str->getCString(), this, menu_selector(GameHUD::speedUp));
    
    speed->setPosition(CCPointZero);
    speed->setFontSizeObj(20);
    CCMenu* menu3 = CCMenu::create(speed,NULL);
    menu3->setColor(ccGREEN);
    menu3->setPosition(menu->getPosition());
    menu3->setTag(101);
    menu->removeFromParent();
    this->addChild(menu3);
    CCScheduler* pScheduler = CCDirector::sharedDirector()->getScheduler();
    pScheduler->setTimeScale(val); //实现加速效果
}
void GameHUD::backToMain(){
    if (getIsPause()) {
        resumeGame(NULL);
    }
    CCScene *scene = StartScene::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(1, scene));
}
float GameHUD::rangeScale(int towerID){
    float ret = 0.0;
    float range = 0;
    switch (towerID) {
        case 1:
            range = 100.0;
            break;
        case 2:
            range = 150.0;
            break;
        case 3:
            range = 200.0;
            break;
        case 4:
            range = 200.0;
            break;
        default:
            break;
    }
   return  ret = range/100.0;
}
bool GameHUD::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	CCPoint touchLocation = this->convertTouchToNodeSpace(pTouch);
	if(!background->boundingBox().containsPoint(touchLocation)){
		return false;
	}
    
	CCSprite* newSprite = NULL;
	CCObject* temp;
	CCARRAY_FOREACH(movableSprites, temp){
		CCSprite* sprite = (CCSprite*)temp;
		if(sprite->boundingBox().containsPoint(touchLocation)){
            tScrollView->setTouchEnabled(false);
			selSpriteRange = CCSprite::create("Range.png");
             float scale = rangeScale(sprite->getTag());
			selSpriteRange->setScale(scale);
			this->addChild(selSpriteRange, -1);
			selSpriteRange->setPosition(sprite->getPosition());
            CCSpriteFrame* frame = (CCSpriteFrame*)towersFrameArr->objectAtIndex(movableSprites->indexOfObject(temp));
			newSprite = CCSprite::createWithSpriteFrame(frame);
			//newSprite->setPosition(ccpAdd(sprite->getPosition(), ccp(0, 30)));
            newSprite->setPosition(touchLocation);
			selSprite = newSprite;
			selSprite->setTag(sprite->getTag());
			this->addChild(newSprite);
			break;
		}
	}
	return true;
}

void GameHUD::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	CCPoint touchLocation = this->convertTouchToNodeSpace(pTouch);
    
	CCPoint oldTouchLocation = pTouch->getPreviousLocationInView();
	oldTouchLocation = CCDirector::sharedDirector()->convertToGL(oldTouchLocation);
	oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);
    
	CCPoint translation = ccpSub(touchLocation, oldTouchLocation);
	if(selSprite){
		CCPoint newPos = ccpAdd(selSprite->getPosition(), translation);
		selSprite->setPosition(newPos);
		selSpriteRange->setPosition(newPos);
        
		GameMediator* m = GameMediator::sharedMediator();
		CCPoint touchLocationInGameLayer = m->getGameLayer()->convertTouchToNodeSpace(pTouch);
        
		bool isBuildable = m->getGameLayer()->canBuildOnTilePosition(touchLocationInGameLayer);
		if(isBuildable){
			selSprite->setOpacity(200);
		}else{
			selSprite->setOpacity(50);
		}
	}
}

void GameHUD::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	CCPoint touchLocation = this->convertTouchToNodeSpace(pTouch);
    
	GameMediator* m = GameMediator::sharedMediator();
    tScrollView->setTouchEnabled(true);
	if(selSprite){
        
		if(!background->boundingBox().containsPoint( touchLocation)){
			CCPoint touchLocationInGameLayer = m->getGameLayer()->convertTouchToNodeSpace(pTouch);
			m->getGameLayer()->addTower(touchLocationInGameLayer, selSprite->getTag());
		}
		this->removeChild(selSprite, true);
		selSprite = NULL;
		this->removeChild(selSpriteRange, true);
		selSpriteRange = NULL;
	}
}

void GameHUD::updateBaseHp(int amount){
	baseHpPercentage += amount;
    
	if(baseHpPercentage <= 25){
		healthBar->setSprite(CCSprite::create("health_bar_red.png"));
		healthBar->setScale(0.5f);
	}
    
	if(baseHpPercentage <=0){
		CCLog("Game Over");
        this->unscheduleAllSelectors();
        GameMediator::sharedMediator()->clear();
        CCDirector::sharedDirector()->replaceScene((CCTransitionJumpZoom::create(3.0f, StartScene::scene())));
        return;
	}
    
	healthBar->setPercentage(baseHpPercentage);
}

void GameHUD::updateResources(int amount){
	resources += amount;
	resourceLabel->setString(CCString::createWithFormat("Money %d",resources)->getCString());
}

void GameHUD::updateResourcesNom(){
	resources += 1;
	resourceLabel->setString(CCString::createWithFormat("Money %d",resources)->getCString());
}

void GameHUD::updateWaveCount(){
	waveCount ++;
	waveCountLabel->setString(CCString::createWithFormat("Wave %d",waveCount)->getCString());
}
void GameHUD::resetHUD(){
    waveCount = 1;
    GameMediator::sharedMediator()->nowSpeed = 1;
    setSpeed(1);
    resumeGame(NULL);
    waveCountLabel->setString(CCString::createWithFormat("Wave %d",waveCount)->getCString());
    resources = 300;
    resourceLabel->setString(CCString::createWithFormat("Money %d",resources)->getCString());
    baseHpPercentage = 100;
    healthBar->setPercentage(baseHpPercentage);
}

