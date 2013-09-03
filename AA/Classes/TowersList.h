//
//  TowersList.h
//  MyTowerDefense2D
//
//  Created by chunyu.wang on 13-8-21.
//
//

#ifndef __MyTowerDefense2D__TowersList__
#define __MyTowerDefense2D__TowersList__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class TowersList:public cocos2d::CCLayerColor,public cocos2d::extension::CCTableViewDataSource,public cocos2d::extension::CCTableViewDelegate{
    public:
    virtual bool init();
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
    
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view);
    
    
    //处理触摸事件，可以计算点击的是哪一个子项
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    
    //每一项的宽度和高度
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    
    //生成列表每一项的内容
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    
    //一共多少项
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void okMenuItemCallback(CCObject *pSender);
    void cancelMenuItemCallback(CCObject *pSender);
    
    void initDialog();
    CCTableView* pTableView;
    CCMenu* m_pMenu;
    cocos2d::CCArray* towersInfos;
    cocos2d::CCArray* towersImages;
    bool m_bTouchedMenu;
    CREATE_FUNC(TowersList);
};
#endif /* defined(__MyTowerDefense2D__TowersList__) */
