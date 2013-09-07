//
//  DataParserBase.cpp
//  AA
//
//  Created by sven on 13-9-6.
//
//

#include "DataParserBase.h"

#include<fstream>
USING_NS_CC;
using namespace std;

DataParserBase::~DataParserBase(){
    keyVec.~vector<string>();
    mapinfo.~map();
     
}
DataParserBase* DataParserBase::creat(const char* path){
    DataParserBase *parser = DataParserBase::create();
    parser->initWithFile(path);
    return parser;
}
bool DataParserBase::init(){
    
    bool bret =false;
    do {
        bret = true;
    } while (0);
    return bret;
}

bool DataParserBase::initWithFile(const char *path){
    
    if (!init()) {
        return false;
    }
     string fullpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(path);

    ifstream readfile;
    string linestr;
    
    readfile.open(fullpath.c_str(),ios::in);
    if(!readfile)
    {
        return false; /*没有打开该文件*/
    }
    mapinfo.clear();
    keyVec.clear();
    vector<string>contentVec;
    
    string key;
    
    
    while (!readfile.eof()&&!readfile.fail()) {
        getline(readfile,linestr);
        
        string::size_type index =linestr.find_first_of("#");
        if (index!=-1) {
            linestr = linestr.substr(0,index);
        }
        index = linestr.find_first_of("=",0);
        if (index!=-1) {
            key = linestr.substr(0,index);
            
            keyVec.push_back(key);
            
        }else {
        index = linestr.find_first_of("(",0);
            int tempindex = linestr.find_last_of(")");
            if (index!=-1&&tempindex!=-1) {
                linestr = linestr.substr(index+1,tempindex-index-1);
                contentVec.push_back(linestr) ;
                
                
            }
        }
        if (linestr.find_first_of(")")==0) {
            mapinfo[key]=contentVec;
            contentVec.clear();
        }
        
    }
    readfile.close();
    return true;
}

CCSprite* DataParserBase::FrameSpriteFromFile(const char* _key,const char* name){
 
    CCSpriteFrame *frame = SpriteFrameFromFile(_key, name);
    CCSprite *sprite = CCSprite::createWithSpriteFrame(frame);
    return sprite;
}
CCSprite* DataParserBase::FrameSpriteFromFile(const char* _key,int _index){
    
    CCSpriteFrame *frame = SpriteFrameFromFile(_key, _index);
    CCSprite *sprite = CCSprite::createWithSpriteFrame(frame);
    return sprite;
}

CCSpriteFrame* DataParserBase::SpriteFrameFromFile(const char* _key,int _index){
    map<string, string>spriteMap;
    vector<string> temp =mapinfo[_key];
    if (temp.size()<_index) {
        return NULL;
    }
    vector<string>content;
    
    string tempstr = temp[_index-1];
    FrameSprite tempFrameSprite;
    int index;
    while ((index = tempstr.find_first_of(" "))!=-1) {
        
        string tempstr1 = tempstr.substr(0,index);
        content.push_back(tempstr1);
        tempstr = tempstr.substr(index+1);
    }
    content.push_back(tempstr);
    tempFrameSprite.index =atoi(content[0].c_str()) ;
    tempFrameSprite.name = content[1].c_str();
    tempFrameSprite.fileName = content[2].c_str();
    tempFrameSprite.rect = CCRect(atoi(content[3].c_str()), atoi(content[4].c_str()), atoi(content[5].c_str()), atoi(content[6].c_str()));
    char file[100];
    strcpy(file, tempFrameSprite.fileName);
    strcat(file, ".png");
    
    CCTexture2D* texture =CCTextureCache::sharedTextureCache()->textureForKey(file);
    CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture, tempFrameSprite.rect);
    return frame;
}
CCSpriteFrame* DataParserBase::SpriteFrameFromFile(const char* _key,const char* name){
    map<string, string>spriteMap;
    vector<string> temp =mapinfo[_key];
    vector<string> content;
    FrameSprite tempFrameSprite;
    vector<string>::iterator piter;
    for (piter=temp.begin(); piter!=temp.end(); piter++) {
        string tempstr = *piter;
        if (tempstr.find(name)!=-1) {
            int index = 0;
            while ((index = tempstr.find_first_of(" "))!=-1) {
                
                string tempstr1 = tempstr.substr(0,index);
                content.push_back(tempstr1);
                tempstr = tempstr.substr(index+1);
                
                
            }
            content.push_back(tempstr);
            break;
        }
    }
    tempFrameSprite.index =atoi(content[0].c_str()) ;
    tempFrameSprite.name = content[1].c_str();
    tempFrameSprite.fileName = content[2].c_str();
    tempFrameSprite.rect = CCRect(atoi(content[3].c_str()), atoi(content[4].c_str()), atoi(content[5].c_str()), atoi(content[6].c_str()));
    char file[100];
    strcpy(file, tempFrameSprite.fileName);
    strcat(file, ".png");
    
    CCTexture2D* texture =CCTextureCache::sharedTextureCache()->textureForKey(file);
    return  CCSpriteFrame::createWithTexture(texture, tempFrameSprite.rect);
}
CCAnimation* DataParserBase::animateFromFile(const char* _key,const char* name,const char* key2){
    map<string, string>spriteMap;
    vector<string> temp =mapinfo[_key];
    vector<string> content;
    AnimateInfo tempAnimateInfo;
    vector<string>::iterator piter;
    for (piter=temp.begin(); piter!=temp.end(); piter++) {
        string tempstr = *piter;
        if (tempstr.find(name)!=-1) {
            int index = 0;
            while ((index = tempstr.find_first_of(" "))!=-1) {
                
                string tempstr1 = tempstr.substr(0,index);
                content.push_back(tempstr1);
                tempstr = tempstr.substr(index+1);
                
                
            }
            content.push_back(tempstr);
            break;
        }
    }
    tempAnimateInfo.name =content[0].c_str();
    tempAnimateInfo.FrameCount = atoi(content[1].c_str()) ;
    int i = 0;
    for (piter=content.begin()+2; piter!=content.end(); piter++) {
        tempAnimateInfo.index[i] = atoi((*piter).c_str());
    }

    CCArray *frameArr = CCArray::create();
    for (i=0; i<tempAnimateInfo.FrameCount; i++) {
        CCSpriteFrame *frame = this->SpriteFrameFromFile(key2, tempAnimateInfo.index[i]);
        frameArr->addObject(frame);
    }
    CCAnimation *animation=CCAnimation::createWithSpriteFrames(frameArr);
    return animation;
}
