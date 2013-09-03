//
//  StartScene.h
//  MyTowerDefense2D
//
//  Created by sven on 13-8-18.
//
//

#ifndef __MyTowerDefense2D__StartScene__
#define __MyTowerDefense2D__StartScene__

#include <iostream>
#include "cocos2d.h"
class StartScene:public cocos2d::CCLayer{
public:
    ~StartScene();
    virtual bool init();
    static cocos2d::CCScene * scene();
    CREATE_FUNC(StartScene);
    void startGame();
    void gotoTowersList();
    void gotoMapsList();
};
#endif /* defined(__MyTowerDefense2D__StartScene__) */
