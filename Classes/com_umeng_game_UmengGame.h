/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include <string.h>
/* Header for class com_umeng_game_UmengGame */

#ifndef _Included_com_umeng_game_UmengGame
#define _Included_com_umeng_game_UmengGame
#ifdef __cplusplus
extern "C" {
#endif
#undef com_umeng_game_UmengGame_DELAY
#define com_umeng_game_UmengGame_DELAY 100L
/*
 * Class:     com_umeng_game_UmengGame
 * Method:    onNativeStart
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_umeng_game_UmengGame_onNativeStart
  (JNIEnv *, jclass);

/*
 * Class:     com_umeng_game_UmengGame
 * Method:    onNativeComplete
 * Signature: (Ljava/lang/String;ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_umeng_game_UmengGame_onNativeComplete
  (JNIEnv *, jclass, jstring, jint, jstring);

/*
 * Class:     com_umeng_game_UmengGame
 * Method:    getCocos2dxScrShot
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_umeng_game_UmengGame_getCocos2dxScrShot
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
