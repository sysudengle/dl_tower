//
//  MenuLayer.cpp
//  dl_tower
//
//  Created by user on 13-10-21.
//
//

#include "MenuLayer.h"

USING_NS_CC;

bool MenuLayer::init()
{
    bool ret = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
//        waveLabel = CCLabelTTF::create(CCString::createWithFormat("Wave: %d", 0)->getCString(), "font_red_14.fnt");
        waveLabel = CCLabelTTF::create("Wave: 0", "Marker Felt", 24);
        waveLabel->setPosition(ccp(winSize.width - 100, winSize.height - 12));
        this->addChild(waveLabel);
        
        hpLabel = CCLabelTTF::create("Hp: 5", "Marker Felt", 24);
        hpLabel->setPosition(ccp(winSize.width - 300, winSize.height - 12));
        this->addChild(hpLabel);
        
        moneyLabel = CCLabelTTF::create("Money: 15", "Marker Felt", 24);
        moneyLabel->setPosition(ccp(winSize.width - 500, winSize.height - 12));
        this->addChild(moneyLabel);
        
        ret = true;
    } while (0);
    
    return ret;
}

void MenuLayer::setWaveLabel(int wave)
{
    waveLabel->setString(CCString::createWithFormat("Wave: %d", wave)->getCString());
}

void MenuLayer::setHpLabel(int hp)
{
    hpLabel->setString(CCString::createWithFormat("Hp: %d", hp)->getCString());
}

void MenuLayer::setMoneyLabel(int money)
{
    moneyLabel->setString(CCString::createWithFormat("Money: %d", money)->getCString());
}