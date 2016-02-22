#include "HelloWorldScene.h"
#include <string>
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
#include <iostream>
#include <vector>
#include <map>

// 环境变量PATH在windows下和linux下的分割符定义
#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

USING_NS_CC;
using namespace std;
// 使用友盟命令空间 
USING_NS_UM_SOCIAL;
// layer tag
int layerTag = 123;
// label tag
int labelTag = 456;

CCScene* HelloWorld::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();
	layer->setTag(layerTag);
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
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

/*
 * 分享回调
 * @param platform 要分享到的目标平台
 * @param stCode 返回码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 分享失败时的错误信息,android平台没有错误信息
 */
void shareCallback(int platform, int stCode, string& errorMsg) {
	HelloWorld* hwLayer =
			(HelloWorld*) CCDirector::sharedDirector()->getRunningScene()->getChildByTag(
					layerTag);
	CCLabelTTF* item = (CCLabelTTF*) hwLayer->getChildByTag(labelTag);
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

	item->setString(result.c_str());
	CCLog("platform num is : %d, %d", platform, stCode);

}

void shareCallBack(int platform, int stCode, const char * errorMsg) {
	printf("%s\n", errorMsg);
}

void authCallBack(int platform, int stCode, const char* usid,
		const char *token) {
	printf("%d %d %s %s", platform, stCode, usid, token);
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init()) {
		return false;
	}
	// ********************  设置友盟的app key以及相关的信息  ***********************************
	// 获取CCUMSocialSDK对象, 如果使用的UMShareButton, 则通过UMShareButton对象的getSocialSDK()方法获取.
	CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	sdk->setTargetUrl("http://www.umeng.com/social");
	//    // 设置QQ的app id, app key
	sdk->setQQAppIdAndAppKey("100424468", "c7394704798a158208a74ab60104f0ba");
	// 设置微信的app id, app key
	sdk->setWeiXinAppInfo("wxdc1e388c3822c80b",
			"a393c1527aaccb95f3a4c88d6d1455f6");
    // 设置新浪微博appkey, appsecret, redirectURL
    sdk->setSinaAppKey("3921700954", "04b48b094faeb16683c32669824ebdad", "http://sns.whalecloud.com/sina2/callback");
	// 设置易信的app key
	sdk->setYiXinAppKey("yx52dd5c14bbb3430b93e6f2dafcbcc68d");
	// 设置来往的app id等信息
    sdk->setLaiwangAppInfo("8112117817424282305", "9996ed5039e641658de7b83345fee6c9", "友盟社会化组件");
	// 设置facebook的app id
	sdk->setFacebookAppId("506027402887373");
	// 设置人人网SSO授权的app id, app key, app secret
	sdk->setRenrenAppInfo("272694", "44b2d8a028fe499db326c77a6ec24350",
			"e2fd480e33104a5da5c6249480d39d90");
	sdk->openTwitterForiOS("fB5tvRpna1CKK97xZUslbxiet", "YcbSvseLIwZ4hZg9YmgJPP5uWzd4zr6BpBKGZhf07zzh3oj62K");
	// 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// 打开分享面板
	CCMenuItemFont *shareTextButton = CCMenuItemFont::create("打开分享面板", this,
			menu_selector(HelloWorld::menuShareCallback));
	shareTextButton->setPosition(ccp(150, 480));

	// 底层API分享
	CCMenuItemFont *directTextButton = CCMenuItemFont::create("底层分享", this,
			menu_selector(HelloWorld::directShareCallback));
	directTextButton->setPosition(ccp(150, 400));

	// 授权某平台
	CCMenuItemFont *authTextButton = CCMenuItemFont::create("授权某平台", this,
			menu_selector(HelloWorld::authorizeCallback));
	authTextButton->setPosition(ccp(150, 320));

	// 删除某平台授权
	CCMenuItemFont *delAuthTextButton = CCMenuItemFont::create("删除某平台删除", this,
			menu_selector(HelloWorld::deleteAuthorizeCallback));
	delAuthTextButton->setPosition(ccp(150, 240));

	// 判断某平台是否授权
	CCMenuItemFont *isAuthTextButton = CCMenuItemFont::create("判断某平台是否授权", this,
			menu_selector(HelloWorld::isAuthorizedShareCallback));
	isAuthTextButton->setPosition(ccp(150, 160));

	// ********************************************************************************

	// 打开或者关闭log
	sdk->setLogEnable(true);

	// 关闭按钮
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", this,
			menu_selector(HelloWorld::menuCloseCallback));
	CCSize size(100, 100);
	pCloseItem->setContentSize(size);
	pCloseItem->setPosition(
			ccp(
					origin.x + visibleSize.width
							- pCloseItem->getContentSize().width / 2,
					origin.y + pCloseItem->getContentSize().height / 2));

	// 友盟share button, 参数1为正常情况下的图片, 参数2为用户点击后的图片, 参数3为友盟app key, 参数四为分享回调.
	UMShareButton *shareButton = UMShareButton::create("share.png",
			"CloseSelected.png", "4eaee02c527015373b000003",
			share_selector(shareCallback));
	vector<int>* platforms = new vector<int>();
	platforms->push_back(SINA);
	platforms->push_back(FACEBOOK);
//	platforms->push_back(INSTAGRAM);
	platforms->push_back(QZONE);
	platforms->push_back(QQ);
	platforms->push_back(YIXIN_CIRCLE);
	platforms->push_back(YIXIN);
	platforms->push_back(WEIXIN);
	// 设置平台
	shareButton->setPlatforms(platforms);
	// 设置分享内容
	shareButton->setShareContent("这是通过UMShareButton设置的分享内容");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	shareButton->setShareImage(NULL);

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	shareButton->setShareImage("share.png");

