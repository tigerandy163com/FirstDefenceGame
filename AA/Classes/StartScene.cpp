//
//  StartScene.cpp
//  MyTowerDefense2D
//
//  Created by sven on 13-8-18.
//
//

#include "StartScene.h"
#include "MainLayer.h"
#include "TowersList.h"
#include "MapsList.h"
#include "PopUpLayer.h"
#include "LoadingLayer.h"
#include "SelectLevel.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "XBridge.h"
#endif
USING_NS_CC;

StartScene::~StartScene(){
    
}

CCScene* StartScene::scene(){
    CCScene *scene = NULL;
    do {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        StartScene *layer = StartScene::create();
        CC_BREAK_IF(!layer);
        scene->addChild(layer);
    } while (0);
    return scene;
}
bool StartScene::init(){
    bool retBool = false;
    do {
        CC_BREAK_IF(! CCLayer::init() );
        CCSize wSize = CCDirector::sharedDirector()->getWinSize();
        CCMenuItemFont *menu = CCMenuItemFont::create("Start Game", this, menu_selector(StartScene::startGame));
        menu->setPosition(wSize.width/2, 200);
        menu->setFontSizeObj(50);
        menu->setFontNameObj("Georgia-Bold");
        CCMenuItemFont *towers = CCMenuItemFont::create("Towers", this, menu_selector(StartScene::gotoTowersList));
        towers->setPosition(menu->getPositionX(), menu->getPositionY()-50-menu->fontSize()/2);
        towers->setFontSizeObj(30);
   
        
        CCMenuItemFont *maps = CCMenuItemFont::create("Maps", this, menu_selector(StartScene::gotoMapsList));
        maps->setPosition(menu->getPositionX(), towers->getPositionY()-50);
        maps->setFontSizeObj(30);
        
        CCMenu *menu1 = CCMenu::create(menu,towers,maps,NULL);
        menu1->setPosition(CCPointZero);
        this->addChild(menu1);
        retBool = true;
    } while (0);
    return retBool;
}
void StartScene::gotoTowersList(){
    TowersList *towers = TowersList::create();
    this->addChild(towers);
}
void StartScene::gotoMapsList(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    XBridge::doSth();
    
#endif
//    MapsList *towers = MapsList::create();
//   this->addChild(towers);
//    CLevelSelectLayer* layer = CLevelSelectLayer::create();
//    this->addChild(layer);
}

void StartScene:: startGame(){
      
    //场景转换
    CCScene *pScene = LoadingLayer::scene();
    
    //跳跃式动画
    CCDirector::sharedDirector()->replaceScene(pScene);
    
    //其他的一些特效
    
    //    CCTransitionFade::transitionWithDuration(t, s);//淡出淡入，原场景淡出，新场景淡入
    //    CCTransitionFade::transitionWithDuration(t, s, ccWHITE);//如果上一个的函数，带3个参数，则第三个参数就是淡出淡入的颜色
    //    CCTransitionFlipX::transitionWithDuration(t, s, kOrientationLeftOver);//x轴左翻
    //    CCTransitionFlipX::transitionWithDuration(t, s, kOrientationRightOver);//x轴右翻
    //    CCTransitionFlipY::transitionWithDuration(t, s, kOrientationUpOver);//y轴上翻
    //    CCTransitionFlipY::transitionWithDuration(t, s, kOrientationDownOver);//y轴下翻
    //    CCTransitionFlipAngular::transitionWithDuration(t, s, kOrientationLeftOver);//有角度转的左翻
    //    CCTransitionFlipAngular::transitionWithDuration(t, s, kOrientationRightOver);//有角度转的右翻
    //    CCTransitionZoomFlipX::transitionWithDuration(t, s, kOrientationLeftOver);//带缩放效果x轴左翻
    //    CCTransitionZoomFlipX::transitionWithDuration(t, s, kOrientationRightOver);//带缩放效果x轴右翻
    //    CCTransitionZoomFlipY::transitionWithDuration(t, s, kOrientationUpOver);//带缩放效果y轴上翻
    //    CCTransitionZoomFlipY::transitionWithDuration(t, s, kOrientationDownOver);//带缩放效果y轴下翻
    //    CCTransitionZoomFlipAngular::transitionWithDuration(t, s, kOrientationLeftOver);//带缩放效果/有角度转的左翻
    //    CCTransitionZoomFlipAngular::transitionWithDuration(t, s, kOrientationRightOver);//带缩放效果有角度转的右翻
    //    CCTransitionShrinkGrow::transitionWithDuration(t, s);//交错换
    //    CCTransitionRotoZoom::transitionWithDuration(t, s);//转角换
    //    CCTransitionMoveInL::transitionWithDuration(t, s);//新场景从左移入覆盖
    //    CCTransitionMoveInR::transitionWithDuration(t, s);//新场景从右移入覆盖
    //    CCTransitionMoveInT::transitionWithDuration(t, s);//新场景从上移入覆盖
    //    CCTransitionMoveInB::transitionWithDuration(t, s);//新场景从下移入覆盖
    //    CCTransitionSlideInL::transitionWithDuration(t, s);//场景从左移入推出原场景
    //    CCTransitionSlideInR::transitionWithDuration(t, s);//场景从右移入推出原场景
    //    CCTransitionSlideInT::transitionWithDuration(t, s);//场景从上移入推出原场景
    //    CCTransitionSlideInB::transitionWithDuration(t, s);//场景从下移入推出原场景
    //    以下三个需要检测opengl版本是否支持CCConfiguration::sharedConfiguration()->getGlesVersion() <= GLES_VER_1_0如果为真则为不支持
    //    CCTransitionCrossFade::transitionWithDuration(t,s);//淡出淡入交叉，同时进行
    //    CCTransitionRadialCCW::transitionWithDuration(t,s);//顺时针切入
    //    CCTransitionRadialCW::transitionWithDuration(t,s);//逆时针切入
    //    以下两个需要先设置摄像机，使用CCDirector::sharedDirector()->setDepthTest(true);
    //    CCTransitionPageTurn::transitionWithDuration(t, s, false);//翻页，前翻
    //    CCTransitionPageTurn::transitionWithDuration(t, s, true);//翻页，后翻
    //    CCTransitionFadeTR::transitionWithDuration(t, s);//向右上波浪
    //    CCTransitionFadeBL::transitionWithDuration(t, s);//向左下波浪
    //    CCTransitionFadeUp::transitionWithDuration(t, s);//向上百叶窗
    //    CCTransitionFadeDown::transitionWithDuration(t, s);//向下百叶窗
    //    CCTransitionTurnOffTiles::transitionWithDuration(t, s);//随机小方块
    //    CCTransitionSplitRows::transitionWithDuration(t, s);//按行切  
    //    CCTransitionSplitCols::transitionWithDuration(t, s);//按列切  
    

}