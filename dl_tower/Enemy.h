//
//  Enemy.h
//  dl_tower
//
//  Created by user on 13-10-18.
//
//

#ifndef __dl_tower__Enemy__
#define __dl_tower__Enemy__

#include "cocos2d.h"
#include "WayPoint.h"
#include "EnemyLayer.h"
#include "RunGameScene.h"

USING_NS_CC;

class WayPoint;
class EnemyLayer;
class Tower;
class RunGameScene;

class Enemy: public CCNode
{
public:
    Enemy();
    ~Enemy();
    static Enemy *nodeWithTheLayer(EnemyLayer *layer, CCTexture2D *texture);
    bool initWithTheLayer(EnemyLayer *layer, CCTexture2D *texture);
    void doActivated(float dt);
    
    void getRemoved();
    void getDamaged(int hp);
    void getAttacker(Tower *tower);
    void getLostSight(Tower *tower);
    
    void draw();
    //CC_SYNTHESIZE(CCScene *, scene, Scene);
    CC_SYNTHESIZE(CCSprite *, _mSprite, MySprite);
    CC_SYNTHESIZE(WayPoint *, destPoint, DestPoint);
    CC_SYNTHESIZE(CCPoint, myLocation, MyLocation)
    CC_SYNTHESIZE(bool, active, Active);
    CC_SYNTHESIZE(float, speed, Speed);
    CC_SYNTHESIZE(int, award, Award);
    CC_SYNTHESIZE(CCArray *, attackedBy, AttackerList)
    CC_SYNTHESIZE(EnemyLayer *, myLayer, MyLayer);
protected:
//    CCArray *attackedBy;
    int maxHp;
    int currentHp;
    static const float HEALTH_BAR_WIDTH = 20;
    static const float HEALTH_BAR_ORIGIN = -10;
//    EnemyLayer *myLayer;
    //CCPoint myLocation;

};

#endif /* defined(__dl_tower__Enemy__) */
