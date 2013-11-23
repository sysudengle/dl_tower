//
//  Tower.cpp
//  dl_tower
//
//  Created by user on 13-10-17.
//
//

#include "Tower.h"

USING_NS_CC;

Tower::Tower()
{
    
}

Tower::~Tower()
{
    
}

Tower *Tower::nodeWithTheLayer(TowerLayer *layer, CCPoint location, CCTexture2D *texture)
{
    Tower *tower = new Tower();
    
    if(tower && tower->initWithTheLayer(layer, location, texture))
    {
        ;
    }
    else
    {
        delete tower;
        tower = NULL;
    }
    return tower;
}

bool Tower::initWithTheLayer(TowerLayer *layer, CCPoint location, CCTexture2D *texture)
{
    bool ret = false;
    
    do {
        chosenEnemy = NULL;
        type = 1;
        damage = 1;
        attackRange = 200;
        fireRate = 0.5;
        fireSpeed = 0.1;
        
        _mSprite = CCSprite::createWithTexture(texture);
        _mSprite->setPosition(location);
        this->layer = layer;
        
        layer->getTowerList()->addObject(this);
        layer->getSpriteBatchNode()->addChild(this->_mSprite);
        this->scheduleUpdate();
        
        /*CCSprite *bullet = CCSprite::create("bullet-hd.png");
        
        
        bullet->setPosition(ccp(500, 300));
        layer->addChild(bullet);*/

        //this->schedule(schedule_selector(Tower::update));
        
        ret = true;
    } while (0);
    return ret;
}

void Tower::update(float dt)
{
    CCLog("Tower Update");
    RunGameScene *scene = layer->getMyScene();
    if(chosenEnemy)
    {
        CCPoint normalized = ccpNormalize(ccp(chosenEnemy->getMySprite()->getPosition().x - _mSprite->getPosition().x,
                                              chosenEnemy->getMySprite()->getPosition().y - _mSprite->getPosition().y));
        _mSprite->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, - normalized.x)) + 90);
        //Enemy out of sight
        if(!scene->collisionWithCircle(chosenEnemy->getMyLocation(), 1,
                                                          _mSprite->getPosition(), this->attackRange))
        {
            this->enemyOutOfSight();
        }
    }
    else
    {
        // search the enemy in scope
        Enemy *enemy = NULL;
        CCObject *pObject = NULL;
        CCARRAY_FOREACH(scene->getEnemyLayer()->getEnemyList(), pObject)
        {
            enemy = (Enemy *)pObject;
            if(scene->collisionWithCircle(enemy->getMyLocation(), 1, _mSprite->getPosition(), this->attackRange))
            {
                chosenEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::draw(void)
{
    CCLog("Tower draw");
#ifdef COCOS2D_DEBUG
    ccDrawColor4F(255, 255, 255, 255);
    ccDrawCircle(this->_mSprite->getPosition(), attackRange, 360, 30, false);
#endif
    ccDrawColor4F(255, 255, 255, 255);
    ccDrawCircle(this->_mSprite->getPosition(), attackRange, 360, 30, false);
    CCNode::draw();
}

void Tower::chosenEnemyForAttack(Enemy *enemy)
{
    chosenEnemy = enemy;
    chosenEnemy->getAttacker(this);
    attackEnemy();
}

void Tower::enemyOutOfSight()
{
    chosenEnemy->getLostSight(this);
    chosenEnemy = NULL;
}

void Tower::attackEnemy()
{
    this->schedule(schedule_selector(Tower::shootEnemy), fireRate);
    
}

void Tower::shootEnemy(float dt)
{
    CCSprite *bullet = setBullet();
    bulletAction(bullet, fireSpeed);
}

void Tower::damageEnemy()
{
    CCLOG("damage Enemy");
    if(chosenEnemy)
    {
        chosenEnemy->getDamaged(damage);
    }
}

void Tower::targetKilled()
{
    chosenEnemy = NULL;
    this->unschedule(schedule_selector(Tower::shootEnemy));
}

CCSprite *Tower::setBullet()
{
    CCSprite *bullet = CCSprite::create("bullet-hd.png");
    
    bullet->setPosition(this->_mSprite->getPosition());
    CCLOG("Bullet Position x: %f, y: %f", this->_mSprite->getPosition().x, this->_mSprite->getPosition().y);
    //bullet->setPosition(ccp(700, 700));
    layer->addChild(bullet);
    
    return bullet;
}

void Tower::bulletAction(CCSprite *bullet, float speed)
{
    if(chosenEnemy)
    {
        CCLOG("Enemy Position x: %f y: %f", chosenEnemy->getMyLocation().x, chosenEnemy->getMyLocation().y);
        bullet->runAction(CCSequence::create(
                                      CCMoveTo::create(speed, chosenEnemy->getMyLocation()),
                                      CCCallFunc::create(this, callfunc_selector(Tower::damageEnemy)),
                                      CCCallFuncN::create(this, callfuncN_selector(Tower::removeBullet)),
                                                          NULL));
    }
}

void Tower::removeBullet(CCSprite *bullet)
{
    bullet->getParent()->removeChild(bullet);
}

