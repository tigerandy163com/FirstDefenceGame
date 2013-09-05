//
//  LoadLevelInfo.h
//  AA
//
//  Created by chunyu.wang on 13-9-5.
//
//

#ifndef __AA__LoadLevelInfo__
#define __AA__LoadLevelInfo__

#include "cocos2d.h"
using namespace cocos2d;
#define NEEDTOLOADIMAGES "needtoloadimages"
#define LEVELPARAMETER "levelparameter"
#define MASTERS "master"
class LoadLevelinfo: public CCObject
{
public:
    //构造函数
    LoadLevelinfo();
    ~LoadLevelinfo();
    static LoadLevelinfo * createLoadLevelinfo(const char *plistpath);
    //变更plist
    bool f_SetPlist(const char * plistpath);
    
    //获取关卡信息 根据key
    float f_GetLevelInfo(const char * key);
    //获得tmx瓦片地图文件路径
    const char * f_GetLevelTmxPath(const char * key);
    /*
     获取预加载图片的容器
     读取的plist格式是这个样子滴
     <key>4</key>
     <string>loadingHMenu/111.plist</string>
     <key>3</key>
     <string>levelselectone/themescene2-hd.plist</string>
     <key>2</key>
     <string>levelselectone/stages_bg-hd.plist</string>
     <key>1</key>
     <string>Hmenu/mainscene1-hd.plist</string>
     */
    const char  * f_GetLoadingImages(int key);
    CCDictionary *getMasterByTypeID(int type);
    
    //清空已经读取的字符串
    void f_ClearAll();
    /* data */
private:
    //保存关卡需要预加载的图片
    CCDictionary * s_NeedToLoadImages;
    
    //保存关卡的相关的数值信息
    CCDictionary * s_LevelParameter;
    CCDictionary *s_masters;
private:
    
};
#endif /* defined(__AA__LoadLevelInfo__) */
