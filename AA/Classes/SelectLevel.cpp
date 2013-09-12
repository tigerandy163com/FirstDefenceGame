//
//  SelectLevel.cpp
//  AA
//
//  Created by chunyu.wang on 13-9-12.
//
//

#include "SelectLevel.h"
USING_NS_CC;
USING_NS_CC_EXT;
#define LevelCount  5

CLevelSelectLayer:: ~CLevelSelectLayer(){
    dataArr->release();
}
bool CLevelSelectLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
//    CCSprite* pBackGround=CCSprite::create("image/scene/menu/levle_select/background.png");
//    pBackGround->setPosition(ccp(CGlobal::s_oVisibleSize.width/2.0f,CGlobal::s_oVisibleSize.height/2.0f));
//    addChild(pBackGround);
    
    //数据源
    dataArr = CCArray::create(CCString::create("map1.png"),CCString::create("map2.png"),CCString::create("map3.png"),CCString::create("map4.png"),CCString::create("map5.png"),NULL);
    dataArr->retain();
    // CCScrollView
    m_ScrollView = CCCGameScrollView::create();    //创建一个scrollview
    
    m_ScrollView->createContainer(
                                  this,
                                  LevelCount,//总共的Page数量
                                  CCSizeMake(winsize.width*0.7,winsize.height));//每一个Page的尺寸
    m_ScrollView->setPosition(ccp(0,0));
    m_ScrollView->setContentOffset(CCPointZero);
    m_ScrollView->setViewSize(winsize);
    m_ScrollView->setDirection(kCCScrollViewDirectionHorizontal);  //设置滚动的方向，有三种可以选择
    
    this->addChild(m_ScrollView);
    
    return true;
    
}

bool CLevelSelectLayer::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
	CCString* helpstr = (CCString*)dataArr->objectAtIndex(nPage);
    
	
	CCSprite *sprite = CCSprite::create(helpstr->getCString());
	pPage->addChild(sprite);
    CCString* str =CCString::createWithFormat("%d",nPage);
	
     CCLabelTTF *pLabel = CCLabelTTF::create(str->getCString(), "Arial", 20.0);

	pLabel->setPosition(ccp(0,200.0f));
	pPage->addChild(pLabel);
    
	return true;
}

void CLevelSelectLayer::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
    CCLog("Current Page=%d",nPage);
}

void CLevelSelectLayer::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
    CCLog("scrollViewClick ....");
}
 void CLevelSelectLayer:: scrollViewDidScroll( cocos2d::extension::CCScrollView* view ){
    
}

 void CLevelSelectLayer:: scrollViewDidZoom( cocos2d::extension::CCScrollView* view ){
    
}

bool CLevelSelectLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    CCRect rec = m_ScrollView->boundingBox();
    if (rec.containsPoint(pTouch->getLocationInView())){
        m_bTouchedMenu = m_ScrollView->ccTouchBegan(pTouch, pEvent);
    }
    
    
    return true;
}

void CLevelSelectLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    if (m_bTouchedMenu) {
        if ( m_ScrollView->boundingBox().containsPoint(pTouch->getLocationInView()))
            m_ScrollView->ccTouchMoved(pTouch, pEvent);
    }
    
}

void CLevelSelectLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    if ( m_bTouchedMenu) {
        if ( m_ScrollView->boundingBox().containsPoint(pTouch->getLocationInView()))
            m_ScrollView->ccTouchEnded(pTouch, pEvent);
        
        m_bTouchedMenu = false;
    }
}

void CLevelSelectLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
    if (m_bTouchedMenu) {
        if ( m_ScrollView->boundingBox().containsPoint(pTouch->getLocationInView()))
            m_ScrollView->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}
void CLevelSelectLayer::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,  - 128, true);
    
}

void CLevelSelectLayer::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
}
