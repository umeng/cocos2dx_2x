//
//  ShareScene.cpp
//  UmengGame
//
//  Created by wangfei on 16/4/6.
//
//

#include "ShareScene.h"
#include "EntranceScene.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Cocos2dx/Common/CCUMSocialSDK.h"
USING_NS_CC;

USING_NS_UM_SOCIAL;

CCScene* Share::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    Share *layer = Share::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Share::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLabelTTF* pLabel = CCLabelTTF::create("分享界面", "Arial", 48);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    CCMenuItemFont *authButton = CCMenuItemFont::create("qq", this,
                                                        menu_selector(Share::qqShare));
    authButton->setPosition(ccp(visibleSize.width/2, 480));
    
    // 底层API分享
    CCMenuItemFont *shareButton = CCMenuItemFont::create("新浪", this,
                                                         menu_selector(Share::sinaShare));
    shareButton->setPosition(ccp(visibleSize.width/2, 400));
    
    // 授权某平台
    CCMenuItemFont *getInfoButton = CCMenuItemFont::create("微信", this,
                                                           menu_selector(Share::wxShare));
    getInfoButton->setPosition(ccp(visibleSize.width/2, 320));
    CCMenuItemFont *boardButton = CCMenuItemFont::create("打开分享面板", this,
                                                         menu_selector(Share::boardShare));
    boardButton->setPosition(ccp(visibleSize.width/2, 240));

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(Share::menuCloseCallback));
    
    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->addChild(getInfoButton, 1);
    pMenu->addChild(pCloseItem, 1);
    pMenu->addChild(shareButton, 1);
    pMenu->addChild(authButton, 1);
    pMenu->addChild(boardButton, 1);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}
/*
 * 分享回调
 * @param platform 要分享到的目标平台
 * @param stCode 返回码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 分享失败时的错误信息,android平台没有错误信息
 */
void shareCallback(int platform, int stCode, string& errorMsg) {
    
       CCLog("#### callback!!!!!!");
    string result = "";
    if (stCode == 100) {
        result = "开始分享";
        CCLog("#### HelloWorld 开始分享");
    } else if (stCode == 200) {
        result = "分享成功";
        CCLog("#### HelloWorld 分享成功 --> Cocos2d-x SDK ");
    } else {
        result = "分享失败";
        CCLog("#### HelloWorld 分享出错 --> Cocos2d-x SDK ");
        cout << errorMsg << endl;
    }
    
    istringstream is;
    is >> platform;
    result.append(is.str());
    CCLog("#### callback!!!!!! %s\n",result.c_str());
  
    CCLog("platform num is : %d, %d", platform, stCode);
    
}
void shareCallBack(int platform, int stCode, const char * errorMsg) {
    printf("%s\n", errorMsg);
}
void Share::qqShare(CCObject* pSender) {
    	CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    	sdk->directShare(QQ,
    			"Umeng Social Cocos2d-x SDK -->  qqshare   testing","title" ,"","",
    			share_selector(shareCallback));
    #elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    	sdk->setPlatformShareContent(SINA, "sina share 内容",
//    			"assets/CloseNormal.png", "sina-title");
//    	sdk->directShare(SINA, "Umeng Social Cocos2d-x SDK -->  directShare   testing", "http://www.baidu.com/img/bdlogo.gif", share_selector(shareCallback));
    #endif
 }
void Share::sinaShare(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    /*setSsoAuthorization方法是用来修改新浪的回调地址REDIRECT_URL,如果默认就是http://sns.whalecloud.com，可以不用修改*/
//    sdk->setSsoAuthorization(SINA, "http://sns.whalecloud.com");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sdk->directShare(SINA,
                     "Umeng Social Cocos2d-x SDK -->  qqshare   testing","title" ,"","",
                     share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    	sdk->setPlatformShareContent(SINA, "sina share 内容",
    //    			"assets/CloseNormal.png", "sina-title");
    //    	sdk->directShare(SINA, "Umeng Social Cocos2d-x SDK -->  directShare   testing", "http://www.baidu.com/img/bdlogo.gif", share_selector(shareCallback));
#endif
}
void Share::wxShare(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sdk->directShare(WEIXIN,
                     "Umeng Social Cocos2d-x SDK -->  qqshare   testing", "title" ,"","",
                     share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //    	sdk->setPlatformShareContent(SINA, "sina share 内容",
    //    			"assets/CloseNormal.png", "sina-title");
    //    	sdk->directShare(SINA, "Umeng Social Cocos2d-x SDK -->  directShare   testing", "http://www.baidu.com/img/bdlogo.gif", share_selector(shareCallback));
#endif
}
void Share::boardShare(CCObject* pSender) {
    CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
    vector<int>* platforms = new vector<int>();
    platforms->push_back(SINA);
    platforms->push_back(RENREN);
    platforms->push_back(DOUBAN);
    platforms->push_back(TENCENT_WEIBO);
    platforms->push_back(INSTAGRAM);
    platforms->push_back(QZONE);
    platforms->push_back(QQ);
    platforms->push_back(SMS);
    platforms->push_back(YIXIN);
    platforms->push_back(YIXIN_CIRCLE);
    platforms->push_back(LAIWANG);
    platforms->push_back(LAIWANG_CIRCLE);
    platforms->push_back(WEIXIN);
    platforms->push_back(WEIXIN_CIRCLE);
    platforms->push_back(TWITTER);
    platforms->push_back(FACEBOOK);
    sdk->setPlatforms(platforms);
    sdk->openShare(platforms, "来自分享面板", "title", "", "", share_selector(shareCallback));

}
void Share::menuCloseCallback(CCObject* pSender)
{
    CCTransitionScene * reScene = NULL;
    CCScene * s = Entrance::scene();
    float t = 1.2f;
    
    reScene = CCTransitionJumpZoom ::create(t , s);
    CCDirector::sharedDirector()->replaceScene(reScene);
}
