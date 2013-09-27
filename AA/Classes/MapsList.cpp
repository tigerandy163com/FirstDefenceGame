//
//  MapsList.cpp
//  MyTowerDefense2D
//
//  Created by sven on 13-8-31.
//
//

#include "MapsList.h"
#include "GameMediator.h"
#include "LoadingLayer.h"
#include "XBridge.h"

#define CELLW 256
#define CELLH 128
bool MapsList::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 100, 0, 0)));
        CCSprite *background = CCSprite::create("popback.png");
        background->setPosition(CCPointZero);
        this->addChild(background);
  
 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        XBridge::doSth();
        
#endif
        CCMenuItemFont *select = CCMenuItemFont::create("选择", this, menu_selector(MapsList::popupLayer));
        select->setFontSize(20);
        menu = CCMenu::create(select,NULL);
        menu->setPosition(ccp(200, 100));
        this->addChild(menu);
//        mapsInfos = CCArray::create(CCStringMake("map1.png"),CCStringMake("map2.png"),CCStringMake("map3.png"),CCStringMake("map4.png"),CCStringMake("map5.png"),CCStringMake("map6.png"), NULL);
//
//        
//        mapsInfos->retain();
//        mapsImages = CCArray::create(CCStringMake("map1.png"),CCStringMake("map2.png"),CCStringMake("map3.png"),CCStringMake("map4.png"),CCStringMake("map5.png"),CCStringMake("map6.png"), NULL);
//        mapsImages->retain();
//        GameMediator::sharedMediator()->getMaps()->addObjectsFromArray(mapsImages);
//        
//        pTableView = CCTableView::create(this, CCSizeMake(480, 320));
//        
//        pTableView->setDirection(kCCScrollViewDirectionHorizontal);
//        pTableView->setPosition(ccp(0,0));
//        pTableView->setDelegate(this);
//        pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
//        this->addChild(pTableView);
//        
//        pTableView->reloadData();
      //  initDialog();
        lastpos = -1;
        bRet = true;
    }while(0);
    
    return bRet;
}

void MapsList::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
//    CCSprite *sp = (CCSprite*)cell->getChildByTag(101);
//    sp->setOpacity(200);
//    GameMediator::sharedMediator()->setCurMapID(cell->getIdx());
//    this->popupLayer();
}

CCSize MapsList::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(CELLW, CELLH);
}

CCTableViewCell* MapsList::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *pString = (CCString*)mapsInfos->objectAtIndex(idx);
    CCString *tString = (CCString*)mapsImages->objectAtIndex(idx);
    CCTableViewCell *pCell =NULL; //table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        float scale=0.0f;
//        CCSprite *pSprite = CCSprite::create("hud.png");
//         scale = CELLH/pSprite->getContentSize().height;
//        pSprite->setScaleY(scale);
//        pSprite->setAnchorPoint(CCPointZero);
//        pSprite->setPosition(CCPointZero);
//        pCell->addChild(pSprite);
//        pSprite->setTag(100);
//        CCLabelTTF *pLabel = CCLabelTTF::create(pString->getCString(), "Arial", 20.0);
//        pLabel->setPosition(CCPointMake(50, 10));
//        pLabel->setAnchorPoint(CCPointZero);
//        ccColor3B color = ccBLUE;
//        pLabel->setColor(color);
//        pLabel->setTag(123);
//        pCell->addChild(pLabel);
        
        CCSprite* tower = CCSprite::create(tString->getCString());
        tower->setAnchorPoint(CCPointZero);

        tower->setPosition(CCPointMake(0,-100));
        pCell->addChild(tower);
        tower->setTag(101);
        
    }
    else
    {
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(123);
//        pLabel->setString(pString->getCString());
//        
//         CCSprite *sp = (CCSprite*)pCell->getChildByTag(101);
//        sp->removeFromParentAndCleanup(true);
        CCSprite* tower = CCSprite::create(tString->getCString());
        tower->setAnchorPoint(CCPointZero);
  
        tower->setTag(101);
        tower->setPosition(CCPointMake(0,-100));
        pCell->addChild(tower);
    }
    
    return pCell;
}
unsigned int MapsList::numberOfCellsInTableView(CCTableView *table)
{
    return mapsInfos->count();
}

