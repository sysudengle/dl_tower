//
//  TouchLayer.h
//  dl_tower
//
//  Created by user on 13-10-17.
//
//

#ifndef __dl_tower__TouchLayer__
#define __dl_tower__TouchLayer__

#include "TouchLayerDelegate.h"

USING_NS_CC;

//class TouchLayerDelegate;
class TouchLayer: public CCLayer
{
public:
    CC_SYNTHESIZE(TouchLayerDelegate *, m_pDelegate, Delegate);
    
    bool init();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    //virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void onExit();
    NODE_FUNC(TouchLayer);
};


#endif /* defined(__dl_tower__TouchLayer__) */
