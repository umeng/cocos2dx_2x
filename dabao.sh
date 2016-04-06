#!/bin/bash
social_cocos_version="5.0"

echo "copy readme.md !"
cp readme.md release
echo "copy cocos2dx !"
cp  -rf Classes/Cocos2dx release/
echo "copy controller"
cp -rf proj.android/src/com/umeng/social release/Platforms/Android/controller/com/umeng/ 
echo "copy main"
cp -rf  androidlib/main release/Platforms/Android/core 
echo "copy sns platform"
cp -rf  androidlib/platforms/email release/Platforms/Android/sns_platforms/
cp -rf  androidlib/platforms/facebook  release/Platforms/Android/sns_platforms/
cp -rf  androidlib/platforms/instagram   release/Platforms/Android/sns_platforms/
cp -rf  androidlib/platforms/qq_qzone   release/Platforms/Android/sns_platforms/ 
cp -rf  androidlib/platforms/renren    release/Platforms/Android/sns_platforms/
cp -rf  androidlib/platforms/sina     release/Platforms/Android/sns_platforms/
cp -rf  androidlib/platforms/sms  release/Platforms/Android/sns_platforms/
cp -rf  androidlib/platforms/tencentweibo  release/Platforms/Android/sns_platforms/ 
cp -rf  androidlib/platforms/weixin   release/Platforms/Android/sns_platforms/
cp -rf  androidlib/platforms/yixin    release/Platforms/Android/sns_platforms/

echo "remove old iOS library"
rm -rf release/Platforms/iOS

echo "copy iOS library"
cp -rf Classes/umeng_ios_social_sdk		release/Platforms/
mv release/Platforms/umeng_ios_social_sdk 	release/platforms/iOS

echo "packaging..."
cp -rf release UMengSocialCocos2dx_${social_cocos_version}
zip -r UMengSocialCocos2dx_${social_cocos_version}.zip UMengSocialCocos2dx_${social_cocos_version}
rm -rf UMengSocialCocos2dx_${social_cocos_version}

echo "packging social cocos2dx-"$social_cocos_version" finish."