//
//  ShareScene.hpp
//  UmengGame
//
//  Created by wangfei on 16/4/6.
//
//

#ifndef ShareScene_hpp
#define ShareScene_hpp

#include "cocos2d.h"

class Share: public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    void qqShare(CCObject* pSender);
    void sinaShare(CCObject* pSender);
    void wxShare(CCObject* pSender);
    void boardShare(CCObject* pSender);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(Share);
};

#endif
