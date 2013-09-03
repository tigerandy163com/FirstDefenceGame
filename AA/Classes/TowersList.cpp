//
//  TowersList.cpp
//  MyTowerDefense2D
//
//  Created by chunyu.wang on 13-8-21.
//
//

#include "TowersList.h"


USING_NS_CC;
USING_NS_CC_EXT;

bool TowersList::init()
{
   bool bRet = false;
    do
        {
            CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 100, 0, 125)));
            towersInfos = CCArray::createWithCapacity(4);
            towersInfos->addObject(CCStringMake("物理攻击，速度最快"));
            towersInfos->addObject(CCStringMake("减速，慢，无伤害"));
            towersInfos->addObject(CCStringMake("导弹攻击，自动锁定并跟踪目标，射程远，速度慢"));
            towersInfos->addObject(CCStringMake("光明魔法攻击"));
            towersInfos->addObject(CCStringMake("黑暗魔法攻击"));
            towersInfos->addObject(CCStringMake("自然魔法攻击"));
            towersInfos->addObject(CCStringMake("混乱攻击"));
            towersInfos->retain();
            towersImages = CCArray::create(CCString::create("MachineGunTurret.png"), CCString::create("FreezeTurret.png"),CCString::create("CannonTurret.png"),CCString::create("CannonTurret.png"),CCString::create("CannonTurret.png"),CCString::create("CannonTurret.png"),CCString::create("CannonTurret.png"),CCString::create("CannonTurret.png"), NULL);
            towersImages->retain();
            
            pTableView = CCTableView::create(this, CCSizeMake(480-150, 320));
            pTableView->setDirection(kCCScrollViewDirectionVertical);
            pTableView->setPosition(ccp(100,0));
            pTableView->setDelegate(this);
            pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
            this->addChild(pTableView);
            pTableView->reloadData();
            initDialog();

            bRet = true;
        }while(0);
    
    return bRet;
}

void TowersList::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
}

CCSize TowersList::cellSizeForTable(CCTableView *table)
{
    return CCSizeMake(480-150, 75);
}

CCTableViewCell* TowersList::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *pString = (CCString*)towersInfos->objectAtIndex(idx);
    CCString *tString = (CCString*)towersImages->objectAtIndex(idx);
    CCTableViewCell *pCell = table->dequeueCell();
    if (!pCell) {
        pCell = new CCTableViewCell();
        pCell->autorelease();
       CCSprite *pSprite = CCSprite::create("hud.png");
        pSprite->setAnchorPoint(CCPointZero);
        pSprite->setPosition(CCPointZero);
        pCell->addChild(pSprite);
        
        CCLabelTTF *pLabel = CCLabelTTF::create(pString->getCString(), "Arial", 10.0);
        pLabel->setPosition(CCPointMake(10, 10));
        pLabel->setAnchorPoint(CCPointZero);
        ccColor3B color = ccBLUE;
        pLabel->setColor(color);
        pLabel->setTag(123);
        pCell->addChild(pLabel);
        
        CCSprite* tower = CCSprite::create(tString->getCString());
        tower->setPosition(CCPointMake(30,50));
        pCell->addChild(tower);
        
        }
    else
        {
            CCLabelTTF *pLabel = (CCLabelTTF*)pCell->getChildByTag(123);
            pLabel->setString(pString->getCString());
            CCSprite* tower = CCSprite::create(tString->getCString());
            tower->setPosition(CCPointMake(30,50));
            pCell->addChild(tower);
        }
    
    return pCell;
}
unsigned int TowersList::numberOfCellsInTableView(CCTableView *table)
{
    return towersInfos->count();
}

void TowersList::scrollViewDidScroll(CCScrollView *view)
{
}

void TowersList::scrollViewDidZoom(CCScrollView *view)
{
}

void TowersList::initDialog()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *label = CCLabelTTF::create("sure exit?", "", 20);
    label->setPosition(ccp(label->getContentSize().width/2+10, winSize.height - 50));
    this->addChild(label);
    
    CCMenuItemFont *okMenuItem = CCMenuItemFont::create("OK", this, menu_selector(TowersList::okMenuItemCallback));
    okMenuItem->setFontSizeObj(20);
    okMenuItem->setPosition(ccp(15, 100));
    
    CCMenuItemFont *cancelMenuItem = CCMenuItemFont::create("Cancel", this, menu_selector(TowersList::cancelMenuItemCallback));
    cancelMenuItem->setPosition(ccp(65, 100));
    cancelMenuItem->setFontSizeObj(20);
    m_pMenu = CCMenu::create(okMenuItem, cancelMenuItem, NULL);
    m_pMenu->setPosition(CCPointZero);
    this->addChild(m_pMenu);
}

void TowersList::onEnter()
{
    CCLayerColor::onEnter();
   CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,  - 128-1, true);
    
}

void TowersList::onExit()
{
    CCLayerColor::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool TowersList::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCRect rec = pTableView->boundingBox();
    if (rec.containsPoint(pTouch->getLocationInView())){
        m_bTouchedMenu = pTableView->ccTouchBegan(pTouch, pEvent);
    }else if (m_pMenu->boundingBox().containsPoint(pTouch->getLocationInView())){
        m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);

    }
    return true;
}

void TowersList::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        if ( pTableView->boundingBox().containsPoint(pTouch->getLocationInView()))
            pTableView->ccTouchMoved(pTouch, pEvent);
        else if (m_pMenu->boundingBox().containsPoint(pTouch->getLocationInView())){
            m_pMenu->ccTouchMoved(pTouch, pEvent);
                
            }
    }
}

void TowersList::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        if ( pTableView->boundingBox().containsPoint(pTouch->getLocationInView()))
        pTableView->ccTouchEnded(pTouch, pEvent);
        else if (m_pMenu->boundingBox().containsPoint(pTouch->getLocationInView())){
            m_pMenu->ccTouchEnded(pTouch, pEvent);
            
        }
        m_bTouchedMenu = false;
    }
}

void TowersList::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        if ( pTableView->boundingBox().containsPoint(pTouch->getLocationInView()))
        pTableView->ccTouchEnded(pTouch, pEvent);
        else if (m_pMenu->boundingBox().containsPoint(pTouch->getLocationInView())){
            m_pMenu->ccTouchCancelled(pTouch, pEvent);
            
        }
        m_bTouchedMenu = false;
    }
}

void TowersList::okMenuItemCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(false);
//    // 点击确定就退出（拷贝的原有方法）
//    CCDirector::sharedDirector()->end();
//    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	exit(0);
//#endif
}

void TowersList::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
    return;
}