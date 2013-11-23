//
//  GameLostScene.cpp
//  dl_tower
//
//  Created by user on 13-10-21.
//
//

#include "GameLostScene.h"

USING_NS_CC;

bool GameLostScene::init()
{
    bool ret = false;
    
    do {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCLabelTTF *contentLabel = CCLabelTTF::create("You lost!~!Haha!~", "Marker Felt", 100);
        contentLabel->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        
        CCLayerGradient *layer = CCLayerGradient::create(ccc4(0, 0, 0, 120), ccc4(255, 255, 255, 120));
        layer->addChild(contentLabel);
        
        this->addChild(layer);
        ret = true;
    } while (0);
    
    return ret;
}