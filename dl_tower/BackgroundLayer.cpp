//
//  BackgroundLayer.cpp
//  dl_tower
//
//  Created by user on 13-10-17.
//
//

#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace CocosDenshion;

//class TowerLayer;

BackgroundLayer::BackgroundLayer()
{
    
}

BackgroundLayer::~BackgroundLayer()
{
    towerBases->release();
}

bool BackgroundLayer::init()
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(! CCLayer::init());
        
        loadBackgroundImage();
        loadTowerPositions();
        ret = true;
    } while (0);
    
    return ret;
}

CCSprite *BackgroundLayer::getTowerBase(CCPoint point)
{
    CCObject *pObject = NULL;
    CCSprite *towerBase = NULL;
    
    CCARRAY_FOREACH(this->towerBases, pObject)
    {
        towerBase = (CCSprite *)pObject;
        //getUserData return false when the towerBase contains no tower
        if(towerBase->boundingBox().containsPoint(point) && !towerBase->getUserData())
        {
            return towerBase;
        }
    }
    return NULL;
}

void BackgroundLayer::loadBackgroundImage()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // load the background
    CCLayer *backgroundLayer = CCLayer::create();
    CCSprite *backgroud = CCSprite::create("bg-hd.png");
    backgroud->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    backgroundLayer->addChild(backgroud);
    this->addChild(backgroundLayer);
}

void BackgroundLayer::loadTowerPositions()
{
    CCArray* towerPositions = CCArray::createWithContentsOfFile("TowersPosition.plist");
    // capacity ???????
    towerBases = CCArray::createWithCapacity(10);
    towerBases->retain();
    
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(towerPositions, pObject)
    {
        CCLOG("add base~");
        CCDictionary* towerPos = (CCDictionary*)pObject;
        CCSprite* towerBase = CCSprite::create("open_spot-hd.png");
        this->addChild(towerBase);
        towerBase->setPosition(ccp(((CCString*)towerPos->objectForKey("x"))->intValue(),
                                   ((CCString*)towerPos->objectForKey("y"))->intValue()));
        CCLog("%f %f", towerBase->getPosition().x, towerBase->getPosition().y);
        towerBases->addObject(towerBase);
    }
}

