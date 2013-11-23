//
//  TouchLayerDelegate.h
//  dl_tower
//
//  Created by user on 13-10-17.
//
//

#ifndef __dl_tower__TouchLayerDelegate__
#define __dl_tower__TouchLayerDelegate__

#include "cocos2d.h"

USING_NS_CC;

class TouchLayerDelegate
{
public:
    virtual void singleTouchDirecting(CCPoint point) = 0;
};


#endif /* defined(__dl_tower__TouchLayerDelegate__) */
