//
//  LoadingLayer.cpp
//  AA
//
//  Created by chunyu.wang on 13-9-5.
//
//

#include "LoadingLayer.h"
#include "MainLayer.h"
#include "LoadLevelInfo.h"
#include "DataParserBase.h"
#include "GameMediator.h"
USING_NS_CC;
#define ToTalResCount 16
LoadingLayer::LoadingLayer(){
    
}
LoadingLayer::~LoadingLayer(){
    
}

CCScene* LoadingLayer::scene(){
   return  LoadingLayer::scene(1);
}
CCScene* LoadingLayer:: scene(int lev){
    do {
        CCLayer *layer = LoadingLayer::creat(lev);
        CC_BREAK_IF(!layer);
        CCScene *scene = CCScene::create();
        scene->addChild(layer);
        return scene;
    } while (0);
    return NULL;
}
LoadingLayer* LoadingLayer::creat(int Lev){
    LoadingLayer *layer =new  LoadingLayer;
    if (layer&&layer->initWithLevel(Lev)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}
LoadingLayer* LoadingLayer::creat(){
    return  creat(1);
}
bool LoadingLayer::init(){
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        bRet = true;
    } while (0);
    return bRet;
}
bool LoadingLayer::initWithLevel(int lev){
    bool bRet = false;
    do {
        CC_BREAK_IF(!LoadingLayer::init());
        scheduleUpdate();
        GameMediator *gm = GameMediator::sharedMediator();
        CCSize winsize = CCDirector::sharedDirector()->getWinSize();
        CCLabelTTF *label = CCLabelTTF::create("Loading(0%)..."," Marker Felt", 30);
        label->setPosition(ccp(winsize.width/2, winsize.height/2));
        addChild(label);
        label->setTag(123);
        currentCount = 0;
        totalCount = ToTalResCount;
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("battle1.wav");
        currentCount++;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tower1.wav");
        currentCount++;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tower2.wav");
        currentCount++;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tower3.wav");
        currentCount++;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("tower4.wav");
        currentCount++;
  
        {
            gm->setParser1(DataParserBase::creat("actorData.txt"));
            currentCount++;
            gm->setParser2(DataParserBase::creat("data.txt"));
            currentCount++;
            gm->setParser3(DataParserBase::creat("res.txt"));
            currentCount++;
            gm->setParser4(DataParserBase::creat("res1.txt"));
            currentCount++;
            gm->setParser5(DataParserBase::creat("stage.txt"));
            currentCount++;
            gm->setParser6(DataParserBase::creat("UI.txt"));
            currentCount++;
        }

       gm->setFirstLoad(false);
        CCTextureCache::sharedTextureCache()->addImageAsync("enemy.png", this, callfuncO_selector(LoadingLayer::loadingCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("choose.png", this, callfuncO_selector(LoadingLayer::loadingCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("effect1.png", this, callfuncO_selector(LoadingLayer::loadingCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("icon.png", this, callfuncO_selector(LoadingLayer::loadingCallBack));
        CCTextureCache::sharedTextureCache()->addImageAsync("effect2.png", this, callfuncO_selector(LoadingLayer::loadingCallBack));
        
        bRet =true;
    } while (0 );
    return bRet;
}

void LoadingLayer::loadingCallBack(cocos2d::CCObject *psender){
    ++currentCount;
}
void LoadingLayer::startGame(){
    CCScene *game = MainLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.3, game));
}
void LoadingLayer::update(float delta){
    float percent = (float)currentCount/(float)totalCount*100;
    CCLabelTTF *label =(CCLabelTTF*) getChildByTag(123);
    CCString *str = CCString::createWithFormat("Loading(%d)...",(int)percent);
    label->setString(str->getCString());
    if (currentCount==totalCount) {
        label->setString("Load finished");
        unscheduleUpdate();
        scheduleOnce(schedule_selector(LoadingLayer::startGame), 0.3);
    }
}