//
//  EnemyLayer.cpp
//  dl_tower
//
//  Created by user on 13-10-18.
//
//

#include "EnemyLayer.h"

USING_NS_CC;

EnemyLayer::EnemyLayer()
{
    
}

EnemyLayer::~EnemyLayer()
{
    this->m_EnemyList->release();
    this->_wayPoints->release();
}

bool EnemyLayer::init()
{
    bool ret = false;
    
    do {
        //this->scheduleUpdate();
        this->loadWavePoints();
        
        this->m_EnemyList = CCArray::create();
        this->m_EnemyList->retain();
        
        this->m_EnemySprite = CCSpriteBatchNode::create("enemy-hd.png");
        this->m_EnemySprite->setPosition(CCPointZero);
        this->addChild(this->m_EnemySprite);
        
        /*Enemy *enemy = Enemy::nodeWithTheLayer(this, this->m_EnemySprite->getTexture());
        enemy->setPosition(CCPointZero);
        this->m_EnemySprite->addChild(enemy->getMySprite());
        this->m_EnemyList->addObject(enemy);*/
        
        this->schedule(schedule_selector(Enemy::update), 0.1f);
        ret = true;
    } while (0);
    
    return ret;
}

Enemy *EnemyLayer::addNewEnemy(int Enemy_id)
{
    Enemy *enemy = NULL;
    switch (Enemy_id) {
        case 0:
        {
            enemy = Enemy::nodeWithTheLayer(this, this->m_EnemySprite->getTexture());
            break;
        }
        default:
            break;
    }
    
    this->m_EnemyList->addObject(enemy);
    this->m_EnemySprite->addChild(enemy->getMySprite());
    this->addChild(enemy);
    CCLog("add new Enemy");
    CCLog("new reference %d", enemy->retainCount());
    return enemy;
}

void EnemyLayer::removeEnemy(Enemy * enemy)
{
    // anounce the attacker to delete
    CCObject *pObject = NULL;
    Tower *tower = NULL;
    CCARRAY_FOREACH(enemy->getAttackerList(), pObject)
    {
        tower = (Tower *)pObject;
        tower->targetKilled();
    }
    
    CCLog("1.reference %d", enemy->retainCount());
    this->m_EnemySprite->removeChild(enemy->getMySprite(), true);
    CCLog("2.reference %d", enemy->retainCount());
    this->m_EnemyList->removeObject(enemy);
    CCLog("3.reference %d", enemy->retainCount());
    this->removeChild(enemy);
    //enemy->release();
    CC_SAFE_RELEASE(enemy);
    CCLog("4.reference %d", enemy->retainCount());
    
    this->scene->enemyGotKilled();
    //enemy->getRemoved();
}

/*void EnemyLayer::setUpdateOn()
{
    this->scheduleUpdate();
}*/

void EnemyLayer::update(float dt)
{
    CCLog("Enemy update");
    //addNewEnemy(0);
    enemyLogic();
}

void EnemyLayer::enemyLogic()
{
    CCObject *pObject = NULL;
    Enemy *enemy = NULL;
    CCARRAY_FOREACH(this->m_EnemyList, pObject)
    {
        //CCLog("Enemy logic loop");
        CCLog("Object reference %d", pObject->retainCount());
        enemy = (Enemy *)pObject;
        CCLog("logic reference %d", enemy->retainCount());
        //CCLog("1.reference %d", enemy->retainCount());
        if(enemy->getActive())
        {
            CCLog("move enemy~");
            this->enemyMove(enemy);
        }
    }
}

void EnemyLayer::enemyMove(Enemy *enemy)
{
    //RunGameScene *scene = (RunGameScene *)this->scene;
    CCPoint targetLocation = enemy->getDestPoint()->getMyPosition();
    
    if(this->collisionInCircle(enemy->getMyLocation(), 1.0, targetLocation, 1.0))
    {
        CCLog("reach nextPosition");
        if(enemy->getDestPoint()->getNextWayPoint())
        {
            enemy->setDestPoint(enemy->getDestPoint()->getNextWayPoint());
        }
        else
        {
            // damage HP and deleted the enemy
            this->scene->playerGotAttacked();
            this->removeEnemy(enemy);
//            this->m_EnemySprite->removeChild(enemy->getMySprite(), true);
//            this->m_EnemyList->removeObject(enemy);
            return;
        }

    }
    CCLog("enemy is moving!~");
    CCPoint myLocation = enemy->getMyLocation();
    CCPoint normalized = ccpNormalize(ccp(targetLocation.x - myLocation.x, targetLocation.y - myLocation.y));
    float speed = enemy->getSpeed();
    
    enemy->setMyLocation(ccp(myLocation.x + speed * normalized.x, myLocation.y + speed * normalized.y));
    // the under code should be deleted since enemy's node's position will be altered
    //enemy->setPosition(enemy->getMyLocation());
    enemy->getMySprite()->setRotation(CC_RADIANS_TO_DEGREES(atan2(normalized.y, normalized.x)));
    enemy->getMySprite()->setPosition(enemy->getMyLocation());
    CCLog("Enemy move: x: %f, y: %f", enemy->getMyLocation().x, enemy->getMyLocation().y);
    //enemy->setPosition(ccp(myL®ocation.x + 2, myLocation.y + 2));
}

