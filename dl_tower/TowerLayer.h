//
//  TowerLayer.h
//  dl_tower
//
//  Created by user on 13-10-17.
//
//

#ifndef __dl_tower__TowerLayer__
#define __dl_tower__TowerLayer__

#include "cocos2d.h"
#include "Tower.h"
#include "TouchLayerDelegate.h"
#include "RunGameScene.h"

USING_NS_CC;

class Tower;
class RunGameScene;

class TowerLayer: public CCLayer, public TouchLayerDelegate
{
public:
    TowerLayer();
    ~TowerLayer();
    
    void singleTouchDirecting(CCPoint point);
    
    bool init();
    void addNewTower(CCPoint position, int tower_id, CCSprite *towerBase);
    void removeTower(Tower * tower);
    void test(float dt);
    CREATE_FUNC(TowerLayer);
    
    CC_SYNTHESIZE(RunGameScene *, scene, MyScene);
    CC_SYNTHESIZE(CCArray *, m_towerList, TowerList);
    CC_SYNTHESIZE(CCSpriteBatchNode *, m_towerSprite, SpriteBatchNode);
private:
    //CCArray *m_towerList;
    //CCSpriteBatchNode *m_towerSprite;
};
#endif /* defined(__dl_tower__TowerLayer__) */
