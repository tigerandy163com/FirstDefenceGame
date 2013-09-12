//
//  SelectLevel.h
//  AA
//
//  Created by chunyu.wang on 13-9-12.
//
//

#ifndef __AA__SelectLevel__
#define __AA__SelectLevel__

#include <iostream>
#include "CCNewScrollView.h"

class CLevelSelectLayer
: public cocos2d::CCLayer
, public CCNewScrollViewDelegate{
public:
    CCCGameScrollView* m_ScrollView;
    cocos2d::CCArray* dataArr;
    virtual bool init();
    ~CLevelSelectLayer();
    void onEnter();
    void onExit();
    bool m_bTouchedMenu;
    CREATE_FUNC(CLevelSelectLayer);
    
    virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView* view );
    
    virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView* view );
    
    virtual bool scrollViewInitPage( cocos2d::CCNode* pPage,int nPage );
    
    virtual void scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage );
    
    virtual void scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage );
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};
#endif /* defined(__AA__SelectLevel__) */
