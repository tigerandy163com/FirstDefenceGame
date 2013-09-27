//
//  MapsList.h
//  MyTowerDefense2D
//
//  Created by sven on 13-8-31.
//
//

#ifndef __MyTowerDefense2D__MapsList__
#define __MyTowerDefense2D__MapsList__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "PopUpLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
class MapsList:public cocos2d::CCLayerColor,public cocos2d::extension::CCTableViewDataSource,public cocos2d::extension::CCTableViewDelegate{
private:
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
    
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    CC_SYNTHESIZE_RETAIN(PopupLayer*, pl,PopUpLayer);
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void okMenuItemCallback(CCObject *pSender);
    void cancelMenuItemCallback(CCObject *pSender);
    float lastpos;
    void initDialog();
    void popupLayer();
    void buttonCallback(cocos2d::CCNode *pNode);
    void removePop();
    
    CCTableView* pTableView;
    CCMenu* m_pMenu;
    CCMenu *menu;
    cocos2d::CCArray* mapsInfos;
    cocos2d::CCArray* mapsImages;
    bool m_bTouchedMenu;
    CCLayer *poplayer;
public:
    CREATE_FUNC(MapsList);
    
};
#endif /* defined(__MyTowerDefense2D__MapsList__) */
