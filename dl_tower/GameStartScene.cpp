#include "GameStartScene.h"
#include "SimpleAudioEngine.h"
#include "RunGameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameStart::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameStart *layer = GameStart::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameStart::init()
{
    do {
        
        CC_BREAK_IF(!CCLayerGradient::initWithColor(ccc4(0, 0, 0, 120), ccc4(255, 255, 255, 120)));
        
        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        
        
        
        // create menu, it's an autorelease object
        /*CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
         pMenu->setPosition( CCPointZero );
         this->addChild(pMenu, 1);*/
        
        /////////////////////////////
        // 3. add your codes below...
        
        // add a label shows "Hello World"
        // create and initialize a label
        CCLabelTTF* pLabel = CCLabelTTF::create("Dengle", "Thonburi", 34);
        
        // ask director the window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        
        // position the label on the center of the screen
        pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
        
        // add the label as a child to this layer
        this->addChild(pLabel, 1);
        
        // add "HelloWorld" splash screen"
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        
        // position the sprite on the center of the screen
        pSprite->setPosition( ccp(size.width/2, size.height/2) );
        
        
        // add a "close" icon to exit the progress. it's an autorelease object
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                              "CloseNormal.png",
                                                              "CloseSelected.png",
                                                              this,
                                                              menu_selector(GameStart::menuCloseCallback) );
        pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
        
        CCMenuItemImage *pGame1Item = CCMenuItemImage::create(
                                                              "button_game_start.png",
                                                              "button_press.png",
                                                              this,
                                                              menu_selector(GameStart::menuGame1Enter));
        pGame1Item->setPosition(ccp(size.width / 2, size.height / 2));
        // Game1 item
        CCMenu *pmenu = CCMenu::create(pCloseItem, pGame1Item, NULL);
        pmenu->setPosition(CCPointZero);
        // add the sprite as a child to this layer
        this->addChild(pmenu, 0);
    } while(0);
    return true;
}

void GameStart::menuGame1Enter(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(2, RunGameScene::create()));
}

void GameStart::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

