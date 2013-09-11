//
//  MapsList.cpp
//  MyTowerDefense2D
//
//  Created by sven on 13-8-31.
//
//

#include "MapsList.h"
#include "GameMediator.h"


bool MapsList::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 100, 0, 0)));
        CCSprite *background = CCSprite::create("popback.png");
        background->setPosition(CCPointZero);
        this->addChild(background);
        mapsInfos = CCArray::createWithCapacity(3);
        mapsInfos->addObject(CCStringMake("沙漠戈壁"));
        
        mapsInfos->addObject(CCStringMake("冰雪原野"));
        
        mapsInfos->retain();
        mapsImages = CCArray::create(CCString::create("tmw_desert_spacing.png"),CCString::create("map3.jpg"), NULL);
        mapsImages->retain();
        GameMediator::sharedMediator()->getMaps()->addObjectsFromArray(mapsImages);
        
        pTableView = CCTableView::create(this, CCSizeMake(480, 320));
        pTableView->setDirection(kCCScrollViewDirectionVertical);
        pTableView->setPosition(ccp(0,0));
        pTableView->setDelegate(this);
        pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
        this->addChild(pTableView);
        pTableView->setZoomScale(0.8);
        pTableView->reloadData();
      //  initDialog();
        
        bRet = true;
    }while(0);
    
    return bRet;
}

void MapsList::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
    CCSprite *sp = (CCSprite*)cell->getChildByTag(101);
    sp->setOpacity(200);
    GameMediator::sharedMediator()->setCurMapID(cell->getIdx());
    this->popupLayer();
}

CCSize MapsList::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(480, 200);
}

CCTableViewCell* MapsList::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *pString = (CCString*)mapsInfos->objectAtIndex(idx);
    CCString *tString = (CCString*)mapsImages->objectAtIndex(idx);
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
        CCSprite *pSprite = CCSprite::create("hud.png");
        float scale = 200/pSprite->getContentSize().height;
        pSprite->setScale(scale);
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
        pSprite->setTag(100);
        CCLabelTTF *pLabel = CCLabelTTF::create(pString->getCString(), "Arial", 20.0);
        pLabel->setPosition(CCPointMake(50, 10));
        pLabel->setAnchorPoint(CCPointZero);
        ccColor3B color = ccBLUE;
        pLabel->setColor(color);
        pLabel->setTag(123);
        pCell->addChild(pLabel);
        
        CCSprite* tower = CCSprite::create(tString->getCString());
        
        scale = 140/tower->getContentSize().height;
        tower->setScale(scale);
        tower->setPosition(CCPointMake(200,120));
        pCell->addChild(tower);
        tower->setTag(101);
        
    }
    else
    {
        CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(123);
        pLabel->setString(pString->getCString());
        
         CCSprite *sp = (CCSprite*)pCell->getChildByTag(101);
        sp->removeFromParentAndCleanup(true);
        CCSprite* tower = CCSprite::create(tString->getCString());
        
        float scale = 140/tower->getContentSize().height;
        tower->setScale(scale);
        tower->setTag(101);
        tower->setPosition(CCPointMake(200,120));
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
}

void MapsList::scrollViewDidZoom(CCScrollView *view)
{
}


void MapsList::popupLayer(){
        // 定义一个弹出层，传入一张背景图
        PopupLayer* pl = PopupLayer::create("popback.png");
        this->setPopUpLayer(pl);
        
        // ContentSize 是可选的设置，可以不设置，如果设置把它当作 9 图缩放
        pl->setContentSize(CCSizeMake(400, 350));
        pl->setTitle("选择地图");
        pl->setContentText("你要在这张地图上进行游戏吗", 20, 60, 250);
        // 设置回调函数，回调传回一个 CCNode 以获取 tag 判断点击的按钮
        // 这只是作为一种封装实现，如果使用 delegate 那就能够更灵活的控制参数了
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
 
        //场景转换
        CCScene *pScene = MainLayer::scene();
        
        //跳跃式动画
        CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(2, pScene));
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

    CCRect rec = pTableView->boundingBox();
    if (rec.containsPoint(pTouch->getLocationInView())){
        m_bTouchedMenu = pTableView->ccTouchBegan(pTouch, pEvent);
    }
        
    
    return true;
}

void MapsList::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    if (m_bTouchedMenu) {
        if ( pTableView->boundingBox().containsPoint(pTouch->getLocationInView()))
            pTableView->ccTouchMoved(pTouch, pEvent); 
        }
    
}

void MapsList::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    if ( m_bTouchedMenu) {
        if ( pTableView->boundingBox().containsPoint(pTouch->getLocationInView()))
            pTableView->ccTouchEnded(pTouch, pEvent);
        
        m_bTouchedMenu = false;
    }
}

void MapsList::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    if (m_bTouchedMenu) {
        if ( pTableView->boundingBox().containsPoint(pTouch->getLocationInView()))
            pTableView->ccTouchEnded(pTouch, pEvent);
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