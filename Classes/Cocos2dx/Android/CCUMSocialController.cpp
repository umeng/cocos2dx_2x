/* DO NOT EDIT THIS FILE - it is machine generated */

//#include <android/log.h>
#include <Cocos2dx/Common/CCUMTypeDef.h>
#include <jni/JniHelper.h>
#include <jni.h>
#include <platform/CCCommon.h>
//#include <stdio.h>
//#include "cocos2d.h"
#include "CCUMSocialController.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// 授权回调
AuthEventHandler authCallback = NULL;
// 分享回调
ShareEventHandler shareCallback = NULL;

/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    OnAuthorizeStart
 * Function : 授权开始的回调函数, platform参数为要授权的平台
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnAuthorizeStart(
		JNIEnv *env, jclass clz, jint platform) {
	if ( NULL != authCallback) {
		map<string, string> nullData;
		authCallback(platform, 100, nullData);
	}

}

/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    OnAuthorizeComplete
 * Function : 授权结束的回调函数, platform为要授权的平台, stCode为返回码,其中200为授权成功, 0代表发生错误, -1代表取消.
 jobjectArray为授权成功时返回的数据,长度为2, 第一个数据为token, 第二个数据为过期时间。
 如果授权失败则返回的长度为1,包含了错误信息.
 而删除授权也是使用这个回调, 返回的字符串会为"deleteOauth", 开发者可以判断字符串来确定回调的结果.
 * Signature: ([Ljava/lang/String;I)V
 */
JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnAuthorizeComplete(
		JNIEnv *env, jclass clz, jint platform, jint stCode,
		jobjectArray data) {
	if (authCallback != NULL) {
		map<string, string> dataMap;
		// 获取数据
		getData(env, data, dataMap);
		authCallback(platform, stCode, dataMap);
	}

}

/*
 *
 *
 */
void getData(JNIEnv *env, jobjectArray data, map<string, string>& outputMap) {
	jsize count = env->GetArrayLength(data);

	if (count > 1) {
		// token
		jstring token = (jstring) env->GetObjectArrayElement(data, 0);
		// uid
		jstring uid = (jstring) env->GetObjectArrayElement(data, 1);
		const char* pToken = env->GetStringUTFChars(token, NULL);
		const char* pUid = env->GetStringUTFChars(uid, NULL);
		outputMap.insert(make_pair("token", pToken));
		outputMap.insert(make_pair("uid", pUid));
	} else if (count == 1) {
		// 错误消息
		jstring msg = (jstring) env->GetObjectArrayElement(data, 0);
		const char* pMsg = env->GetStringUTFChars(msg, NULL);
		outputMap.insert(make_pair("msg", pMsg));
	}
}

/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    OnShareStart
 * Function : 开始分享的回调函数
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnShareStart(
		JNIEnv *env, jclass clz) {
	if (shareCallback != NULL) {
		// 参数1代表平台, 参数2代表状态, 比如start, cancel, complete, 参数3代表状态码, 200为成功.
		shareCallback(-1, 100, "");

	}
}

/*
 * Class:     com_umeng_social_CCUMSocialController
 * Method:    OnShareComplete
 * Function : 分享完成的的回调函数, platform为分享的平台; stCode为返回码, 200为分享成功.
 * Signature: (IILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_umeng_social_CCUMSocialController_OnShareComplete(
		JNIEnv *env, jclass clz, jint platform, jint stCode,
		jstring descriptor) {
	if (shareCallback != NULL) {
		shareCallback(platform, stCode, "");
	}
}

/*
 * 设置友盟app key
 * @param appKey 友盟app key
 */
void setUmengAppkey(const char* appkey) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setUmengAppkey", "(Ljava/lang/String;)V");
	if (isHave) {
		jstring umkey = mi.env->NewStringUTF(appkey);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, umkey);
		mi.env->DeleteLocalRef(umkey);
		releaseMethod(mi);
	}

}

/*
 * 对某平台进行授权
 * @param platfrom 要授权的平台, 参考CCUMTypeDef.h中的Platform枚举定义
 * @param  callback 授权回调, 具体参考CCUMTypeDef.h中的定义
 */
void doAuthorize(int platform, AuthEventHandler callback) {
	authCallback = callback;
	if (authCallback != NULL) {
		CCLog("#### 授权回调不为NULL");

	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "doAuthorize", "(I)V");
	if (isHave) {
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform);
		releaseMethod(mi);
	}
}

