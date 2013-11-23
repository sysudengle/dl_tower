//
//  Tower.h
//  dl_tower
//
//  Created by user on 13-10-17.
//
//

#ifndef __dl_tower__Tower__
#define __dl_tower__Tower__

#include "cocos2d.h"
#include "Enemy.h"
#include "RunGameScene.h"

USING_NS_CC;

class TowerLayer;
class Enemy;
class RunGameScene;

class Tower: public CCNode
{
public:
    Tower();
    ~Tower();
    
    static Tower *nodeWithTheLayer(TowerLayer *layer, CCPoint location, CCTexture2D *texture);
    bool initWithTheLayer(TowerLayer *layer, CCPoint location, CCTexture2D *texture);
    
    void update(float dt);
    void draw(void);
    
    void chosenEnemyForAttack(Enemy *enemy);
    void enemyOutOfSight();
//    void removeChosenEnemy(Enemy *enemy);
    void attackEnemy();
    void shootEnemy(float dt);
    void damageEnemy();
    void targetKilled();
    
    CCSprite *setBullet();
    void bulletAction(CCSprite *bullet, float speed);
    void removeBullet(CCSprite *bullet);
    
    CC_SYNTHESIZE(CCSprite *, _mSprite, MySprite);
    static const int price = 5;
protected:
    Enemy *chosenEnemy;
    int type;
    int damage;
    int attackRange;
    float fireRate;
    float fireSpeed;
    
    TowerLayer *layer;
    CCSpriteBatchNode *m_towerSprite;
    
    int level;
};

#endif /* defined(__dl_tower__Tower__) */
