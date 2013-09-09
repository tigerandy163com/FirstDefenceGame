//
//  MainLayer.cpp
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#include "MainLayer.h"
#include "TileData.h"
#include "GameMediator.h"
#include "GameHUD.h"
#include "Tower.h"
#include "Enemy.h"
#include "Wave.h"
#include "ProjectTile.h"
#include "Lightning.h"
#include "StartScene.h"
#include "data.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

MainLayer::~MainLayer(){
	CC_SAFE_RELEASE_NULL(tileDataArray);
}

CCScene* MainLayer::scene()
{
	CCScene * scene = NULL;
	do
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
        
		// 'layer' is an autorelease object
		MainLayer *layer = MainLayer::create();
		CC_BREAK_IF(! layer);
        
		// add layer as a child to scene
		scene->addChild(layer);
        
		GameHUD* myGameHUD = GameHUD::sharedHUD();
		scene->addChild(myGameHUD, 2);
        
		GameMediator* m = GameMediator::sharedMediator();
		m->setGameLayer(layer);
		m->setGameHUDLayer(myGameHUD);
        
	} while (0);
    
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainLayer::init()
{
	bool bRet = false;
	do
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
        
		CC_BREAK_IF(! CCLayer::init());
        
		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
        //打开pvr支持
        CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
        //添加到帧序列中
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("enemy.plist");
        //通过一个镇图片生产精灵

        
		this->setTouchEnabled(true);
        
//	background = CCSprite::create("map.jpg");
//		background->setAnchorPoint(ccp(0,0));
//		background->setPosition(CCPointZero);
//		this->addChild(background);
  
		createTileMap();
        
		gameHUD = GameHUD::sharedHUD();
         
		currentLevel = 0;
		addWaves();
        
		m_emitter = CCParticleRain::create();
		//m_emitter->retain();
		this->addChild(m_emitter, 10);
		m_emitter->setLife(4);
        
		m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png") );
        
		Lightning* l = Lightning::create(ccp(160,maxHeight), ccp(200, 20));
		l->setVisible(false);
		this->addChild(l, 1, 999);
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("battle1.wav", true);
        this->schedule(schedule_selector(MainLayer::strikeLight), 5.0f,kCCRepeatForever,3.0f);
        
        this->schedule(schedule_selector(MainLayer::gameLogic), 0.1f, kCCRepeatForever,5.0f);
		bRet = true;
	} while (0);
    
	return bRet;
}
//void MainLayer::onEnter(){
//
//}
void MainLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	
}

void MainLayer::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
	CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
	CCPoint touchPoint = pTouch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);
    
	CCPoint oldPoint = pTouch->getPreviousLocationInView();
	oldPoint = CCDirector::sharedDirector()->convertToGL(oldPoint);
    
	CCPoint translation = ccpSub(touchPoint, oldPoint);
	CCPoint newPos = ccpAdd(this->getPosition(), translation);
	CCPoint oldPos = this->getPosition();
	this->setPosition(boundLayerPos(newPos));
    
	m_emitter->setPosition(ccpSub(m_emitter->getPosition(), ccpSub(boundLayerPos(newPos), oldPos)));
}

void MainLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    
}


CCPoint MainLayer::boundLayerPos(cocos2d::CCPoint newPos){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint retval = newPos;
	retval.x = MIN(retval.x, 0);
	retval.x = MAX(retval.x, -mapsize.width+winSize.width);
	retval.y = MIN(0, retval.y);
	retval.y = MAX(-mapsize.height+winSize.height, retval.y);
	return retval;
}

