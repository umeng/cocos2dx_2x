//
//  UMSocialCSDK.cpp
//  UmengGame
//
//  Created by yeahugo on 14-6-26.
//
//

#include "UMSocialCSDK.h"
#import "UMSocial.h"
#import "UMSocialUIObject.h"
#import "UMSocialCObject.h"

#import "UMSocialQQHandler.h"
#import "UMSocialWechatHandler.h"
#import "UMSocialLaiwangHandler.h"
#import "UMSocialYiXinHandler.h"
#import "UMSocialFacebookHandler.h"
#import "UMSocialTwitterHandler.h"
#import "UMSocialInstagramHandler.h"

static char * AppKey = NULL;

NSString* getNSStringFromCStr(const char* cstr){
    if (cstr) {
        return [NSString stringWithUTF8String:cstr];
    }
    return nil;
}

NSString* getPlatformNSString(int platform){
    NSString *const platforms[17] = {
        UMShareToSina
        , UMShareToWechatSession
        , UMShareToWechatTimeline
        , UMShareToQQ
        , UMShareToQzone
        , UMShareToRenren
        , UMShareToDouban
        , UMShareToLWSession
        , UMShareToLWTimeline
        , UMShareToYXSession
        , UMShareToYXTimeline
        , UMShareToFacebook
        , UMShareToTwitter
        , UMShareToInstagram
        , UMShareToSms
        , UMShareToEmail
        , UMShareToTencent};
    
    return platforms[platform];
}

