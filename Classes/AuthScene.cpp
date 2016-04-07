//
//  AuthScene.cpp
//  UmengGame
//
//  Created by wangfei on 16/4/6.
//
//

#include "AuthScene.h"
#include "EntranceScene.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Cocos2dx/Common/CCUMSocialSDK.h"
USING_NS_CC;

USING_NS_UM_SOCIAL;
// 环境变量PATH在windows下和linux下的分割符定义
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

CCScene* Auth::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    Auth *layer = Auth::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Auth::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
       CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLabelTTF* pLabel = CCLabelTTF::create("授权界面", "Arial", 48);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    CCMenuItemFont *qqButton = CCMenuItemFont::create("qq授权", this,
                                                        menu_selector(Auth::qqAuth));
    qqButton->setPosition(ccp(visibleSize.width/2-qqButton->getContentSize().width, 480));
    
    // 底层API分享
    CCMenuItemFont *sinaButton = CCMenuItemFont::create("新浪授权", this,
                                                         menu_selector(Auth::sinaAuth));
    sinaButton->setPosition(ccp(visibleSize.width/2-sinaButton->getContentSize().width, 400));
    
    // 授权某平台
    CCMenuItemFont *wxButton = CCMenuItemFont::create("微信授权", this,
                                                           menu_selector(Auth::wxAuth));
    wxButton->setPosition(ccp(visibleSize.width/2-wxButton->getContentSize().width, 320));
    CCMenuItemFont *doubanButton = CCMenuItemFont::create("豆瓣授权", this,
                                                      menu_selector(Auth::doubanAuth));
    doubanButton->setPosition(ccp(visibleSize.width/2-doubanButton->getContentSize().width, 240));
    CCMenuItemFont *renrenButton = CCMenuItemFont::create("人人授权", this,
                                                      menu_selector(Auth::renrenAuth));
    renrenButton->setPosition(ccp(visibleSize.width/2-renrenButton->getContentSize().width, 160));
    CCMenuItemFont *facebookButton = CCMenuItemFont::create("facebook授权", this,
                                                      menu_selector(Auth::facebookAuth));
    facebookButton->setPosition(ccp(visibleSize.width/2-facebookButton->getContentSize().width, 80));
    
    CCMenuItemFont *delqqButton = CCMenuItemFont::create("qq删除授权", this,
                                                        menu_selector(Auth::qqAuthDel));
    delqqButton->setPosition(ccp(visibleSize.width/2+delqqButton->getContentSize().width, 480));
    
    // 底层API分享
    CCMenuItemFont *delsinaButton = CCMenuItemFont::create("新浪删除授权", this,
                                                         menu_selector(Auth::sinaAuthDel));
    delsinaButton->setPosition(ccp(visibleSize.width/2+delsinaButton->getContentSize().width, 400));
    
    // 授权某平台
    CCMenuItemFont *delwxButton = CCMenuItemFont::create("微信删除授权", this,
                                                           menu_selector(Auth::wxAuthDel));
    delwxButton->setPosition(ccp(visibleSize.width/2+delwxButton->getContentSize().width, 320));
    CCMenuItemFont *deldoubanButton = CCMenuItemFont::create("豆瓣删除授权", this,
                                                          menu_selector(Auth::doubanAuthDel));
    deldoubanButton->setPosition(ccp(visibleSize.width/2+doubanButton->getContentSize().width, 240));
    CCMenuItemFont *delrenrenButton = CCMenuItemFont::create("人人删除授权", this,
                                                          menu_selector(Auth::renrenAuthDel));
    delrenrenButton->setPosition(ccp(visibleSize.width/2+renrenButton->getContentSize().width, 160));
    CCMenuItemFont *delfacebookButton = CCMenuItemFont::create("facebook删除授权", this,
                                                            menu_selector(Auth::facebookAuthDel));
    delfacebookButton->setPosition(ccp(visibleSize.width/2+facebookButton->getContentSize().width, 80));
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(Auth::menuCloseCallback));
    
    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->addChild(qqButton, 1);
    pMenu->addChild(pCloseItem, 1);
    pMenu->addChild(sinaButton, 1);
    pMenu->addChild(wxButton, 1);
    pMenu->addChild(delqqButton, 1);
    pMenu->addChild(delsinaButton, 1);
    pMenu->addChild(delwxButton, 1);
    
    pMenu->addChild(doubanButton, 1);
    pMenu->addChild(renrenButton, 1);
    pMenu->addChild(facebookButton, 1);
    pMenu->addChild(deldoubanButton, 1);
    pMenu->addChild(delrenrenButton, 1);
    pMenu->addChild(delfacebookButton, 1);
    pMenu->setPosition(CCPointZero);

    this->addChild(pMenu, 1);
    
    return true;
}
/*
 *授权回调
 * @param platform 要授权的平台
 * @param stCode 返回码, 200代表授权成功, 100代表开始授权, 0代表授权出错, -1代表取消授权
 * @param data 授权时返回的数据
 */
void authCallback(int platform, int stCode, map<string, string>& data) {
    if (stCode == 100) {
        CCLog("#### 授权开始");
    } else if (stCode == 200) {
        CCLog("#### 授权完成");
    } else if (stCode == 0) {
        CCLog("#### 授权出错");
    } else if (stCode == -1) {
        CCLog("#### 取消授权");
    }
    
    // 输入授权数据, 如果授权失败,则会输出错误信息
    map<string, string>::iterator it = data.begin();
    for (; it != data.end(); ++it) {
        CCLog("#### data  %s -> %s.", it->first.c_str(), it->second.c_str());
    }
}
void authCallBack(int platform, int stCode, const char* usid,
                  const char *token) {
    printf("%d %d %s %s", platform, stCode, usid, token);
}






void Auth::qqAuth(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("授权");
    sdk->authorize(QQ, auth_selector(authCallback));
}
void Auth::sinaAuth(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("授权");
    sdk->authorize(SINA, auth_selector(authCallback));
}
void Auth::wxAuth(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("授权");
    sdk->authorize(WEIXIN, auth_selector(authCallback));
}
void Auth::qqAuthDel(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("删除授权");
    sdk->deleteAuthorization(QQ, auth_selector(authCallback));
}
void Auth::sinaAuthDel(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("删除授权");
    sdk->deleteAuthorization(SINA, auth_selector(authCallback));
}
void Auth::wxAuthDel(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("删除授权");
    sdk->deleteAuthorization(WEIXIN, auth_selector(authCallback));
}
void Auth::doubanAuth(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("授权");
    sdk->authorize(DOUBAN, auth_selector(authCallback));
}
void Auth::renrenAuth(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("授权");
    sdk->authorize(RENREN, auth_selector(authCallback));
}
void Auth::facebookAuth(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("授权");
    sdk->authorize(FACEBOOK, auth_selector(authCallback));
}
void Auth::doubanAuthDel(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("删除授权");
    sdk->deleteAuthorization(DOUBAN, auth_selector(authCallback));
}
void Auth::renrenAuthDel(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("删除授权");
    sdk->deleteAuthorization(RENREN, auth_selector(authCallback));
}
void Auth::facebookAuthDel(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    CCLog("删除授权");
    sdk->deleteAuthorization(FACEBOOK, auth_selector(authCallback));
}
void Auth::menuCloseCallback(CCObject* pSender)
{
    CCTransitionScene * reScene = NULL;
    CCScene * s = Entrance::scene();
    float t = 1.2f;
    
    reScene = CCTransitionJumpZoom ::create(t , s);
    CCDirector::sharedDirector()->replaceScene(reScene);
}

