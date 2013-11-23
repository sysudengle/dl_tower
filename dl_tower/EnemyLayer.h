//
//  EnemyLayer.h
//  dl_tower
//
//  Created by user on 13-10-18.
//
//

#ifndef __dl_tower__EnemyLayer__
#define __dl_tower__EnemyLayer__

#include "cocos2d.h"
#include "Tower.h"
#include "Enemy.h"
#include "RunGameScene.h"

USING_NS_CC;

class Enemy;
class RunGameScene;

class EnemyLayer: public CCLayer
{
public:
    EnemyLayer();
    ~EnemyLayer();
    
    bool init();
    Enemy *addNewEnemy(int Enemy_id);
    void removeEnemy(Enemy * enemy);
    
    void setUpdateOn();
    void update(float dt);
    
    void enemyLogic();
    void enemyMove(Enemy *enemy);
    
    bool loadWavePoints();
    bool loadEnemyWaves(int wave);
    bool collisionInCircle(CCPoint point1, float radius1, CCPoint point2, float radius2);
    void test(float dt);
    void doActivated(float dt);
    CC_SYNTHESIZE_RETAIN(CCArray *, _wayPoints, WayPoints);
    CC_SYNTHESIZE(CCArray *, m_EnemyList, EnemyList);
    CREATE_FUNC(EnemyLayer);
    
    CC_SYNTHESIZE(RunGameScene *, scene, Scene);
private:
//    CCArray *m_EnemyList;
    CCSpriteBatchNode *m_EnemySprite;
};

#endif /* defined(__dl_tower__EnemyLayer__) */
