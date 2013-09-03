//
//  Lightning.cpp
//  MyTowerDefense2D
//
//  Created by su xinde on 13-6-8.
//
//

#include "Lightning.h"
#include <OpenGLES/ES1/gl.h>

using namespace cocos2d;

int getNextRandom(unsigned long *seed)
{
	//taken off a linux site (linux.die.net)
	(*seed) = (*seed) * 1103515245 + 12345;
	return ((unsigned)((*seed)/65536)%32768);
}

cocos2d::CCPoint drawLightning(cocos2d::CCPoint pt1, cocos2d::CCPoint pt2, int displace, int minDisplace, unsigned long randSeed){
	cocos2d::CCPoint mid = ccpMult(ccpAdd(pt1,pt2), 0.5f);
    
	if (displace < minDisplace)
		ccDrawLine(pt1, pt2);
	else
	{
		int r = getNextRandom(&randSeed);
		mid.x += (((r % 101)/100.0)-.5)*displace;
		r = getNextRandom(&randSeed);
		mid.y += (((r % 101)/100.0)-.5)*displace;
        
		drawLightning(pt1,mid,displace/2,minDisplace,randSeed);
		drawLightning(pt2,mid,displace/2,minDisplace,randSeed);
	}
    
	return mid;
}

Lightning* Lightning::create(cocos2d::CCPoint strikePoint){
	Lightning* l = new Lightning;
	if(l && l->initWithStrikePoint(strikePoint)){
		l->autorelease();
		return l;
	}
	CC_SAFE_DELETE(l);
	return NULL;
}

Lightning* Lightning::create(cocos2d::CCPoint strikePoint, cocos2d::CCPoint strikePoint2){
	Lightning* l = new Lightning;
	if(l && l->initWithStrikePoint(strikePoint, strikePoint2)){
		l->autorelease();
		return l;
	}
	CC_SAFE_DELETE(l);
	return NULL;
}

bool Lightning::initWithStrikePoint(cocos2d::CCPoint strikePoint){
	return initWithStrikePoint(strikePoint, ccp(0, 0));
}

bool Lightning::initWithStrikePoint(cocos2d::CCPoint strikePoint, cocos2d::CCPoint strikePoint2){
	_strikePoint = strikePoint;
	_strikePoint2 = strikePoint2;
	_strikePoint3 = ccp(0, 0);
	_color = ccWHITE;
	_opacity = 255;
    
	srand(time(NULL));
	_seed = rand();
	_split = false;
    
	_displacement = 120;
	_minDisplacement = 4;
	_lighteningWidth = 1.0f;
    
	return true;
}

void Lightning::draw(){
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);
    
	glColor4ub(_color.r, _color.g, _color.b, _opacity);
	glLineWidth(_lighteningWidth);
	glEnable(GL_LINE_SMOOTH);
    
	if (_opacity != 255)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	CCPoint mid = drawLightning(_strikePoint3, _strikePoint, _displacement, _minDisplacement, _seed);
	
	if(_split)
		drawLightning(mid, _strikePoint2, _displacement/2, _minDisplacement, _seed);
    
	if (_opacity != 255)
		glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
}

void Lightning::setColor(const ccColor3B& color){
	_color = color;
}

const ccColor3B& Lightning::getColor(){
	return _color;
}

void Lightning::setOpacity(GLubyte opacity){
	_opacity = opacity;
}

GLubyte Lightning::getOpacity(){
	return _opacity;
}

void Lightning::strikeRandom(){
	srand(time(NULL));
	_seed = rand();
	this->strike();
}
CCArray* Lightning::getRGBAChildren() {
    return getChildren();
}
CCNode* Lightning::getRGBAParent() {
    return getParent();
}
void Lightning::strikeWithSeed(unsigned long seed){
	_seed = seed;
	this->strike();
}

void Lightning::strike(){
	this->setVisible(false);
	this->setOpacity(255);
    
	this->runAction(CCSequence::create(CCShow::create(), CCBlink::create(0.5f, 2), CCFadeOut::create(0.5f), NULL));
}
