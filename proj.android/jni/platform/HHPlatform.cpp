/* 
 * File:   HHPlatform.cpp
 * Author: zhaocong
 * 
 * Created on March 31, 2014, 4:37 PM
 */

#include "HHPlatform.h"
#include "platform/android/jni/JniHelper.h"




JNIEXPORT void JNICALL Java_com_nextmv_hero_googlekr_HHPayClientActivity_OnPurchaseNotify
(JNIEnv *env, jclass jc,jint jerrorCode ,jobject  jPurchaseInfo,jstring jErrorInfos){

}

static jclass m_shareQQ;
static jclass m_shareWX;
static jclass m_shareSina;
static jclass m_shareFB;

HHPlatform* HHPlatform::m_pInst;


HHPlatform* HHPlatform::GetInstance() {
	if (m_pInst == NULL) {
		CCLog("HHPlatform::GetInstance");
		m_pInst = new HHPlatform();
		m_pInst->retain();
	}
	return m_pInst;
}

void HHPlatform::setVM(){
	    m_pVM = JniHelper::getJavaVM();
	    JNIEnv *env;
	    m_pVM->AttachCurrentThread(&env, NULL);

	    jclass cls_Sina = env->FindClass("com/game/gws/jump/share/SinaClient");
	    m_shareSina = (jclass) env->NewGlobalRef(cls_Sina);
	    env->DeleteLocalRef(cls_Sina);

	    jclass cls_QQ = env->FindClass("com/game/gws/jump/share/TencentClient");
	    m_shareQQ = (jclass) env->NewGlobalRef(cls_QQ);
	    env->DeleteLocalRef(cls_QQ);

	   jclass cls_WX = env->FindClass("com/game/gws/jump/share/WxClient");
	   m_shareWX = (jclass) env->NewGlobalRef(cls_WX);
	   env->DeleteLocalRef(cls_WX);

	  jclass cls_FB = env->FindClass("com/game/gws/jump/share/SinaClient");
	  m_shareFB = (jclass) env->NewGlobalRef(cls_FB);
	  env->DeleteLocalRef(cls_FB);

}
void HHPlatform::share(int shareType,std::string absPath){
	   JNIEnv *env;
		m_pVM->AttachCurrentThread(&env, NULL);
		jmethodID m_shareImage;
		jstring jstrImagePath = env->NewStringUTF(absPath.c_str());
		jstring jstrContent = env->NewStringUTF("content");
		CCLOG("----------------------------%d",shareType);
       switch(shareType){
       case Share_SINA:
    	   CCLOG("share    Share_SINA---------------------1");
    	   m_shareImage = env->GetMethodID(m_shareSina,
    	   			         "callShare",
    	   			            "(Ljava/lang/String;Ljava/lang/String;)V");
    	   CCLOG("share    Share_SINA---------------------2");
    	   env->CallVoidMethod(m_shareSina, m_shareImage,jstrImagePath,jstrContent);
    	   CCLOG("share    Share_SINA---------------------3");
    	   break;
       case Share_QQ:
    	   m_shareImage = env->GetStaticMethodID(m_shareQQ,
    	      	   			         "shareImg",
    	      	   			            "(Ljava/lang/String;)V");
    	   env->CallStaticVoidMethod(m_shareQQ, m_shareImage,jstrImagePath);
    	   break;
       case Share_WX:
    	   m_shareImage = env->GetStaticMethodID(m_shareWX,
    	      	   			         "shareImg",
    	      	   			            "(Ljava/lang/String;Ljava/lang/String;)V");
    	   env->CallStaticVoidMethod(m_shareWX, m_shareImage,jstrImagePath,jstrContent);
    	   break;
       case Share_FB:
    	   m_shareImage = env->GetStaticMethodID(m_shareSina,
    	      	   			         "shareImgAndContent",
    	      	   			            "(Ljava/lang/String;Ljava/lang/String;)V");
    	   env->CallStaticVoidMethod(m_shareSina, m_shareImage,jstrImagePath,jstrContent);
    	   break;

       }


		env->DeleteLocalRef(jstrImagePath);
		env->DeleteLocalRef(jstrContent);

}