void MainLayer::createTileMap(){
	tileDataArray = CCArray::create();
	tileDataArray->retain();
    wayTilesArr = CCArray::create();
    wayTilesArr ->retain();
    totolWays = CCArray::create();
    totolWays->retain();
    dirChangeArr=CCArray::create();
    dirChangeArr->retain();
    CCLog("%s",GameMediator::sharedMediator()->getCurMapName()->getCString());
    gameMap = CCTMXTiledMap::create(GameMediator::sharedMediator()->getCurMapName()->getCString());
    
  //  CCSize wSize = CCDirector::sharedDirector()->getWinSize();
    this->mapsize = gameMap->getContentSize();
    mapRect = CCRectMake(0, 0, mapsize.width, mapsize.height);
   // float scale = wSize.height/mapsize.height;
   // gameMap->setScale(scale);
    gameMap->setPosition(0,0);
    
    _bg1layer = gameMap->layerNamed("bg1");
    _objects = gameMap->objectGroupNamed("Objects");
    
    //CCPoint tankPoint=this->objectPosition(_objects, "pl1");
    
    this->addChild(gameMap,0);
    CCSize tile = gameMap->getTileSize();
    this->tileSize = tile;
    maxWidth = mapsize.width - tile.width - tile.width * 0.5f;
    maxHeight = mapsize.height - tile.height * 2- tile.height * 0.5f;
    CCSize map = gameMap->getMapSize();
	maxTileWidth = map.width;
	maxTileHeight = map.height;
    
	for(int i = 0; i < maxTileWidth; i++){
		for(int j = 0; j < maxTileHeight; j++){
			TileData* td = TileData::create(ccp(i, j));
            int gid = _bg1layer->tileGIDAt(ccp(i,j));
            CCDictionary *dic = gameMap->propertiesForGID(gid);
            
            if  (dic!=NULL&&dic->valueForKey("way")->intValue()==1) {
                CCLOG("way tile pos:%d,%d",i,j);
                td->setisWay(true);
                totolWays->addObject(td);
            }
            td->isThroughing = false;
			tileDataArray->addObject(td);
		}
	}
    this->getWayTiles();
}
CCPoint MainLayer::objectPosition(CCTMXObjectGroup *group,const char *object){
    CCPoint point;
    CCDictionary *groupdic  = group->objectNamed(object);
    point.x = groupdic->valueForKey("x")->intValue()+tileSize.width/2;
    point.y =  groupdic->valueForKey("y")->intValue()+tileSize.height/2;
    return point;
}
//触摸点坐标转化成地图上的坐标点
CCPoint MainLayer::tileCoordinateFromPosition(CCPoint pos)
{
    
    int cox,coy;
    
    
    CCSize szLayer=_bg1layer->getLayerSize();
    
    CCSize szTile=gameMap->getTileSize();
    
    cox = pos.x / szTile.width;
    //与地图坐标相反，所以减
    coy = szLayer.height - pos.y / szTile.height;
    
    if ((cox >=0) && (cox < szLayer.width) && (coy >= 0) && (coy < szLayer.height)) {
        
        
        return  ccp(cox,coy);
    }else {
        
        return ccp(-1,-1);
    }
    
}


//将地图坐标点转换成瓦片值
int MainLayer::tileIDFromPosition(CCPoint pos)
{
    CCPoint cpt = this->tileCoordinateFromPosition(pos);
    if (cpt.x < 0) return  -1;
    if (cpt.y < 0) return -1;
    if (cpt.x >= _bg1layer->getLayerSize().width) return -1;
    if (cpt.y >= _bg1layer->getLayerSize().height) return -1;
    
    
    return _bg1layer->tileGIDAt(cpt);
    
}

CCPoint MainLayer::tileCoordForPosition(cocos2d::CCPoint position){
	int x, y;
	if(position.x < TILE_WIDTH){
		x = 0;
	}else if(position.x > maxWidth){
		x = maxTileWidth - 1;
	}else{
		x = (position.x - TILE_WIDTH) / TILE_WIDTH;
	}
    
	if(position.y < TILE_HEIGHT * 2){
		y = 0;
	}else if(position.y > maxHeight){
		y = maxTileHeight - 1;
	}else{
		y = (position.y - TILE_HEIGHT * 2) / TILE_HEIGHT;
	}
    
	return ccp(x, y);
}

CCPoint MainLayer::positionForTileCoord(cocos2d::CCPoint position){
	float x, y;
    CCSize size = gameMap->getTileSize();
    CCSize map = gameMap->getContentSize();
	x =  position.x * size.width  + size.width  * 0.5f;
	y = map.height - position.y * size.height - size.height * 0.5f;
    
	return ccp(x, y);
}

