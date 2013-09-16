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
using namespace cocos2d;

void XBridge::doSth() {
    id sth = [[UIApplication sharedApplication] delegate];
    if ([sth isKindOfClass:[AppController class]]) {
        NSMutableArray *set1 = [[NSMutableArray alloc] init];
        for (int i = 1; i <= 6; i++) {
            [set1 addObject:[UIImage imageNamed:[NSString stringWithFormat:@"map%d.png", i]]];
        }
       InfiniteScrollPicker* isp = [[InfiniteScrollPicker alloc] initWithFrame:CGRectMake(0, 0, 480, 200)];
        [isp setItemSize:CGSizeMake(160, 160)];
        [isp setImageAry:set1];
        [set1 release];
        AppController *controller = (AppController *)sth;
        [controller.viewController.view addSubview:isp];
//        
//        XBridgeTableViewController *tempTableViewController = [[XBridgeTableViewController alloc] initWithNibName:nil bundle:nil];        
//        tempTableViewController.tableView.frame = CGRectMake(100, 100, 200, 100);
//        AppController *controller = (AppController *)sth;
//        [controller.viewController.view addSubview:tempTableViewController.tableView];
    }
}
