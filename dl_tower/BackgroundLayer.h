//
//  BackgroundLayer.h
//  dl_tower
//
//  Created by user on 13-10-17.
//
//

#ifndef __dl_tower__BackgroundLayer__
#define __dl_tower__BackgroundLayer__

#include "cocos2d.h"
#include "RunGameScene.h"

USING_NS_CC;

class BackgroundLayer: public CCLayer
{
public:
    BackgroundLayer();
    ~BackgroundLayer();
    bool init();
    CCSprite *getTowerBase(CCPoint point);
    CREATE_FUNC(BackgroundLayer);
    CCScene *scene;
//    CC_SYNTHESIZE_RETAIN(CCScene *, scene, Scene);
private:
    void loadTowerPositions();
    void loadBackgroundImage();
    CCArray *towerBases;
    // TowerLayer is friend
};

#endif /* defined(__dl_tower__BackgroundLayer__) */
