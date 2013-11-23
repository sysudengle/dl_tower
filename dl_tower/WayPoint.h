//
//  WayPoint.h
//  dl_tower
//
//  Created by user on 13-10-18.
//
//

#ifndef __dl_tower__WayPoint__
#define __dl_tower__WayPoint__

#include "cocos2d.h"
#include "RunGameScene.h"

USING_NS_CC;

class WayPoint: public CCNode
{
public:
    WayPoint();
    ~WayPoint();
    static WayPoint *nodeWithTheLayer(CCLayer *game, CCPoint point);
    bool initWithTheLayer(CCLayer *layer, CCPoint point);
    CC_SYNTHESIZE(CCPoint, myPosition, MyPosition);
    CC_SYNTHESIZE(WayPoint *, _nextWayPoint, NextWayPoint);
    
    void draw();
private:
    CCLayer *m_layer;
};

#endif /* defined(__dl_tower__WayPoint__) */
