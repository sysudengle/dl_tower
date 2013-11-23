//
//  TowerLayer.cpp
//  dl_tower
//
//  Created by user on 13-10-17.
//
//

#include "TowerLayer.h"

USING_NS_CC;

class TouchLayer;

TowerLayer::TowerLayer()
{
    
}

TowerLayer::~TowerLayer()
{
    this->m_towerList->release();
}

bool TowerLayer::init()
{
    bool ret = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        m_towerList = CCArray::create();
        m_towerList->retain();
        
        m_towerSprite = CCSpriteBatchNode::create("tower-hd.png");
        m_towerSprite->setPosition(CCPointZero);
        this->addChild(m_towerSprite);
        
        /*CCSprite * news = CCSprite::createWithTexture(this->m_towerSprite->getTexture());
        news->setPosition(ccp(200, 200));
        this->m_towerSprite->addChild(news);*/
        
        /*CCSprite *bullet = CCSprite::create("bullet-hd.png");
        
        bullet->setPosition(ccp(400, 400));
        this->addChild(bullet);*/

        
        this->schedule(schedule_selector(TowerLayer::test));
        ret = true;
    } while (0);
    
    return ret;

}

void TowerLayer::addNewTower(CCPoint position, int tower_id, CCSprite *towerBase)
{
    Tower *tower = NULL;
    
    switch (tower_id) {
        case 0:
        {
            tower = Tower::nodeWithTheLayer(this, position, this->m_towerSprite->getTexture());
            break;
        }
        default:
            break;
    }
    towerBase->setUserData((void *)tower);
    this->addChild(tower);
    //this->m_towerSprite->addChild(tower->getMySprite());
    //this->m_towerList->addObject(tower);
}

void TowerLayer::removeTower(Tower * tower)
{
    
}

void TowerLayer::singleTouchDirecting(CCPoint point)
{
    CCLog("Tower Single");
    RunGameScene *scene = (RunGameScene *)this->scene;
    CCSprite *towerBase = NULL;
    
    //scene->m_enemyLayer->addNewEnemy(0);
    if((towerBase = scene->m_backgroundLayer->getTowerBase(point)) && towerBase != NULL && scene->canBuy(Tower::price))
    {
        CCLOG("add New tower");
        this->addNewTower(towerBase->getPosition(), 0, towerBase);
    }
}

void TowerLayer::test(float dt)
{
    
}