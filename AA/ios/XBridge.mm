//
//  XBridgeViewController.cpp
//  xbridge
//
//  Created by diwwu on 5/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "XBridge.h"
#include "AppController.h"
#include "RootViewController.h"
#include "XBridgeTableViewController.h"
#import "InfiniteScrollPicker.h"
#import "MapSelViewController.h"
#import "StartScene.h"
#import "GameMediator.h"
using namespace cocos2d;

void XBridge::doSth() {
    id sth = [[UIApplication sharedApplication] delegate];
    if ([sth isKindOfClass:[AppController class]]) {
        NSMutableArray *set1 = [[NSMutableArray alloc] init];
        for (int i = 1; i <= 6; i++) {
            [set1 addObject:[UIImage imageNamed:[NSString stringWithFormat:@"map%d.png", i]]];
        }
//       InfiniteScrollPicker* isp = [[InfiniteScrollPicker alloc] initWithFrame:CGRectMake(0, 0, 480, 200)];
//        [isp setItemSize:CGSizeMake(160, 160)];
//        [isp setImageAry:set1];
//        
//        [set1 release];
//        [isp setTag:1015];
//        AppController *controller = (AppController *)sth;
//        [controller.viewController.view addSubview:isp];
//
        MapSelViewController *mapSelViewController = [[MapSelViewController alloc] initWithNibName:@"MapSelViewController" bundle:nil];
        [mapSelViewController.view setFrame:CGRectMake(-480, 0, mapSelViewController.view.frame.size.width, mapSelViewController.view.frame.size.height)];
        [mapSelViewController.view setTag:1015];
        AppController *controller = (AppController *)sth;
        
        [controller.viewController.view addSubview:mapSelViewController.view];
        [UIView animateWithDuration:1.0f delay:0.0 options:UIViewAnimationCurveEaseIn
                         animations:^{
                              [mapSelViewController.view setFrame:CGRectMake(0, 0, mapSelViewController.view.frame.size.width, mapSelViewController.view.frame.size.height)];
                         }completion:^(BOOL finished){
                            
                         }];
//                [UIView beginAnimations:nil context:nil];
//                [UIView setAnimationDelay:1.0f];
//                [UIView setAnimationCurve:UIViewAnimationCurveEaseInOut];
//                [mapSelViewController.view setFrame:CGRectMake(0, 0, mapSelViewController.view.frame.size.width, mapSelViewController.view.frame.size.height)];
//                [UIView commitAnimations];
//
    }
}
void XBridge::tobackground(){
    id sth = [[UIApplication sharedApplication] delegate];
    AppController *controller = (AppController *)sth;
    for (UIView *view in controller.viewController.view.subviews) {
        if (view.tag==1015) {
            [controller.viewController.view sendSubviewToBack:view];
            break;
        }
    }
}
void XBridge::tofront(){
    id sth = [[UIApplication sharedApplication] delegate];
    AppController *controller = (AppController *)sth;
    for (UIView *view in controller.viewController.view.subviews) {
        if (view.tag==1015) {
            [controller.viewController.view bringSubviewToFront:view];
            break;
        }
    }
}
void XBridge::setCurMap(int cur){

    GameMediator::sharedMediator()->setCurMapID(cur);

   
}
int XBridge::getCurMap(){
  return   GameMediator::sharedMediator()->getCurMapID();
}
void XBridge::startGameWithMap(){
    XBridge::clearmy(false);
    StartScene *nowscene = (StartScene*)CCDirector::sharedDirector()->getRunningScene();
    nowscene->startGame();
}
void XBridge::clearmy(bool animate){
    id sth = [[UIApplication sharedApplication] delegate];
      AppController *controller = (AppController *)sth;
    for (UIView *view in controller.viewController.view.subviews) {
        if (view.tag==1015) {
            if (animate) {
                [UIView animateWithDuration:1.0f delay:0.0 options:UIViewAnimationCurveEaseOut
                                 animations:^{
                                     [view setFrame:CGRectMake(-480, 0,view.frame.size.width, view.frame.size.height)];
                                 }completion:^(BOOL finished){
                                     [view removeFromSuperview];
                                 }];
            }else
                [view removeFromSuperview];
//            [UIView beginAnimations:nil context:nil];
//            [UIView setAnimationDelay:1.0f];
//            [UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
//            [view setFrame:CGRectMake(-480, 0,view.frame.size.width, view.frame.size.height)];
//             [view removeFromSuperview];
//            [UIView commitAnimations];

           
            break;
        }
    }
}