bool MainLayer::canBuildOnTilePosition(cocos2d::CCPoint pos){
	//pos = ccpAdd(pos, ccp(0, 20));
	CCPoint towerLoc = this->tileCoordinateFromPosition(pos);
    if (isOutOfMap(pos)) {
        return false;
    }
//	if(towerLoc.equals(ccp(0, maxTileHeight / 2)) ||
//       towerLoc.equals(ccp(maxTileWidth  - 1, maxTileHeight / 2))){
//        return false;
//	}
//    
	TileData* td = getTileData(towerLoc);
	if(td->getIsUsed() || td->getIsThroughing()){
		return false;
	}
    return true;
//	bool canBuild = false;
//	for(int y =0; y < maxTileHeight; y++){
//		if(y == towerLoc.y)
//			continue;
//		TileData* t = getTileData(ccp(towerLoc.x, y));
//		if(t->getIsUsed() == false){
//			canBuild = true;
//			break;
//		}
//	}
//    
//	return canBuild;
}

TileData* MainLayer::getTileData(CCPoint tileCoord){
	CCObject* temp;
	CCARRAY_FOREACH(tileDataArray, temp){
		TileData* td = (TileData*)temp;
        if (td->getPosition().equals(tileCoord)) {
            return td;
        }
//		if(CCPoint::CCPointEqualToPoint(td->getPosition(), tileCoord)){
//			return td;
//		}
	}
	return NULL;
}
TileData* MainLayer::getTileDataForPositon(cocos2d::CCPoint tilepositon){
    CCPoint tilecoord = this->tileCoordForPosition(tilepositon);
    return this->getTileData(tilecoord);
}
void MainLayer::addTower(CCPoint pos, int towerTag){
	//pos = ccpAdd(pos, ccp(0, 30));
	GameMediator* m = GameMediator::sharedMediator();
	Tower* target = NULL;
	CCPoint towerLoc = this->tileCoordinateFromPosition(pos);
    
	
	if(canBuildOnTilePosition(pos)){
		switch(towerTag){
            case 1:
                if(gameHUD->getResources() >= 25){
                    target = MachineGunTower::create();
                    gameHUD->updateResources(-25);
                }else{
                    return;
                }
                
                break;
            case 2:
                if(gameHUD->getResources() >= 30){
                    target = FreezeTower::create();
                    gameHUD->updateResources(-30);
                }else{
                    return;
                }
                break;
            case 3:
                if(gameHUD->getResources() >= 40){
                    target = CannonTower::create();
                    gameHUD->updateResources(-40);
                }else{
                    return;
                }
                break;
            case 4:
                if(gameHUD->getResources() >= 60){
                    target = MutilTower::create();
                    gameHUD->updateResources(-60);
                }else{
                    return;
                }
                break;
            default:
                break;
		}
		//target->setPosition(positionForTileCoord(towerLoc));
        
        CCPoint newPos = positionForTileCoord(towerLoc);
        target->setPosition(newPos);
		this->addChild(target, 5);
        
		m->getTowers()->addObject(target);
        
		TileData* td = getTileData(towerLoc);
		td->setIsUsed(true);
	}
}