UIViewController* getCurrentViewController(){
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


void setAppKey(const char* appKey)
{
    AppKey = (char *)malloc(strlen(appKey) + 1);
    strcpy(AppKey, appKey);
    [UMSocialData setAppKey:[NSString stringWithUTF8String:appKey]];
}

void initCocos2dxSDK(const char *sdkType, const char *version)
{
    [[UMSocialData defaultData] performSelector:@selector(setSdkType:version:) withObject:getNSStringFromCStr(sdkType) withObject:getNSStringFromCStr(version)];
}

void setTargetUrl(const char *targetUrl){
    [UMSocialData defaultData].extConfig.wechatSessionData.url = getNSStringFromCStr(targetUrl);
    [UMSocialData defaultData].extConfig.wechatTimelineData.url = getNSStringFromCStr(targetUrl);
    [UMSocialData defaultData].extConfig.wechatFavoriteData.url = getNSStringFromCStr(targetUrl);
    [UMSocialData defaultData].extConfig.qqData.url = getNSStringFromCStr(targetUrl);
    [UMSocialData defaultData].extConfig.qzoneData.url = getNSStringFromCStr(targetUrl);
    [UMSocialData defaultData].extConfig.lwsessionData.url =getNSStringFromCStr(targetUrl);
    [UMSocialData defaultData].extConfig.lwtimelineData.url =getNSStringFromCStr(targetUrl);
    [UMSocialData defaultData].extConfig.yxsessionData.url =getNSStringFromCStr(targetUrl);
    [UMSocialData defaultData].extConfig.yxtimelineData.url =getNSStringFromCStr(targetUrl);
    [UMSocialData defaultData].extConfig.facebookData.urlString =getNSStringFromCStr(targetUrl);
}

void authorize(int platform, AuthHandler callback){
    
    UMSocialSnsPlatform *snsPlatform = [UMSocialSnsPlatformManager getSocialPlatformWithName:getPlatformNSString(platform)];
    
    
    auto ctrol = getCurrentViewController();
    [UMSocialConfig setSupportedInterfaceOrientations:UIInterfaceOrientationMaskAll];
    snsPlatform.loginClickHandler(ctrol,[UMSocialControllerService defaultControllerService],YES,^(UMSocialResponseEntity *response)
                                  {
                                      if (callback) {
                                          if (response.responseCode == UMSResponseCodeSuccess) {
                                              UMSocialAccountEntity *snsAccount = [[UMSocialAccountManager socialAccountDictionary] valueForKey:snsPlatform.platformName];
                                              callback(platform,response.responseCode,snsAccount.usid.UTF8String,snsAccount.accessToken.UTF8String);
                                          } else {
                                              callback(platform,response.responseCode,NULL,NULL);
                                          }
                                      }
                                  });
}

void deleteAuthorization(int platform, AuthHandler callback){
    [[UMSocialDataService defaultDataService] requestUnOauthWithType:getPlatformNSString(platform)  completion:^(UMSocialResponseEntity *response){
     if (callback) {
     callback(platform, (int)response.responseCode,NULL,NULL);
     }
     }
     ];
}

bool isAuthorized(int platform){
    BOOL isOauth = [UMSocialAccountManager isOauthWithPlatform:getPlatformNSString(platform)];
    
    return isOauth == YES;
}

id getImageFromFilePath(const char* imagePath){
    id returnImage = nil;
    if (imagePath) {
        NSString *imageString = getNSStringFromCStr(imagePath);
        if ([imageString.lowercaseString hasSuffix:@".gif"]) {
            NSString *path = [[NSBundle mainBundle] pathForResource:[[imageString componentsSeparatedByString:@"."] objectAtIndex:0]
                                                             ofType:@"gif"];
            
            returnImage = [NSData dataWithContentsOfFile:path];
        } else if ([imageString rangeOfString:@"/"].length > 0){
            returnImage = [NSData dataWithContentsOfFile:imageString];
        } else {
            returnImage = [UIImage imageNamed:imageString];
        }
        NSLog(@"return Image is %@",returnImage);
        [UMSocialData defaultData].urlResource.resourceType = UMSocialUrlResourceTypeDefault;
    }
    return returnImage;
}

void openShareWithImagePath(int platform[], int platformNum, const char* text, const char* imagePath,ShareHandler callback)
{
    if (AppKey == NULL) {
        NSLog(@"请设置友盟AppKey到UMShareButton对象.");
        return ;
    }
    
    NSMutableArray* array = [NSMutableArray array];
    for (unsigned int i = 0; i < platformNum; i++) {
        [array addObject:getPlatformNSString(platform[i])];
    }
    
    id image = nil;
    NSString *imageString = getNSStringFromCStr(imagePath);
    if ([imageString hasPrefix:@"http://"] || [imageString hasPrefix:@"https://"]) {
        [[UMSocialData defaultData].urlResource setResourceType:UMSocialUrlResourceTypeImage url:imageString];
    } else {
        image = getImageFromFilePath(imagePath);
    }
    
    UMSocialCObject * delegate = nil;
    if (callback) {
        delegate = [[UMSocialCObject alloc] initWithCallback:callback];
    }
    
    NSString *appKey = nil;
    NSString *shareText = nil;
    if (AppKey != NULL) {
        appKey = [NSString stringWithUTF8String:AppKey];
    }
    if (text) {
        shareText = [NSString stringWithUTF8String:text];
    }
    
    [UMSocialSnsService presentSnsIconSheetView:getCurrentViewController()
                                         appKey:appKey
                                      shareText:shareText
                                     shareImage:image
                                shareToSnsNames:array
                                       delegate:delegate];
    [UMSocialConfig setSupportedInterfaceOrientations:UIInterfaceOrientationMaskAll];
    if (delegate) {
        [delegate release];
    }
}

void openLog(int flag)
{
    if (flag) {
        [UMSocialData openLog:flag];
    }
}

void directShare(const char* text, const char* imagePath,int platform, ShareEventHandler callback){
    
    if (AppKey == NULL) {
        NSLog(@"请设置友盟AppKey到UMShareButton对象.");
        return ;
    }
    UMSocialUrlResource *urlResource = nil;
    id image = nil;
    NSString *imageString = getNSStringFromCStr(imagePath);
    if ([imageString hasPrefix:@"http://"] || [imageString hasPrefix:@"https://"]) {
        urlResource = [[UMSocialUrlResource alloc] initWithSnsResourceType:UMSocialUrlResourceTypeImage url:imageString];
        [[UMSocialData defaultData].urlResource setResourceType:UMSocialUrlResourceTypeImage url:imageString];
    } else {
        image = getImageFromFilePath(imagePath);
    }
    
    [UMSocialConfig setSupportedInterfaceOrientations:UIInterfaceOrientationMaskAll];
    
    NSString *shareText = nil;
    if (text != NULL) {
        shareText = [NSString stringWithUTF8String:text];
    }
    
    [[UMSocialDataService defaultDataService]  postSNSWithTypes:@[getPlatformNSString(platform)] content:shareText image:image location:nil urlResource:urlResource presentedController:getCurrentViewController() completion:^(UMSocialResponseEntity *response){
     if (callback) {
     string message = string();
     if (response.message) {
     message = string([response.message UTF8String]);
     }
     callback(platform, (int)response.responseCode,message);
     }
     }];
    [urlResource release];
}

void setQQAppIdAndAppKey(const char *appId,const char *appKey){
    [UMSocialQQHandler setQQWithAppId:getNSStringFromCStr(appId) appKey:getNSStringFromCStr(appKey) url:@"http://www.umeng.com/social"];
}

void setWechatAppId(const char *appId){
    [UMSocialWechatHandler setWXAppId:getNSStringFromCStr(appId) url:@"http://www.umeng.com/social"];
}


void setLaiwangAppInfo(const char *appId, const char *appKey, const char *appName){
    [UMSocialLaiwangHandler setLaiwangAppId:getNSStringFromCStr(appId) appSecret:getNSStringFromCStr(appKey) appDescription:getNSStringFromCStr(appName) urlStirng:@"http://www.umeng.com/social"];
}


void setYiXinAppKey(const char *appKey){
    [UMSocialYixinHandler  setYixinAppKey:getNSStringFromCStr(appKey) url:@"http://www.umeng.com/social"];
}


void setFacebookAppId(const char *appId){
    [UMSocialFacebookHandler setFacebookAppID:getNSStringFromCStr(appId) shareFacebookWithURL:@"http://www.umeng.com/social"];
}


void openTwitter(){
    [UMSocialTwitterHandler openTwitter];
}

void openInstagram()
{
    [UMSocialInstagramHandler openInstagramWithScale:YES paddingColor:[UIColor blackColor]];
}