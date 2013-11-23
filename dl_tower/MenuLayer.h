//
//  MenuLayer.h
//  dl_tower
//
//  Created by user on 13-10-21.
//
//

#ifndef __dl_tower__MenuLayer__
#define __dl_tower__MenuLayer__

#include "cocos2d.h"
#include "RunGameScene.h"

class RunGameScene;

class MenuLayer: public CCLayer
{
public:
    bool init();
    CREATE_FUNC(MenuLayer);
    void setWaveLabel(int wave);
    void setHpLabel(int hp);
    void setMoneyLabel(int money);
    CC_SYNTHESIZE(RunGameScene *, scene, MyScene);
protected:
    CCLabelTTF *waveLabel;
    CCLabelTTF *hpLabel;
    CCLabelTTF *moneyLabel;
};

USING_NS_CC;


#endif /* defined(__dl_tower__MenuLayer__) */