CCDictionary* MainLayer::getTilesNextToTile(cocos2d::CCPoint tileCoord){
	CCDictionary* tiles = CCDictionary::create();
    if(tileCoord.y - 1 >= 0){
		tiles->setObject(CCString::createWithFormat("{%f, %f}", tileCoord.x, tileCoord.y - 1),"up");
	}
    if(tileCoord.x - 1 >= 0){
		tiles->setObject(CCString::createWithFormat("{%f, %f}", tileCoord.x - 1, tileCoord.y),"left");
	}
	if(tileCoord.y + 1 < maxTileHeight){
		tiles->setObject(CCString::createWithFormat("{%f, %f}", tileCoord.x, tileCoord.y + 1),"down");
	}
    if(tileCoord.x + 1 < maxTileWidth){
		tiles->setObject(CCString::createWithFormat("{%f, %f}", tileCoord.x + 1, tileCoord.y),"right");
	}
//    if(tileCoord.y + 1 < maxTileHeight&&tileCoord.x + 1 < maxTileWidth)
//    tiles->addObject(CCString::createWithFormat("{%f, %f}", tileCoord.x + 1, tileCoord.y+1));
//    if(tileCoord.y - 1 >= 0&&tileCoord.x + 1 < maxTileWidth)
//    tiles->addObject(CCString::createWithFormat("{%f, %f}", tileCoord.x + 1, tileCoord.y-1));
//    if(tileCoord.y + 1 < maxTileHeight&&tileCoord.x - 1 >=0)
//    tiles->addObject(CCString::createWithFormat("{%f, %f}", tileCoord.x - 1, tileCoord.y+1));
//    if(tileCoord.y - 1 >=0&&tileCoord.x - 1 >=0)
//    tiles->addObject(CCString::createWithFormat("{%f, %f}", tileCoord.x - 1, tileCoord.y-1));
	return tiles;
}
bool MainLayer::isexit(TileData *tile){
    bool ret = false;
    CCObject *obj;
    CCARRAY_FOREACH(totolWays, obj){
        TileData *obj1 = (TileData *)obj;
        if (obj1->getPosition().equals(tile->getPosition())) {
            ret = true;
            break;
        }
    }
    return ret;
}
void MainLayer::getWayTiles(){
    CCPoint star;
    TileData *tile;
    bool next = true;
    star =  this->objectPosition(_objects, "pl1");
    CCPoint pos = this->tileCoordinateFromPosition(star);
    HeroDirection orignDirection = kRight;
     int num=0;
    do {
         CCLOG("pos***%f,%f",pos.x,pos.y);
        tile = this-> getTileData(pos);
        wayTilesArr->addObject(tile);
        tile->isThroughing = true;
        CCDictionary* tiles = this->getTilesNextToTile(pos);
        CCObject* temp;
          CCLOG("ways:%d",tiles->count());
        int ways=0;
        CCArray *dics = tiles->allKeys();
        CCARRAY_FOREACH(dics, temp){
            CCString *str = (CCString*)temp;
            CCString* string =(CCString*)tiles->objectForKey(str->getCString());
            
            CCPoint tileCoord = CCPointFromString(string->getCString());
            CCLOG("pos::::%f,%f",tileCoord.x,tileCoord.y);
            TileData* _neighbourTile = this->getTileData(tileCoord);
            
            if(!_neighbourTile->getIsThroughing()&&_neighbourTile->getisWay()){
                if (isexit(_neighbourTile)) {
                ways++;
                HeroDirection dir = this->directionFor(str);
                    if (dir!=orignDirection) {
                        num++;
                        orignDirection = dir;
                        _neighbourTile->setDirection(dir);
                        dirChangeArr->addObject(_neighbourTile);       
                    }
                pos = _neighbourTile->getPosition();
                    break;
                }
              //  break;
            }
        }
        if (ways<=0) {
            next = false;
        }
    } while (next);
    CCLOG("ways:%d",wayTilesArr->count());
    CCObject* temp;

    num=0;
    CCARRAY_FOREACH(wayTilesArr, temp){
        TileData* hi = (TileData*)temp;
        if (hi->getDirection()!= KUnKnow) {
            num++;
        }
    }
}
HeroDirection MainLayer::directionFor(CCString *cstr){
    HeroDirection ret = KUnKnow;
    if (cstr->compare("left")==0) {
        ret = kLeft;
    }else if (cstr->compare("right")==0)
        ret = kRight;
    else if (cstr->compare("up")==0)
        ret = kUp;
    else if (cstr->compare("down")==0)
        ret = kDown;
    return ret;
}
void MainLayer::addWaves(){
	GameMediator* m = GameMediator::sharedMediator();
    
	Wave* wave = Wave::create(2.0f, 5, 10);
	m->getWaves()->addObject(wave);
	wave = NULL;
    
	wave = Wave::create(1.7f, 10, 15);
	m->getWaves()->addObject(wave);
	wave = NULL;
    
	wave = Wave::create(1.5f, 25, 25);
	m->getWaves()->addObject(wave);
	wave = NULL;
    
	wave = Wave::create(1.3f, 25, 30);
	m->getWaves()->addObject(wave);
	wave = NULL;
    
	wave = Wave::create(1.2f, 30, 30);
	m->getWaves()->addObject(wave);
	wave = NULL;
    
    wave =(Wave*) m->getWaves()->objectAtIndex(0);
}

