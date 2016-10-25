//
//  UmSocialControllerIOS.cpp
//  UmengGame
//
//  Created by 张梓琦 on 14-3-16.
//
//

#include "UmSocialControllerIOS.h"
#import <UIKit/UIKit.h>
#import <UMSocialCore/UMSocialCore.h>
//#import "UMSocialTencentWeiboHandler.h"

#define UMSYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)

string UmSocialControllerIOS::m_appKey = "";
//UMSocialUIDelegateObject * UmSocialControllerIOS::m_socialDelegate = nil;

int getPlatformString(int platform){
    int const platforms[17] = {
        UMSocialPlatformType_Sina
        , UMSocialPlatformType_WechatSession
        , UMSocialPlatformType_WechatTimeLine
        , UMSocialPlatformType_QQ
        , UMSocialPlatformType_Qzone
        , UMSocialPlatformType_Renren
        , UMSocialPlatformType_Douban
        , UMSocialPlatformType_Facebook
        , UMSocialPlatformType_Twitter
      };
    
    return platforms[platform];
}

NSString* getNSStringFromCString(const char* cstr){
    if (cstr) {
        return [NSString stringWithUTF8String:cstr];
    }
    return nil;
}

UIViewController* getViewController(){
    UIViewController* ctrol = nil;
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        NSArray* array=[[UIApplication sharedApplication]windows];
        UIWindow* win=[array objectAtIndex:0];
        
        UIView* ui=[[win subviews] objectAtIndex:0];
        ctrol=(UIViewController*)[ui nextResponder];
    }
    else
    {
        // use this method on ios6
        ctrol=[UIApplication sharedApplication].keyWindow.rootViewController;
    }
    return ctrol;
}



void UmSocialControllerIOS::initCocos2dxSDK(const char *sdkType, const char *version){
  [UMSocialGlobal shareInstance].type = @"react native";
    
}

void UmSocialControllerIOS::setTargetUrl(const char *targetUrl){
  }

//bool UmSocialControllerIOS::openURL(const char *url){
//    
//    NSString *urlString = [[NSString alloc] initWithBytes:url length:strlen(url) encoding:NSUTF8StringEncoding];
//    NSURL *urlPath = [NSURL URLWithString:urlString];
//    return (bool)[UMSocialSnsService handleOpenURL:urlPath wxApiDelegate:nil];
//    return false;
//}





UIImage * formatImage(id image) {
    UIImage *retImage = image;
    if ([image isKindOfClass:[UIImage class]]) {
        retImage = [UIImage imageWithData:UIImagePNGRepresentation(image)];
    } else if ([image isKindOfClass:[NSData class]]) {
        retImage = [UIImage imageWithData:image];
    }
    return retImage;
}

void UmSocialControllerIOS::setPlatformShareContent(int platform, const char* text,
                                                                const char* imagePath, const char* title ,
                                                    const char* targetUrl){
   
}








void UmSocialControllerIOS::authorize(int platform, AuthEventHandler callback){
    
  
}

void UmSocialControllerIOS::deleteAuthorization(int platform, AuthEventHandler callback){
   
}

bool UmSocialControllerIOS::isAuthorized(int platform){
   
    
    return YES;
}

void UmSocialControllerIOS::openShareWithImagePath(vector<int>* platforms, const char* text, const char* imagePath,ShareEventHandler callback){
    
  }

void UmSocialControllerIOS::setSharePlatforms(vector<int>* platform)
{
   }


void UmSocialControllerIOS::openLog(bool flag)
{
   [[UMSocialManager defaultManager] openLog:YES];
}

void UmSocialControllerIOS::directShare(const char* text, const char* imagePath,int platform, ShareEventHandler callback){
    
   
}
