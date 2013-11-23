//
//  RunGameScene.h
//  dengle2
//
//  Created by user on 13-10-15.
//
//
#ifndef __dl_defend__RunGameScene__
#define __dl_defend__RunGameScene__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "TowerLayer.h"
#include "TouchLayer.h"
#include "MenuLayer.h"
#include "TouchLayerDelegate.h"

#include "WayPoint.h"
#include "Enemy.h"

#include "GameLostScene.h"
#include "GameWinScene.h"
//#include "../Bullet.h"
//#include "../Enemy.h"

USING_NS_CC;

enum sprite{
    kingbox_id,
    girl_id
};

class BackgroundLayer;
class EnemyLayer;
class TowerLayer;
class MenuLayer;

class RunGameScene: public CCScene
{
public:
    RunGameScene();
    ~RunGameScene();
    virtual bool init();
    bool canAffordTower(int cost);
    bool collisionWithCircle(CCPoint point1, float radius1, CCPoint point2, float radius2);
    void enemyGotKilled();
    void playerGotAttacked();
    bool canBuy(int cost);
    void getAward(int award);
    CREATE_FUNC(RunGameScene);
    CC_SYNTHESIZE(int, money, getMoney);
    BackgroundLayer * m_backgroundLayer;
    TouchLayer * m_touchLayer;
    TowerLayer *m_towerLayer;
//    EnemyLayer *m_enemyLayer;
    CC_SYNTHESIZE(EnemyLayer *, m_enemyLayer, EnemyLayer);
    CC_SYNTHESIZE(MenuLayer *, m_menuLayer, MenuLayer)
private:
    void loadBackground();
    void loadTowerLayer();
    void loadWayPoint();
    void loadEnemyLayer();
    bool loadEnemyWave();
    void loadMenuLayer();
    void loadTouchLayer();
    
    int wave;
    int playerHp;
};


#endif /* defined(__dengle2__RunGameScene__) */
