//
//  GameOverLayer.cpp
//  AA
//
//  Created by chunyu.wang on 13-9-5.
//
//

#include "GameOverLayer.h"
USING_NS_CC;
GameOverLayer::GameOverLayer(){
    
}

GameOverLayer::~GameOverLayer(){
    
}

bool GameOverLayer::init(){
    bool Rbool = false;

    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)));
        //CCLabelBMFont *font = CCLabelBMFont::create("Game Over" , <#const char *fntFile#>)
        Rbool = true;
    } while (0);
    
    return Rbool;
}