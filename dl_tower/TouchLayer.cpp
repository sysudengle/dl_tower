//
//  TouchLayer.cpp
//  dl_tower
//
//  Created by user on 13-10-17.
//
//

#include "TouchLayer.h"

USING_NS_CC;


bool TouchLayer::init()
{
    bool ret = false;
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        this->registerWithTouchDispatcher();
        this->setDelegate(NULL);
        ret = true;
    } while (0);
    
    return ret;
}

void TouchLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if(pTouches->count() == 1)
    {
        CCTouch *touch = dynamic_cast<CCTouch *>(pTouches->anyObject());
        CCPoint position = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        CCLog("Touch !");
        if(this->getDelegate())
        {
            CCLog("Touch 2~");
            this->getDelegate()->singleTouchDirecting(position);
        }
    }
}


void TouchLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}