Wave* MainLayer::getCurrentWave(){
	GameMediator* m = GameMediator::sharedMediator();
	Wave* wave = (Wave*)m->getWaves()->objectAtIndex(currentLevel);
	return wave;
}

Wave* MainLayer::getNextWave(){
	GameMediator* m = GameMediator::sharedMediator();
	currentLevel ++;
    
	if(currentLevel >=5){
		CCLog("you have reached the end of the game!");
		currentLevel = 0;
        this->unscheduleAllSelectors();
        
        CCDirector::sharedDirector()->replaceScene((CCTransitionJumpZoom::create(3.0f, StartScene::scene())));
        return NULL;
	}
	Wave* wave = (Wave*)m->getWaves()->objectAtIndex(currentLevel);
	return wave;
}

void MainLayer::addTarget(){
	GameMediator* m = GameMediator::sharedMediator();
    
	Wave* wave = this->getCurrentWave();
	if(wave->getRedEnemys() == 0 && wave->getGreenEnemys() == 0){
		return;
	}
    CCPoint star =this->objectPosition(_objects, "pl1");
    //star = this->positionForTileCoord(star);
	Enemy* target = NULL;
	if(rand() % 2 == 0){
		if(wave->getRedEnemys() > 0){
			target = FastRedEnemy::create(star);
			wave->setRedEnemys(wave->getRedEnemys() - 1);
		}else if(wave->getGreenEnemys() > 0){
			target = StrongGreenEnemy::create(star);
			wave->setGreenEnemys(wave->getGreenEnemys() - 1);
		}
        
	}else
    {
		if(wave->getGreenEnemys() > 0){
			target = StrongGreenEnemy::create(star);
			wave->setGreenEnemys(wave->getGreenEnemys() - 1);
		}else if(wave->getRedEnemys() > 0){
			target = FastRedEnemy::create(star);
			wave->setRedEnemys(wave->getRedEnemys() - 1);
		}
	}
    target->WayTilesArray->addObjectsFromArray(wayTilesArr);
	this->addChild(target, 1);
	m->getTargets()->addObject(target);
   // target->attack();
}

void MainLayer::gameLogic(float dt){
	GameMediator* m = GameMediator::sharedMediator();
    
	Wave* wave = this->getCurrentWave();
    
	if(m->getTargets()->count() == 0 && wave->getRedEnemys()<= 0 && wave->getGreenEnemys() <= 0){
		if(!this->getNextWave())
            return;
		gameHUD->updateWaveCount();
	}
    
	static long lastTimeTargetAdded = 0;
	long now = millisecondNow();
	if(lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= wave->getSpawnRate() * 1000){
		this->addTarget();
		lastTimeTargetAdded = now;
	}
}

bool MainLayer::isOutOfMap(cocos2d::CCPoint pos){
	if(mapRect.containsPoint(pos)){
		return false;
	}
	return true;
}

void MainLayer::removeTower(Tower* tower){
	GameMediator* gm = GameMediator::sharedMediator();
	gm->getTowers()->removeObject(tower);
    
	CCPoint coordPos = tileCoordForPosition(tower->getPosition());
	TileData* td = getTileData(coordPos);
	td->setIsUsed(false);
    
	this->removeChild(tower, true);
}

void MainLayer::strikeLight(float dt){
	Lightning *l = (Lightning *)this->getChildByTag(999);
    
	srand(time(NULL));
	//random position
	l->setStrikePoint(ccp(20 + CCRANDOM_0_1() * mapsize.width, mapsize.height));
	l->setStrikePoint2(ccp(20 + CCRANDOM_0_1() * mapsize.width, 10));
	l->setStrikePoint3(ccp(20 + CCRANDOM_0_1() * mapsize.width, 10));
    
	//random color
	l->setColor(ccc3(CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255));
    
	//random style
	l->setDisplacement(100 + CCRANDOM_0_1() * 200);
	l->setMinDisplacement(4 + CCRANDOM_0_1() * 10);
	l->setLighteningWidth(2.0f);
	l->setSplit(true);
    
	//call strike
	l->strikeRandom();
}
void MainLayer::onExit(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    GameMediator* gm = GameMediator::sharedMediator();
    gm->clear();
    GameHUD* hud = gameHUD->sharedHUD();
    hud->resetHUD();
}