/*
 * 删除某平台的授权信息
 * @param   callback 删除授权的回调, 具体参考CCUMTypeDef.h中的定义
 */
void deletePlatformAuthorization(int platform, AuthEventHandler callback) {
	authCallback = callback;
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "deleteAuthorization", "(I)V");
	if (isHave) {
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform);
		releaseMethod(mi);
	}
}

/*
 * 判断某平台是否已经授权
 * @param platform 要判定的平台, 参考CCUMTypeDef.h中的Platform枚举定义
 */
bool isPlatformAuthorized(int platform) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "isAuthorized", "(I)Z");
	jboolean isAuthorized = false;
	if (isHave) {
		isAuthorized = mi.env->CallStaticBooleanMethod(mi.classID, mi.methodID,
				platform);
		releaseMethod(mi);
	}
	return isAuthorized;
}

/*
 * 打开分享面板
 * @param callback 分享回调,具体参考CCUMTypeDef.h中的定义
 */
void doOpenShare(vector<int>* platforms,const char* text, const char* title,const char* imgName,const char* targeturl,ShareEventHandler callback) {
	shareCallback = callback;
	if (shareCallback != NULL) {
		CCLog("#### 分享回调不为NULL");

	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "openShare", "([ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	int* platformArr = platforms->data();
	int length = platforms->size();

	// 创建数组对象,且不能在函数末尾删除引用
	jintArray iArr = mi.env->NewIntArray(length);
	// 将nums数组中的内容设置到jintArray对象中,
	mi.env->SetIntArrayRegion(iArr, 0, length, platformArr);
	if (isHave) {
		jstring text_content = mi.env->NewStringUTF(text);
						jstring image = mi.env->NewStringUTF(imgName);
						jstring share_title = mi.env->NewStringUTF(title);
						jstring share_target_url = mi.env->NewStringUTF(targeturl);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID,iArr,text_content,share_title,share_target_url,image);
		releaseMethod(mi);
	}
}

/*
 * 直接分享到某个平台，不打开分享面板和内容编辑页面
 * @param platform 要分享到的目标平台， 参考CCUMTypeDef.h中的Platform枚举定义
 * @param callback 分享回调，具体参考CCUMTypeDef.h中的定义
 */
	void doDirectShare(const char* text,const char* title,const char* targeturl,
			const char* imgName,int platform, ShareEventHandler callback) {
	shareCallback = callback;
	if (shareCallback != NULL) {
		CCLog("#### 授权回调不为NULL");

	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "directShare", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave) {
		jstring text_content = mi.env->NewStringUTF(text);
				jstring image = mi.env->NewStringUTF(imgName);
				jstring share_title = mi.env->NewStringUTF(title);
				jstring share_target_url = mi.env->NewStringUTF(targeturl);
				mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform,
								text_content,share_title,share_target_url,image);
//		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform);
				mi.env->DeleteLocalRef(text_content);
				mi.env->DeleteLocalRef(image);
				mi.env->DeleteLocalRef(share_title);
				mi.env->DeleteLocalRef(share_target_url);
		releaseMethod(mi);
	}

}

/*
 * 设置要分享的文字内容
 * @param text 要分享的文字内容
 */
void setShareTextContent(const char* text) {
	if (text == NULL) {
		CCLog("#### share text is null.");
		return;
	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setShareContent", "(Ljava/lang/String;)V");
	if (isHave) {
		jstring content = mi.env->NewStringUTF(text);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, content);
		mi.env->DeleteLocalRef(content);
		releaseMethod(mi);
	}
	CCLog("#### setShareTextContent");
}

/*
 * 设置要分享的图片的本地路径或者url
 * @param path 图片的本地路径或者url, 如果是url必须则必须以http://或者https://开头
 */
void setShareImagePath(const char* path) {
	if (path == NULL) {
		CCLog("#### image path is null.");
		return;
	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setShareImagePath", "(Ljava/lang/String;)V");
	if (isHave) {
		jstring imgPath = mi.env->NewStringUTF(path);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, imgPath);
		mi.env->DeleteLocalRef(imgPath);
		releaseMethod(mi);
	}
	CCLog("#### setShareImageName");
}

/*
 * 设置SDK支持的平台
 * @param platforms SDK支持的平台， 参考CCUMTypeDef.h中的Platform枚举定义
 */