bool EnemyLayer::loadEnemyWaves(int wave)
{
    //CCNode::onEnter();
    CCArray *waveData = CCArray::createWithContentsOfFile("Waves.plist");
    if(wave > waveData->count())
    {
        return false;
    }
    
    CCArray *currentWaveData = (CCArray *)waveData->objectAtIndex(wave - 1);
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(currentWaveData, pObject)
    {
        CCDictionary* enemyData = (CCDictionary *)pObject;
        Enemy *enemy = this->addNewEnemy(0);
        //CCNode::onEnter();
        enemy->schedule(schedule_selector(Enemy::doActivated), ((CCString*)enemyData->objectForKey("spawnTime"))->floatValue());
        //enemy->doActivated(1);
        //this->addChild(enemy);
        //enemy->schedule(schedule_selector(Enemy::doActivated), 1);
        //this->schedule(schedule_selector(Enemy::doActivated), ((CCString*)enemyData->objectForKey("spawnTime"))->floatValue());
        CCLog("load Waves.plist once %f", ((CCString*)enemyData->objectForKey("spawnTime"))->floatValue());
    }
    
    //this->schedule(schedule_selector(EnemyLayer::test), 1);
    //ui_wave_lbl->setString(CCString::createWithFormat("WAVE: %d", wave)->getCString());
    return true;

}
bool EnemyLayer::loadWavePoints()
{
    _wayPoints = CCArray::create();
    _wayPoints->retain();
    
    CCObject *pObject = NULL;
    CCArray *wayPointsData = CCArray::createWithContentsOfFile("WayPoints.plist");
    CCDictionary* wayPointData = (CCDictionary *)wayPointsData->objectAtIndex(0);
    WayPoint *nextWayPoint = NULL;
    float x, y;
    
    x = ((CCString *)wayPointData->objectForKey("x"))->floatValue();
    y = ((CCString *)wayPointData->objectForKey("y"))->floatValue();
    WayPoint *currentWayPoint = WayPoint::nodeWithTheLayer(this, ccp(x, y));
    _wayPoints->addObject(currentWayPoint);
    
    for(int i = 1; i < wayPointsData->count(); i++)
    {
        nextWayPoint = currentWayPoint;
        
        wayPointData = (CCDictionary *)wayPointsData->objectAtIndex(i);
        x = ((CCString *)wayPointData->objectForKey("x"))->floatValue();
        y = ((CCString *)wayPointData->objectForKey("y"))->floatValue();
        currentWayPoint = WayPoint::nodeWithTheLayer(this, ccp(x, y));
        
        _wayPoints->addObject(currentWayPoint);
        currentWayPoint->setNextWayPoint(nextWayPoint);
    }
    /*
    WayPoint *wayPoint1 = WayPoint::nodeWithTheLayer(this, ccp(420, 100));
    _wayPoints->addObject(wayPoint1);
    
    WayPoint *wayPoint2 = WayPoint::nodeWithTheLayer(this, ccp(420, 500));
    _wayPoints->addObject(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);
    
    WayPoint *wayPoint3 = WayPoint::nodeWithTheLayer(this, ccp(35, 500));
    _wayPoints->addObject(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);
    
    CCLog("Way load");*/

}

bool EnemyLayer::collisionInCircle(CCPoint point1, float radius1, CCPoint point2, float radius2)
{
    float x = point1.x - point2.x, y = point1.y - point2.y;
    float distance = sqrt(x * x + y * y);
    
    if(distance <= radius1 + radius2)
    {
        return true;
    }
    return false;
}

void EnemyLayer::doActivated(float dt)
{
    
}

void EnemyLayer::test(float dt)
{
    CCLog("test here!~");
}