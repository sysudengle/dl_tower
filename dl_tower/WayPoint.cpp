//
//  WayPoint.cpp
//  dl_tower
//
//  Created by user on 13-10-18.
//
//

#include "WayPoint.h"

USING_NS_CC;

WayPoint::WayPoint()
{
    this->_nextWayPoint = NULL;
}

WayPoint::~WayPoint()
{
    
}

WayPoint *WayPoint::nodeWithTheLayer(CCLayer *layer, CCPoint point)
{
    WayPoint *wayPoint = new WayPoint();
    
    if(wayPoint && wayPoint->initWithTheLayer(layer, point))
    {
        ;
    }
    else
    {
        delete wayPoint;
        wayPoint = NULL;
    }
    return wayPoint;

}

bool WayPoint::initWithTheLayer(CCLayer *layer, CCPoint point)
{
    bool ret = false;
    
    do {
        this->m_layer = (EnemyLayer *)layer;
        myPosition = point;
        
        this->setPosition(CCPointZero);
        this->m_layer->addChild(this);
        ret = true;
    } while (0);
    return ret;
}

void WayPoint::draw()
{
#ifdef COCOS2D_DEBUG
    ccDrawColor4F(0, 255, 0, 255);
    ccDrawCircle(myPosition, 6, 360, 30, false);
    ccDrawCircle(myPosition, 2, 360, 30, false);
    
    if (_nextWayPoint)
    {
        ccDrawLine(myPosition, _nextWayPoint->myPosition);
    }
#endif
    
    CCNode::draw();
}