void setSocialPlatforms(vector<int>* platforms) {
	if (platforms == NULL) {
		return;
	}
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setPlatforms", "([I)V");

	int* platformArr = platforms->data();
	int length = platforms->size();

	// 创建数组对象,且不能在函数末尾删除引用
	jintArray iArr = mi.env->NewIntArray(length);
	// 将nums数组中的内容设置到jintArray对象中,
	mi.env->SetIntArrayRegion(iArr, 0, length, platformArr);
	if (isHave) {
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, iArr);
		releaseMethod(mi);
	}
}

///*
// * 添加平台支持
// * @param platform 要添加的目标平台
// */
//void supportPlatform(int platform) {
//	JniMethodInfo mi;
//	bool isHave = getMethod(mi, "supportPlatfrom", "(I)V");
//	if (isHave) {
//		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform);
//		releaseMethod(mi);
//	}
//}

/*
 * 初始化Cocos2d-x sdk
 */
void initCocos2dxSDKFromJni(const char* type, const char* version) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "initCocos2dxSDKInfo",
			"(Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave) {
		jstring wpType = mi.env->NewStringUTF(type);
		jstring sdkVersion = mi.env->NewStringUTF(version);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, wpType,
				sdkVersion);
		mi.env->DeleteLocalRef(wpType);
		mi.env->DeleteLocalRef(sdkVersion);
		releaseMethod(mi);
	}
	CCLog("#### setQQConnectPlatformAppId");
}

/**
 * 设置QQ的app id
 * 
 * @param appid
 */
void setQQAndQzoneAppIdWithAppKey(const char* appid, const char* appKey) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setQQAndQzoneAppIdWithAppKey",
			"(Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave) {
		jstring jAppid = mi.env->NewStringUTF(appid);
		jstring jAppKey = mi.env->NewStringUTF(appKey);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, jAppid, jAppKey);
		mi.env->DeleteLocalRef(jAppid);
		mi.env->DeleteLocalRef(jAppKey);
		releaseMethod(mi);
	}
	CCLog("#### setQQAndQzoneAppIdAndAppKey");
}

/**
 * 设置微信和微信朋友圈的app id
 * 
 * @param appid
 */
void setWeiXinPlatformInfo(const char* appid, const char* appsecret) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setWeiXinAppInfo",
			"(Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave) {
		jstring jAppid = mi.env->NewStringUTF(appid);
		jstring jAppSecret = mi.env->NewStringUTF(appsecret);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, jAppid,
				jAppSecret);
		mi.env->DeleteLocalRef(jAppid);
		mi.env->DeleteLocalRef(jAppSecret);
		releaseMethod(mi);
	}
	CCLog("#### setWeiXinPlatformAppid");
}

/**
 * 设置人人网的app id,app key,app secret信息
 *
 * @param appid 人人网的appid
 * @param appKey 人人网的app key
 * @param appsecret 人人网的appsecret
 */
void setRenrenSsoAppInfo(const char* appid, const char* appkey,
		const char* appsecret) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setRenrenAppInfo",
			"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave) {
		jstring jAppid = mi.env->NewStringUTF(appid);
		jstring jAppkey = mi.env->NewStringUTF(appkey);
		jstring jAppSecret = mi.env->NewStringUTF(appsecret);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, jAppid, jAppkey,
				jAppSecret);
		mi.env->DeleteLocalRef(jAppid);
		mi.env->DeleteLocalRef(jAppkey);
		mi.env->DeleteLocalRef(jAppSecret);
		releaseMethod(mi);
	}

}

/**
 * 设置易信和易信朋友圈的app id
 *
 * @param appid
 */
void setYiXinPlatformAppKey(const char* appid) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setYiXinAppKey", "(Ljava/lang/String;)V");
	if (isHave) {
		jstring jAppKey = mi.env->NewStringUTF(appid);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, jAppKey);
		mi.env->DeleteLocalRef(jAppKey);
		releaseMethod(mi);
	}
	CCLog("#### setYiXinPlatformAppKey");

}

/**
 * 设置来往和来往动态的app id
 * 
 * @param appid
 */
void setLaiwangPlatformAppId(const char* appid) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setLaiwangAppId", "(Ljava/lang/String;)V");
	if (isHave) {
		jstring jAppid = mi.env->NewStringUTF(appid);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, jAppid);
		mi.env->DeleteLocalRef(jAppid);
		releaseMethod(mi);
	}
	CCLog("#### setLaiwangPlatformAppid");
}

/**
 * 设置来往和来往动态的app key
 *
 * @param appKey
 */
