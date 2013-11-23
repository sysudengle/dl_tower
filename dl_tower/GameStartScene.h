#ifndef __GAMESTART_SCENE_H__
#define __GAMESTART_SCENE_H__

#include "cocos2d.h"

class GameStart : public cocos2d::CCLayerGradient
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    //void startGame(CCNode *sender);
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    void menuGame1Enter(CCObject* pSender);
    CREATE_FUNC(GameStart);
};

#endif // __HELLOWORLD_SCENE_H__
