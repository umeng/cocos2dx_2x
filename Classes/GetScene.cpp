//
//  GetScene.cpp
//  UmengGame
//
//  Created by wangfei on 16/4/6.
//
//

#include "GetScene.h"
#include "EntranceScene.h"
USING_NS_CC;

CCScene* Get::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    Get *layer = Get::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Get::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLabelTTF* pLabel = CCLabelTTF::create("获取用户信息界面", "Arial", 48);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    CCMenuItemFont *authButton = CCMenuItemFont::create("qq", this,
                                                        menu_selector(Get::qqGet));
    authButton->setPosition(ccp(visibleSize.width/2, 480));
    
    // 底层API分享
    CCMenuItemFont *shareButton = CCMenuItemFont::create("新浪", this,
                                                         menu_selector(Get::sinaGet));
    shareButton->setPosition(ccp(visibleSize.width/2, 400));
    
    // 授权某平台
    CCMenuItemFont *getInfoButton = CCMenuItemFont::create("微信", this,
                                                           menu_selector(Get::wxGet));
    getInfoButton->setPosition(ccp(visibleSize.width/2, 320));
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(Get::menuCloseCallback));
    
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
void Get::qqGet(CCObject* pSender) {
    
}
void Get::sinaGet(CCObject* pSender) {
    
}
void Get::wxGet(CCObject* pSender) {
    
}

void Get::menuCloseCallback(CCObject* pSender)
{
    CCTransitionScene * reScene = NULL;
    CCScene * s = Entrance::scene();
    float t = 1.2f;
    
    reScene = CCTransitionJumpZoom ::create(t , s);
    CCDirector::sharedDirector()->replaceScene(reScene);
}
