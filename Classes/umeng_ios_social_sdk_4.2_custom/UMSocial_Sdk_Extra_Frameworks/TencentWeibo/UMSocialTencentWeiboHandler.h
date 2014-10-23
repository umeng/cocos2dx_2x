//
//  UMSocialTencentWeiboHandler.h
//  SocialSDK
//
//  Created by yeahugo on 14-5-28.
//  Copyright (c) 2014年 Umeng. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UMSocialTencentWeiboHandler : NSObject

/**
 设置腾讯微博redirectUrl
 
 @param redirectUrl
 */
+(void)openSSOWithRedirectUrl:(NSString *)redirectUrl;

@end