void setLaiwangPlatformAppKey(const char* appkey) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setLaiwangAppKey", "(Ljava/lang/String;)V");
	if (isHave) {
		jstring jAppKey = mi.env->NewStringUTF(appkey);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, jAppKey);
		mi.env->DeleteLocalRef(jAppKey);
		releaseMethod(mi);
	}
	CCLog("#### setLaiwangPlatformAppKey   jni");
}

/**
 * 设置来往和来往动态的app key
 *
 * @param appName
 */
void setLaiwangPlatformAppName(const char* appName) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setLaiwangAppName", "(Ljava/lang/String;)V");
	if (isHave) {
		jstring jAppName = mi.env->NewStringUTF(appName);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, jAppName);
		mi.env->DeleteLocalRef(jAppName);
		releaseMethod(mi);
	}
	CCLog("#### setLaiwangPlatformAppName jni ");
}

/**
 * 设置facebook app id
 *
 * @param appId
 */
void setFacebookPlatformAppId(const char* appid) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setFacebookAppId", "(Ljava/lang/String;)V");
	if (isHave) {
		jstring jAppId = mi.env->NewStringUTF(appid);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, jAppId);
		mi.env->DeleteLocalRef(jAppId);
		releaseMethod(mi);
	}
	CCLog("#### setFacebookPlatformAppId  jni ");

}

/*
 * 设置SDK的target url
 * @param url 用户点击某条分享时跳转到的目标页面通常为app的主页或者下载链接等
 */
void setShareTargetUrl(const char* url) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setTargetUrl", "(Ljava/lang/String;)V");
	if (isHave) {
		jstring targetUrl = mi.env->NewStringUTF(url);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, targetUrl);
		mi.env->DeleteLocalRef(targetUrl);
		releaseMethod(mi);
	}
	CCLog("#### setShareTargetUrl");
}

/**
 * 设置平台的sso授权，目前支持的平台有新浪微博、人人网、腾讯微博三个平台.
 * @param  platform 要支持SSO授权的平台
 * @param  redirectURL SSO授权回调地址
 */
void supportSsoAuthorization(int platform, const char* redirectURL) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "supportSsoAuthorization",
			"(ILjava/lang/String;)V");
	if (isHave) {
		jstring callbackUrl = mi.env->NewStringUTF(redirectURL);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform,
				callbackUrl);
		mi.env->DeleteLocalRef(callbackUrl);
		releaseMethod(mi);
	}
	CCLog("#### supportSsoAuthorization");
}

/**
 *
 */
void setPlatformDepShareContent(int platform, const char* text,
		const char* imagePath, const char* title, const char* targetUrl) {
	JniMethodInfo mi;
	bool isHave =
			getMethod(mi, "setPlatformShareContent",
					"(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave) {
		jstring text_content = mi.env->NewStringUTF(text);
		jstring image = mi.env->NewStringUTF(imagePath);
		jstring share_title = mi.env->NewStringUTF(title);
		jstring share_target_url = mi.env->NewStringUTF(targetUrl);
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, platform,
				text_content, image, share_title, share_target_url);
		mi.env->DeleteLocalRef(text_content);
		mi.env->DeleteLocalRef(image);
		mi.env->DeleteLocalRef(share_title);
		mi.env->DeleteLocalRef(share_target_url);
		releaseMethod(mi);
	}
	CCLog("#### setPlatformDepShareContent");

}
/**
 *  是否开启log
 * @param flag 如果为true则开启log, 否则关闭.
 */
void setAndroidLogEnable(bool flag) {
	JniMethodInfo mi;
	bool isHave = getMethod(mi, "setAndroidLogEnable", "(Z)V");
	if (isHave) {
		mi.env->CallStaticVoidMethod(mi.classID, mi.methodID, flag);
		releaseMethod(mi);
	}
	CCLog("#### setAndroidLogEnable");

}

/*
 * 获取某个方法的对象
 * @param mi 方法对象， 传递的是引用
 * @param methodName 方法名
 * @param sig       方法签名
 */
bool getMethod(JniMethodInfo &mi, const char *methodName,
		const char *signature) {
	return JniHelper::getStaticMethodInfo(mi,
			"com/umeng/social/CCUMSocialController", methodName, signature);
}

/*
 * 释放方法对象
 * @param mi 要释放的方法对象
 */
void releaseMethod(JniMethodInfo &mi) {
	mi.env->DeleteLocalRef(mi.classID);
}

