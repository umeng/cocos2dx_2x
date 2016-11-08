//
//  AuthScene.hpp
//  UmengGame
//
//  Created by wangfei on 16/4/6.
//
//

#ifndef __AUTH_SCENE_H__
#define __AUTH_SCENE_H__

#include "cocos2d.h"
using namespace std;
class Auth: public cocos2d::CCLayer
{
public:
  
    virtual bool init();

    static cocos2d::CCScene* scene();
    void qqAuth(CCObject* pSender);
    void sinaAuth(CCObject* pSender);
    void wxAuth(CCObject* pSender);
    void qqAuthDel(CCObject* pSender);
    void sinaAuthDel(CCObject* pSender);
    void wxAuthDel(CCObject* pSender);
    void doubanAuth(CCObject* pSender);
    void renrenAuth(CCObject* pSender);
    void facebookAuth(CCObject* pSender);
    void twitterAuth(CCObject* pSender);
    void doubanAuthDel(CCObject* pSender);
    void renrenAuthDel(CCObject* pSender);
    void facebookAuthDel(CCObject* pSender);
    void twitterAuthDel(CCObject* pSender);

   
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(Auth);
};

#endif
