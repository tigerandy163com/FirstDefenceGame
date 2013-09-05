//
//  LoadingLayer.h
//  AA
//
//  Created by chunyu.wang on 13-9-5.
//
//

#ifndef __AA__LoadingLayer__
#define __AA__LoadingLayer__

#include <iostream>
#include "cocos2d.h"

class LoadingLayer:public cocos2d::CCLayer{
public:
    LoadingLayer();
    ~LoadingLayer();

virtual bool init();
static  cocos2d::CCScene*   scene();
static  cocos2d::CCScene*   scene(int lev);
static LoadingLayer* creat(int Lev);
static LoadingLayer* creat();
bool initWithLevel(int lev);
int currentCount;
int totalCount;
void loadingCallBack(cocos2d::CCObject* psender);
void startGame();
cocos2d::CCProgressTimer* process;
};
#endif /* defined(__AA__LoadingLayer__) */
