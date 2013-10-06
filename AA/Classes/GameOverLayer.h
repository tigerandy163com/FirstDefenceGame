//
//  GameOverLayer.h
//  AA
//
//  Created by chunyu.wang on 13-9-5.
//
//

#ifndef __AA__GameOverLayer__
#define __AA__GameOverLayer__

#include <iostream>
#include "cocos2d.h"
class GameOverLayer:public cocos2d::CCLayerColor{
public:
    GameOverLayer();
    ~GameOverLayer();
    virtual bool init();
    CREATE_FUNC(GameOverLayer);
    
};

#endif /* defined(__AA__GameOverLayer__) */
