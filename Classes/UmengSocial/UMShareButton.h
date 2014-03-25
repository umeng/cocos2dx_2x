//
//  UMShareButton.h
//  crossdemo
//
//  Created by mrsimple on 3/18/14.
//
//

#ifndef __crossdemo__UMShareButton__
#define __crossdemo__UMShareButton__

#include <iostream>
#include "cocos2d.h"
#include "CCUMSocialSDK.h"
#include <vector>

USING_NS_CC;
using namespace std;

class UMShareButton : public cocos2d::CCMenuItemImage
{
public:
    virtual  ~UMShareButton() ;
    
    /** creates a menu item with a normal and selected image*/
    static UMShareButton* create(const char *normalImage, const char *selectedImage, CCObject* target);
    
    // 设置友盟app key
    void setUmengAppkey(const char* appkey);
    // 设置文本内容
    void setShareContent(const char* text);
    // 可以设置本地图片和url图片, url图片必须以http://开头
    void setShareImage(const char* imgName);
    // 设置分享回调
    void setShareCallback(ShareEventHandler callback);

private:
    UMShareButton();
    void shareCallback(CCNode* pSender);
    vector<int>* mPlatforms;
    const char* mShareText;
    const char*  mImageName;
    const char*  mAppKey;
    ShareEventHandler mCallback ;
    CCUMSocialSDK *socialSDK ;
};

#endif /* defined(__crossdemo__UMShareButton__) */