#endif

	// 设置分享回调
	shareButton->setShareCallback(share_selector(shareCallback));
	shareButton->setPosition(ccp(480, 150));

	CCMenuItemFont *umshareTextButton = CCMenuItemFont::create("友盟ShareButton");
	umshareTextButton->setPosition(ccp(480, 60));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create();
	pMenu->addChild(pCloseItem, 1);
	// 友盟share button
	pMenu->addChild(shareButton, 1);
	pMenu->addChild(umshareTextButton, 1);

	// 文字按钮
	pMenu->addChild(shareTextButton, 1);
	pMenu->addChild(directTextButton, 1);
	pMenu->addChild(authTextButton, 1);
	pMenu->addChild(delAuthTextButton, 1);
	pMenu->addChild(isAuthTextButton, 1);

	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	CCLabelTTF* pLabel = CCLabelTTF::create("Umeng Social Cocos2d-x SDK",
			"Arial", 34);
	pLabel->setTag(labelTag);
	// position the label on the center of the screen
	pLabel->setPosition(
			ccp(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height
							- pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(
			ccp(visibleSize.width / 2 + origin.x,
					visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	return true;
}

// 直接分享的按钮回调
void HelloWorld::directShareCallback(CCObject* pSender) {

	CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	sdk->directShare(QQ,
			"Umeng Social Cocos2d-x SDK -->  directShare   testing", "sdfsd",
			share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    setAppKey("4eaee02c527015373b000003");
//    int platform[2] = {0,1};
//    openShareWithImagePath(platform, 2, "share text", "cat.gif", NULL);

	sdk->setPlatformShareContent(SINA, "sina share 内容",
			"assets/CloseNormal.png", "sina-title");

	sdk->directShare(SINA, "Umeng Social Cocos2d-x SDK -->  directShare   testing", "http://www.baidu.com/img/bdlogo.gif", share_selector(shareCallback));
#endif
}

// 授权某个平台的按钮回调
void HelloWorld::authorizeCallback(CCObject* pSender) {

	static int count = 0;
	CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	CCLog("授权");
	sdk->authorize(QQ, auth_selector(authCallback));
}

// 删除某个平台的按钮回调
void HelloWorld::deleteAuthorizeCallback(CCObject* pSender) {
	CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	CCLog("删除腾讯微博授权");
	sdk->deleteAuthorization(SINA, auth_selector(authCallback));
}

// 判断某个平台的按钮回调
void HelloWorld::isAuthorizedShareCallback(CCObject* pSender) {
	CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	CCLog("@@@@ 判断新浪微博是否授权");
	bool isAuthorized = sdk->isAuthorized(QQ);
	if (isAuthorized) {
		CCLog("@@ 新浪微博已经授权");
	} else {
		CCLog("@@ 新浪微博还没有授权");
	}
}

// 弹出分享面板
void HelloWorld::menuShareCallback(CCObject* pSender) {
	CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	vector<int>* platforms = new vector<int>();
	platforms->push_back(SINA);
	platforms->push_back(RENREN);
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
	// 设置平台
	sdk->setPlatforms(platforms);

	// 设置新浪微博SSO登录
	sdk->setSsoAuthorization(RENREN, "http://sns.whalecloud.com");
	//
	sdk->setPlatformShareContent(SINA, "sina share 内容",
			"", "");
	//
	sdk->setPlatformShareContent(WEIXIN_CIRCLE, "WEIXIN share 内容",
			"assets/CloseNormal.png", "WEIXIN share 标题",
			"http://blog.csdn.net/bboyfeiyu");
    //
    sdk->setPlatformShareContent(QQ, "", "http://www.umeng.com/images/pic/home/social/img-1.png",
                                 "", "");
    sdk->setPlatformShareContent(SMS, "QQ hello", "http://www.umeng.com/images/pic/home/social/img-1.png","", "");
	sdk->setPlatformShareContent(RENREN, "renren share 内容",
			"assets/CloseNormal.png", "QQ-title",
			"http://blog.csdn.net/bboyfeiyu");
	sdk->setPlatformShareContent(DOUBAN, "douban share 内容",
			"assets/CloseNormal.png", "QQ-title",
			"http://blog.csdn.net/bboyfeiyu");

	// 打开分享面板, 注册分享回调, android 和 IOS的图片地址格式不一致，因此分开设置
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	sdk->openShare("这是文本分享内容",
			"http://www.umeng.com/images/pic/home/social/img-1.png",
			share_selector(shareCallback));

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	printf("CC_PLATFORM_IOS !!!\n");
//    this->saveScreenshot();
//    setAppKey("4eaee02c527015373b000003");
//    int platform[2] = {SINA,TENCENT_WEIBO};
	sdk->openShare("Umeng Social Cocos2d-x SDK V1.0","share.png", share_selector(shareCallback));
#endif
}

/**
 * 截图功能
 */
void HelloWorld::saveScreenshot() {
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCRenderTexture* texture = CCRenderTexture::create((int) size.width,
			(int) size.height);
	texture->setPosition(ccp(size.width / 2, size.height / 2));
	texture->begin();
	CCDirector::sharedDirector()->getRunningScene()->visit();
	texture->end();
	string imagePath =
			CCFileUtils::sharedFileUtils()->getWritablePath().c_str();
		//保存为png
	bool result = texture->saveToFile("screenshot.png", kCCImageFormatPNG);
	if (result) {
		imagePath += "screenshot.png";

	}
	CCUMSocialSDK *sdk = CCUMSocialSDK::create("4eaee02c527015373b000003");
	sdk->directShare(SINA,
			"Umeng Social Cocos2d-x SDK -->  directShare   testing",
			imagePath.c_str(), share_selector(shareCallback));
}

void HelloWorld::menuCloseCallback(CCObject* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}
