//
//  DataParserBase.h
//  AA
//
//  Created by sven on 13-9-6.
//
//

#ifndef __AA__DataParserBase__
#define __AA__DataParserBase__

#include <iostream>
#include<map>
#include "cocos2d.h"
 using namespace std;
typedef struct{
    int index;
    const char* name;
    const char* fileName;
    cocos2d::CCRect rect;
}FrameSprite;
typedef struct{
    const char* name;
    int FrameCount;
    int index[20];
}AnimateInfo;
class DataParserBase:public cocos2d::CCObject{
public:
    ~DataParserBase();
    virtual bool init();
    bool initWithFile(const char* path);
    
    CREATE_FUNC(DataParserBase);
    static DataParserBase* creat(const char* path);
    cocos2d::CCDictionary* dataDic;
    std::string trueName;
    map<string,vector<string> >mapinfo;
    vector<string>keyVec;
    cocos2d::CCSprite* FrameSpriteFromFile(const char* key,const char* name);
    cocos2d::CCSprite* FrameSpriteFromFile(const char* key,int index);
    cocos2d::CCSpriteFrame* SpriteFrameFromFile(const char* key,int index);
    cocos2d::CCSpriteFrame* SpriteFrameFromFile(const char* key,const char* name);
    cocos2d::CCAnimation* animateFromFile(const char* key,const char* name,const char* key2);
};
#endif /* defined(__AA__DataParserBase__) */
