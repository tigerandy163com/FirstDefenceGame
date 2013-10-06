//
//  LoadLevelInfo.cpp
//  AA
//
//  Created by chunyu.wang on 13-9-5.
//
//

#include "LoadLevelInfo.h"

//
//
#include "LoadLevelinfo.h"
LoadLevelinfo::LoadLevelinfo()
{
}
LoadLevelinfo::~LoadLevelinfo()
{
    
    //TODO： 安全删除s_arr
    //f_ClearAll();
    // CC_SAFE_RELEASE(s_LevelParameter);
    // CC_SAFE_RELEASE(s_NeedToLoadImages);
}
LoadLevelinfo *LoadLevelinfo::createLoadLevelinfo(const char *plistpath)
{
    LoadLevelinfo *pRet = new LoadLevelinfo();
    if (pRet && pRet->f_SetPlist(plistpath))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
//变更plist
bool LoadLevelinfo::f_SetPlist(const char *plistpath)
{
    
    bool bRet = false;
    do
    {
        /* code */
        // if (s_LevelParameter != NULL && s_NeedToLoadImages != NULL)
        // f_ClearAll();
        //创建一个实力
        CCDictionary *ccd = CCDictionary::createWithContentsOfFile(plistpath);
        CC_BREAK_IF(!ccd);
        //进入关卡所需加载图片资源的节点
        s_NeedToLoadImages = dynamic_cast<CCDictionary *>(ccd->objectForKey(NEEDTOLOADIMAGES));
        CC_BREAK_IF(!s_NeedToLoadImages);
        //进入关卡所需信息节点
        s_LevelParameter = dynamic_cast<CCDictionary *>(ccd->objectForKey(LEVELPARAMETER));
        CC_BREAK_IF(!s_LevelParameter);
        
        s_masters =  dynamic_cast<CCDictionary *>(ccd->objectForKey(MASTERS));
        //You need to remove : 输出调试信息
        CCLog("Needtoloadimages count is : %d", s_NeedToLoadImages->count());
        CCLog("levelparameter count is : %d", s_LevelParameter->count());
        bRet = true;
    }
    while (0/* condition */);
    return bRet;
}
//清空已经读取的字符串
void LoadLevelinfo::f_ClearAll()
{
    s_NeedToLoadImages->removeAllObjects();
    s_LevelParameter->removeAllObjects();
    s_masters->removeAllObjects();
}
//获取关卡信息 根据key
float LoadLevelinfo::f_GetLevelInfo(const char *key)
{
    CCString * temp =   dynamic_cast<CCString*>(s_LevelParameter->objectForKey(key));
    return temp->floatValue();
}
const char * LoadLevelinfo::f_GetLevelTmxPath(const char * key)
{
    CCString * temp =   dynamic_cast<CCString*>(s_LevelParameter->objectForKey(key));
    return temp->getCString();
    
}
//获取预加载图片的容器
const char  *LoadLevelinfo::f_GetLoadingImages(int key)
{
    CCString * pString  = CCString ::createWithFormat("%d",key);
    CCString * temp =   dynamic_cast<CCString*>(s_NeedToLoadImages->objectForKey(pString->getCString()));
    return temp->getCString();
}
CCDictionary *LoadLevelinfo::getMasterByTypeID(int type){
    CCString * pString  = CCString ::createWithFormat("%d",type);
    CCDictionary * temp =   dynamic_cast<CCDictionary*>(s_masters->objectForKey(pString->getCString()));
    return temp;
}