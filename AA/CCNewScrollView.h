//
//  CCNewScrollView.h
//  AA
//
//  Created by sven on 13-9-11.
//
//

#ifndef __AA__CCNewScrollView__
#define __AA__CCNewScrollView__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

// 校正滑动动画速度
#define ADJUST_ANIM_VELOCITY 2000

class CCNewScrollViewDelegate
: public cocos2d::extension::CCScrollViewDelegate
{
public:
    //初始化每个单独Page的回调
    virtual bool scrollViewInitPage(cocos2d::CCNode* pPage,int nPage)=0;
    //点击一个Page的回调
    virtual void scrollViewClick(const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )=0;
    //每一次切换Page的回调
    virtual void scrollViewScrollEnd(cocos2d::CCNode * pPage,int nPage)=0;
};

class CCCGameScrollView
: public cocos2d::extension::CCScrollView
{
public:
    CCCGameScrollView();
    ~CCCGameScrollView();
public:
    CREATE_FUNC(CCCGameScrollView);
    
    bool init();
    
    bool createContainer(CCNewScrollViewDelegate* pDele, int nCount,const cocos2d::CCSize & oSize );
    
    virtual bool ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );
    
    virtual void ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );
    
    virtual void ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );
    
    virtual void ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );
    
    void scrollToPage(int nPage);
    void scrollToNextPage();
    void scrollToPrePage();
    
    int getCurPage();
protected:
    void adjustScrollView(const cocos2d::CCPoint& oBegin,const cocos2d::CCPoint & oEnd);
    
    virtual void onScrollEnd(float fDelay);
protected:
    int m_nPageCount;
    int m_nPrePage;
    cocos2d::CCPoint m_BeginOffset;
    cocos2d::CCSize m_CellSize;
    float m_fAdjustSpeed;
};

#endif /* defined(__AA__CCNewScrollView__) */
