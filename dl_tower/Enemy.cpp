//
//  Enemy.cpp
//  dl_tower
//
//  Created by user on 13-10-18.
//
//

#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy()
{
    
}

Enemy::~Enemy()
{
    attackedBy->release();
}

Enemy *Enemy::nodeWithTheLayer(EnemyLayer *layer, CCTexture2D *texture)
{
    Enemy *enemy = new Enemy();
    
    if(enemy && enemy->initWithTheLayer(layer, texture))
    {
        ;
    }
    else
    {
        delete enemy;
        enemy = NULL;
    }
    return enemy;

}

bool Enemy::initWithTheLayer(EnemyLayer *layer, CCTexture2D *texture)
{
    bool ret = false;
    
    do {
        this->maxHp = 5;
        this->currentHp = 5;
        this->speed = 5;
        this->award = 2;
        this->active = false;
        this->attackedBy = CCArray::create();
        this->attackedBy->retain();
        
        this->myLayer = layer;
//        RunGameScene *scene = (RunGameScene *)layer->scene;
        WayPoint *startPoint = (WayPoint *)layer->getWayPoints()->objectAtIndex(layer->getWayPoints()->count() - 1);
        this->destPoint = startPoint->getNextWayPoint();
        this->myLocation = startPoint->getMyPosition();
        
        this->_mSprite = CCSprite::createWithTexture(texture);
        this->_mSprite->setPosition(this->myLocation);

        
        ret = true;
    } while (0);
    return ret;
}

void Enemy::doActivated(float dt)
{
    CCLog("do Activated~");
    this->active = true;
    this->unschedule(schedule_selector(Enemy::doActivated));
}

void Enemy::getRemoved()
{
    
}

void Enemy::getDamaged(int hp)
{
    currentHp -= hp;
    if(currentHp < 1)
    {
        this->myLayer->getScene()->getAward(this->getAward());
        myLayer->removeEnemy(this);
    }
}

void Enemy::getAttacker(Tower *tower)
{
    attackedBy->addObject(tower);
}

void Enemy::getLostSight(Tower *tower)
{
    attackedBy->removeObject(tower);
}

void Enemy::draw()
{
    if(_mSprite)
    {
    CCLog("x: %f, y: %f", this->getMyLocation().x, this->getMyLocation().y);
        CCLog("x: %f, y: %f", _mSprite->getPosition().x, _mSprite->getPosition().y);
    CCPoint healthBarBack[] = {
        ccp(_mSprite->getPosition().x - 10, _mSprite->getPosition().y + 16),
        ccp(_mSprite->getPosition().x + 10, _mSprite->getPosition().y + 16),
        ccp(_mSprite->getPosition().x + 10, _mSprite->getPosition().y + 14),
        ccp(_mSprite->getPosition().x - 10, _mSprite->getPosition().y + 14)
    };
    //ccDrawPoint(this->getMyLocation());
    //ccDrawColor4F(255, 255, 255, 255);
    //ccDrawCircle(this->_mSprite->getPosition(), 100, 360, 30, false);
    ccDrawSolidPoly(healthBarBack, 4, ccc4f(255, 0, 0, 255));
    
    CCPoint healthBar[] = {
        ccp(_mSprite->getPosition().x + HEALTH_BAR_ORIGIN, _mSprite->getPosition().y + 16),
        ccp(_mSprite->getPosition().x + HEALTH_BAR_ORIGIN + (float)(currentHp * HEALTH_BAR_WIDTH) / maxHp, _mSprite->getPosition().y + 16),
        ccp(_mSprite->getPosition().x + HEALTH_BAR_ORIGIN + (float)(currentHp * HEALTH_BAR_WIDTH) / maxHp, _mSprite->getPosition().y + 14),
        ccp(_mSprite->getPosition().x + HEALTH_BAR_ORIGIN, _mSprite->getPosition().y + 14)
    };
    ccDrawSolidPoly(healthBar, 4, ccc4f(0, 255, 0, 255));
    
    CCNode::draw();
    }
}
