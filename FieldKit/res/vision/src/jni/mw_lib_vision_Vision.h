/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class mw_lib_vision_Vision */

#ifndef _Included_mw_lib_vision_Vision
#define _Included_mw_lib_vision_Vision
#ifdef __cplusplus
extern "C" {
#endif
#undef mw_lib_vision_Vision_BLOB_COUNT
#define mw_lib_vision_Vision_BLOB_COUNT 10L
#undef mw_lib_vision_Vision_STAGE_COUNT
#define mw_lib_vision_Vision_STAGE_COUNT 10L
#undef mw_lib_vision_Vision_DATA_LIST_START
#define mw_lib_vision_Vision_DATA_LIST_START -2000L
#undef mw_lib_vision_Vision_DATA_LIST_END
#define mw_lib_vision_Vision_DATA_LIST_END -2001L
#undef mw_lib_vision_Vision_DATA_LIST_ITEM_START
#define mw_lib_vision_Vision_DATA_LIST_ITEM_START -3000L
#undef mw_lib_vision_Vision_DATA_LIST_ITEM_END
#define mw_lib_vision_Vision_DATA_LIST_ITEM_END -3001L
/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniCreate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_mw_lib_vision_Vision_jniCreate
  (JNIEnv *, jobject);

/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniUpdate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_mw_lib_vision_Vision_jniUpdate
  (JNIEnv *, jobject);

/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniDestroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_mw_lib_vision_Vision_jniDestroy
  (JNIEnv *, jobject);

/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniSetSize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_mw_lib_vision_Vision_jniSetSize
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniSetROI
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_mw_lib_vision_Vision_jniSetROI
  (JNIEnv *, jobject, jint, jint, jint, jint);

/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniSetSlider
 * Signature: (IF)V
 */
JNIEXPORT void JNICALL Java_mw_lib_vision_Vision_jniSetSlider
  (JNIEnv *, jobject, jint, jfloat);

/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniSetWarp
 * Signature: (IIIIIIII)V
 */
JNIEXPORT void JNICALL Java_mw_lib_vision_Vision_jniSetWarp
  (JNIEnv *, jobject, jint, jint, jint, jint, jint, jint, jint, jint);

/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniGetWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_mw_lib_vision_Vision_jniGetWidth
  (JNIEnv *, jobject);

/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniGetHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_mw_lib_vision_Vision_jniGetHeight
  (JNIEnv *, jobject);

/*
 * Class:     mw_lib_vision_Vision
 * Method:    jniGetBlobData
 * Signature: ()Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_mw_lib_vision_Vision_jniGetBlobData
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
/* Header for class mw_lib_vision_Vision_ProcStage */

#ifndef _Included_mw_lib_vision_Vision_ProcStage
#define _Included_mw_lib_vision_Vision_ProcStage
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
#endif
/* Header for class mw_lib_vision_Vision_ProcSlider */

#ifndef _Included_mw_lib_vision_Vision_ProcSlider
#define _Included_mw_lib_vision_Vision_ProcSlider
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
#endif
/* Header for class mw_lib_vision_Stage */

#ifndef _Included_mw_lib_vision_Stage
#define _Included_mw_lib_vision_Stage
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     mw_lib_vision_Stage
 * Method:    jniSetEnabled
 * Signature: (ZI)V
 */
JNIEXPORT void JNICALL Java_mw_lib_vision_Stage_jniSetEnabled
  (JNIEnv *, jobject, jboolean, jint);

/*
 * Class:     mw_lib_vision_Stage
 * Method:    jniGetImageBuffer
 * Signature: (I)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_mw_lib_vision_Stage_jniGetImageBuffer
  (JNIEnv *, jobject, jint);

/*
 * Class:     mw_lib_vision_Stage
 * Method:    jniGetWidth
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_mw_lib_vision_Stage_jniGetWidth
  (JNIEnv *, jobject, jint);

/*
 * Class:     mw_lib_vision_Stage
 * Method:    jniGetHeight
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_mw_lib_vision_Stage_jniGetHeight
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif