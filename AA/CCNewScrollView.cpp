//
//  CCNewScrollView.cpp
//  AA
//
//  Created by sven on 13-9-11.
//
//

#include "CCNewScrollView.h"


USING_NS_CC;
USING_NS_CC_EXT;

CCCGameScrollView::CCCGameScrollView()
:m_fAdjustSpeed(ADJUST_ANIM_VELOCITY)
, m_nPrePage(0)
{
    
}

CCCGameScrollView::~CCCGameScrollView()
{
    
}

bool CCCGameScrollView::init()
{
	if (!CCScrollView::init())
	{
		return false;
	}
    
	return true;
}

bool CCCGameScrollView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	m_BeginOffset = getContentOffset();
	return CCScrollView::ccTouchBegan(pTouch, pEvent);
}

void CCCGameScrollView::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCScrollView::ccTouchMoved(pTouch, pEvent);
}

void CCCGameScrollView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint touchPoint = pTouch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
    
	CCScrollView::ccTouchEnded(pTouch, pEvent);
    
	CCPoint m_EndOffset=getContentOffset();
    
	if (m_BeginOffset.equals(m_EndOffset))
	{
		int nPage = abs(m_EndOffset.x / (int)m_CellSize.width);
		CCNewScrollViewDelegate* pDele=(CCNewScrollViewDelegate*)m_pDelegate;
		pDele->scrollViewClick(m_EndOffset,touchPoint,m_pContainer->getChildByTag(nPage),nPage);
		return ;
	}
    
	adjustScrollView(m_BeginOffset,m_EndOffset);
}

void CCCGameScrollView::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCScrollView::ccTouchCancelled(pTouch, pEvent);
    
	CCPoint m_EndOffset=getContentOffset();
	adjustScrollView(m_BeginOffset,m_EndOffset);
}

void CCCGameScrollView::adjustScrollView( const cocos2d::CCPoint& oBegin,const cocos2d::CCPoint & oEnd)
{
    
	int nPage = abs(oBegin.x / (int)m_CellSize.width);
    
	int nAdjustPage = 0;
    
	int nDis = oEnd.x-oBegin.x;
    
	if (nDis<-getViewSize().width/5)
	{
		nAdjustPage=nPage+1;
	}
	else if (nDis>getViewSize().width/5)
	{
		nAdjustPage=nPage-1;
	}
	else
	{
		nAdjustPage=nPage;
	}
    
	nAdjustPage=MIN(nAdjustPage,m_nPageCount-1);
	nAdjustPage=MAX(nAdjustPage,0);
    
	scrollToPage(nAdjustPage);
}

void CCCGameScrollView::scrollToPage( int nPage )
{
	// 关闭CCScrollView中的自调整
	unscheduleAllSelectors();
    
	CCPoint oOffset=getContentOffset();
	// 调整位置
	CCPoint adjustPos=ccp(-m_CellSize.width*nPage,0);
    
	// 调整动画时间
	float adjustAnimDelay=ccpDistance(adjustPos,oOffset)/m_fAdjustSpeed;
    
	// 调整位置
	setContentOffsetInDuration(adjustPos, adjustAnimDelay);
    
	if (nPage!=m_nPrePage)
	{
		schedule(schedule_selector(CCCGameScrollView::onScrollEnd),adjustAnimDelay,0,0.0f);
		m_nPrePage=nPage;
	}
}

void CCCGameScrollView::onScrollEnd(float fDelay)
{
	int nPage=getCurPage();
	CCNewScrollViewDelegate* pDele=(CCNewScrollViewDelegate*)m_pDelegate;
	pDele->scrollViewScrollEnd(m_pContainer->getChildByTag(nPage),nPage);
}

void CCCGameScrollView::scrollToNextPage()
{
	int nCurPage=getCurPage();
	if (nCurPage>=m_nPageCount-1)
	{
		return ;
	}
	scrollToPage(nCurPage+1);
}

void CCCGameScrollView::scrollToPrePage()
{
	int nCurPage=getCurPage();
	if (nCurPage<=0)
	{
		return ;
	}
	scrollToPage(nCurPage-1);
}

bool CCCGameScrollView::createContainer(CCNewScrollViewDelegate* pDele, int nCount,const cocos2d::CCSize & oSize )
{
	m_nPageCount=nCount;
	m_CellSize=oSize;
	setDelegate(pDele);
    
	CCLayer* pContainer=CCLayer::create();
	pContainer->setAnchorPoint(CCPointZero);
	pContainer->setPosition(CCPointZero);
    
	CCSize winSize=CCDirector::sharedDirector()->getVisibleSize();
    
	for (int i=0;i<nCount;++i)
	{
		CCNode* pNode=CCNode::create();
		pDele->scrollViewInitPage(pNode,i);
		pNode->setPosition(ccp(winSize.width/2+i*oSize.width,winSize.height/2));
		pNode->setTag(i);
		pContainer->addChild(pNode);
	}
    
	setContainer(pContainer);
	setContentSize(CCSizeMake(oSize.width*nCount,oSize.height));
    
	return true;
}

int CCCGameScrollView::getCurPage()
{
	return abs(getContentOffset().x / (int)m_CellSize.width);
}