void MapsList::scrollViewDidScroll(CCScrollView *view)
{
    int  dir = -1;
    if (lastpos!=-1) {
        if (view->getContentOffset().x<lastpos) {
            dir = 0;
        }
        if (view->getContentOffset().x>lastpos) {
            dir =1;
        }
    }
    lastpos = view->getContentOffset().x ;
     CCLOG("last:%f",lastpos);
    int nPage = abs((int)view->getContentOffset().x / (int)CELLW);
    if (pTableView) {
        CCTableViewCell *cell = pTableView->cellAtIndex(nPage);
        if (cell!=NULL){
    
       CCPoint pos= this->convertToNodeSpace( cell->getPosition());
        
        float pos_x =-( pos.x + CELLW/2);
            CCLOG("pagddd:%f",pos_x);
            {
                if (dir==1&&( lastpos==-128||lastpos==-384||lastpos==-640)) {
                    
                    cell->getChildByTag(101)->setScale(1.2);
                }else if (dir==0)
                    cell->getChildByTag(101)->setScale(1);
            }
        }
    }
 
}

void MapsList::scrollViewDidZoom(CCScrollView *view)
{
    
    
}
void MapsList:: tableCellHighlight(CCTableView* table, CCTableViewCell* cell){
    CCLOG("hiiii");

}
 void MapsList:: tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell){
     CCLOG("kkkkk");

}

void MapsList::popupLayer(){
        // 定义一个弹出层，传入一张背景图
        PopupLayer* pl = PopupLayer::create("popback.png");
        this->setPopUpLayer(pl);
        

        pl->setContentSize(CCSizeMake(400, 350));
        pl->setTitle("选择地图");
        pl->setContentText("你要在这张地图上进行游戏吗", 20, 60, 250);

        pl->setCallbackFunc(this, callfuncN_selector(MapsList::buttonCallback));
        // 添加按钮，设置图片，文字，tag 信息
        pl->addButton("button.png", "button_hl.png", "确定", 0);
        pl->addButton("button.png", "button_hl.png", "取消", 1);
        // 添加到当前层
      
        this->addChild(pl);
    }


void MapsList::removePop(){
  
    this->getPopUpLayer()->removeFromParentAndCleanup(true);
}
void MapsList::buttonCallback(cocos2d::CCNode *pNode){
    // 打印 tag 0， 确定，1 ，取消
    int tag = pNode->getTag();
    CCLog("button call back. tag: %d",tag);
    if (tag==0) {
      
        GameMediator::sharedMediator()->setCurMapID(XBridge::getCurMap());
        CCLog("Mapis:%d",XBridge::getCurMap());
        //场景转换
        CCScene *pScene = LoadingLayer::scene();
        
     
        CCDirector::sharedDirector()->replaceScene(pScene);
         XBridge::clearmy();
 
    
    }else
    {
        
    }
}
void MapsList::onEnter()
{
    CCLayerColor::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,  - 128, true);
    
}

void MapsList::onExit()
{
    CCLayerColor::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->getPopUpLayer()->release();
   
}

bool MapsList::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

//    CCRect rec = pTableView->boundingBox();
//    if (rec.containsPoint(pTouch->getLocationInView())){
//        m_bTouchedMenu = pTableView->ccTouchBegan(pTouch, pEvent);
//    }
//        
        CCRect rec = menu->boundingBox();
        if (rec.containsPoint(pTouch->getLocationInView())){
           m_bTouchedMenu = menu->ccTouchBegan(pTouch, pEvent);
        }
    
    return true;
}

void MapsList::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

//    if (m_bTouchedMenu) {
//        if ( pTableView->boundingBox().containsPoint(pTouch->getLocationInView()))
//            pTableView->ccTouchMoved(pTouch, pEvent); 
//        }

}

void MapsList::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

//    if ( m_bTouchedMenu) {
//        if ( pTableView->boundingBox().containsPoint(pTouch->getLocationInView()))
//            pTableView->ccTouchEnded(pTouch, pEvent);
//        
//        m_bTouchedMenu = false;
//    }
        if ( m_bTouchedMenu) {
            if ( menu->boundingBox().containsPoint(pTouch->getLocationInView()))
                menu->ccTouchEnded(pTouch, pEvent);
    
           m_bTouchedMenu = false;
        }
}

void MapsList::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

//    if (m_bTouchedMenu) {
//        if ( pTableView->boundingBox().containsPoint(pTouch->getLocationInView()))
//            pTableView->ccTouchEnded(pTouch, pEvent);
//        m_bTouchedMenu = false;
//    }
       if (m_bTouchedMenu) {
            if ( menu->boundingBox().containsPoint(pTouch->getLocationInView()))
               menu->ccTouchEnded(pTouch, pEvent);
           m_bTouchedMenu = false;
        }
}

void MapsList::okMenuItemCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(false);
    //    // 点击确定就退出（拷贝的原有方法）
    //    CCDirector::sharedDirector()->end();
    //
    //#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //	exit(0);
    //#endif
}

void MapsList::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
    return;
}