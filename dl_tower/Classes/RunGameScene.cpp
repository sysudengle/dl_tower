//
//  RunGameScene.cpp
//  dengle2
//
//  Created by user on 13-10-15.
//
//

#include "RunGameScene.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

RunGameScene::RunGameScene() {}

RunGameScene::~RunGameScene()
{

}

bool RunGameScene::init()
{
    if(CCScene::init())
    {
        wave = 0;
        playerHp = 5;
        money = 10;
        
        loadBackground();
        loadWayPoint();
        loadEnemyLayer();
        loadTowerLayer();
        loadMenuLayer();
        loadTouchLayer();
        
        loadEnemyWave();
        
        return true;
    }
    else
    {
        return false;
    }
}

void RunGameScene::loadBackground()
{
    this->m_backgroundLayer = BackgroundLayer::create();
    this->addChild(this->m_backgroundLayer);
    this->m_backgroundLayer->scene = this;
    CCLog("Background load");
}

void RunGameScene::loadTowerLayer()
{
    this->m_towerLayer = TowerLayer::create();
    this->addChild(this->m_towerLayer);
    //this->m_towerLayer->scene = this;
    this->m_towerLayer->setMyScene(this);
    CCLog("Tower load");
}

void RunGameScene::loadWayPoint()
{
        /*WayPoint *wayPoint3 = WayPoint::nodeWithTheScene(this, ccp(35, 130));
    _wayPoints->addObject(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);*/
}

void RunGameScene::loadEnemyLayer()
{
    this->m_enemyLayer = EnemyLayer::create();
    this->addChild(this->m_enemyLayer);
    this->m_enemyLayer->setScene(this);
    //this->m_enemyLayer->scene = this;
    //this->m_enemyLayer->setUpdateOn();
    CCLog("Enemy load");
}

bool RunGameScene::loadEnemyWave()
{
    m_menuLayer->setWaveLabel(++wave);
    return this->m_enemyLayer->loadEnemyWaves(this->wave);
    CCLog("Enemy Wave load");
}

void RunGameScene::loadMenuLayer()
{
    this->m_menuLayer = MenuLayer::create();
    this->addChild(this->m_menuLayer);
    this->m_menuLayer->setMyScene(this);
    
    this->m_menuLayer->setMoneyLabel(money);
    CCLog("Menu load");
}

void RunGameScene::loadTouchLayer()
{
    this->m_touchLayer = TouchLayer::node();
    this->m_touchLayer->setDelegate(this->m_towerLayer);
    this->addChild(this->m_touchLayer);
    CCLog("Touch load");
}

bool RunGameScene::canAffordTower(int cost)
{
    return true;
}

bool RunGameScene::collisionWithCircle(CCPoint point1, float radius1, CCPoint point2, float radius2)
{
    float x = point1.x - point2.x, y = point1.y - point2.y;
    float distance = sqrt(x * x + y * y);
    
    if(distance <= radius1 + radius2)
    {
        return true;
    }
    return false;
}


void RunGameScene::enemyGotKilled()
{
    if(m_enemyLayer->getEnemyList()->count() <= 0)
    {
        if(!this->loadEnemyWave())
        {
            CCDirector::sharedDirector()->replaceScene(GameWinScene::create());
            CCLOG("You win!~");
        }
    }
}

void RunGameScene::playerGotAttacked()
{
    playerHp--;
    m_menuLayer->setHpLabel(playerHp);
    if(playerHp <= 0)
    {
        CCDirector::sharedDirector()->replaceScene(GameLostScene::create());
        CCLog("You lost!~");
    }
}

bool RunGameScene::canBuy(int cost)
{
    bool ret = false;
    
    if(money < cost)
    {
        CCLog("You don't have enough money");
    }
    else
    {
        money -= cost;
        m_menuLayer->setMoneyLabel(money);
        ret = true;
    }
    return ret;
}

void RunGameScene::getAward(int award)
{
    money += award;
    m_menuLayer->setMoneyLabel(money);
}