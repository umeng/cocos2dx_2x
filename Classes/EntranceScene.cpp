//
//  EntranceScene.cpp
//  UmengGame
//
//  Created by wangfei on 16/4/6.
//
//

#include "EntranceScene.h"
#include "AuthScene.h"
#include "ShareScene.h"
#include "GetScene.h"
USING_NS_CC;

CCScene* Entrance::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    Entrance *layer = Entrance::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Entrance::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCLabelTTF* pLabel = CCLabelTTF::create("UM-Cocos2dx-Social", "Arial", 48);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    CCMenuItemFont *authButton = CCMenuItemFont::create("授权", this,
                                                             menu_selector(Entrance::gotoAuth));

    authButton->setPosition(ccp(visibleSize.width/2, 680));

    // 底层API分享
    CCMenuItemFont *shareButton = CCMenuItemFont::create("分享", this,
                                                              menu_selector(Entrance::gotoShare));
    shareButton->setPosition(ccp(visibleSize.width/2, 500));

    // 授权某平台
    CCMenuItemFont *getInfoButton = CCMenuItemFont::create("获取用户信息", this,
                                                            menu_selector(Entrance::gotoGetPlatform));
    getInfoButton->setPosition(ccp(visibleSize.width/2, 320));

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(Entrance::menuCloseCallback));
    
    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
   
    CCMenu* pMenu = CCMenu::create();
    pMenu->addChild(getInfoButton, 1);
    pMenu->addChild(pCloseItem, 1);
    pMenu->addChild(shareButton, 1);
    pMenu->addChild(authButton, 1);
    pMenu->setPosition(CCPointZero);
this->addChild(pMenu, 1);
    return true;
}

void Entrance::gotoAuth(CCObject* pSender) {
    CCTransitionScene * reScene = NULL;
    CCScene * s = Auth::scene();
    float t = 1.2f;
   
    reScene = CCTransitionJumpZoom ::create(t , s);
    CCDirector::sharedDirector()->replaceScene(reScene);
}
void Entrance::gotoShare(CCObject* pSender) {
    CCTransitionScene * reScene = NULL;
    CCScene * s = Share::scene();
    float t = 1.2f;
    
    reScene = CCTransitionJumpZoom ::create(t , s);
    CCDirector::sharedDirector()->replaceScene(reScene);
}
void Entrance::gotoGetPlatform(CCObject* pSender) {
    CCTransitionScene * reScene = NULL;
    CCScene * s = Get::scene();
    float t = 1.2f;
    
    reScene = CCTransitionJumpZoom ::create(t , s);
    CCDirector::sharedDirector()->replaceScene(reScene);
}
void Entrance::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

