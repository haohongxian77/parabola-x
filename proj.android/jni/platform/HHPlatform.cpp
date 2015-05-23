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
static jclass m_googleClient;

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

	  jclass cls_FB = env->FindClass("com/game/gws/jump/share/FaceBookClient");
	  m_shareFB = (jclass) env->NewGlobalRef(cls_FB);
	  env->DeleteLocalRef(cls_FB);

	  jclass cls_google = env->FindClass("com/game/gws/jump/google/GwsGooglePlayServiceClient");
	  	  m_googleClient = (jclass) env->NewGlobalRef(cls_google);
	  	  env->DeleteLocalRef(cls_google);

}
void HHPlatform::share(int shareType,std::string absPath){
	   JNIEnv *env;
		m_pVM->AttachCurrentThread(&env, NULL);
		jmethodID construction_id;
		jmethodID m_shareImage;
		jobject obj;
//		jmethodID shareClient;

		jstring jstrImagePath = env->NewStringUTF(absPath.c_str());
		jstring jstrContent = env->NewStringUTF("content");
		CCLOG("----------------------------%d",shareType);
       switch(shareType){
       case Share_SINA:
    	   construction_id = env->GetStaticMethodID(m_shareSina, "getInstance", "()Lcom/game/gws/jump/share/SinaClient;");
    	   obj = env->CallStaticObjectMethod(m_shareSina, construction_id);
//    	   obj =getInstanceObj(env,m_shareSina);
    	   m_shareImage = env->GetMethodID(m_shareSina,
    	   			         "callShare",
    	   			            "(Ljava/lang/String;Ljava/lang/String;)V");
    	   env->CallVoidMethod(obj, m_shareImage,jstrImagePath,jstrContent);
    	   break;
       case Share_QQ:
    	   construction_id = env->GetStaticMethodID(m_shareQQ, "getInstance", "()Lcom/game/gws/jump/share/TencentClient;");
    	   obj = env->CallStaticObjectMethod(m_shareQQ, construction_id);
//    	   obj =getInstanceObj(env,m_shareQQ);
    	   m_shareImage = env->GetMethodID(m_shareQQ,
    	      	   			         "shareImg",
    	      	   			            "(Ljava/lang/String;)V");
    	   env->CallVoidMethod(obj, m_shareImage,jstrImagePath);
    	   break;
       case Share_WX:
    	   construction_id = env->GetStaticMethodID(m_shareWX, "getInstance", "()Lcom/game/gws/jump/share/WxClient;");
    	   obj = env->CallStaticObjectMethod(m_shareWX, construction_id);
//    	   obj =getInstanceObj(env,m_shareWX);
    	   m_shareImage = env->GetMethodID(m_shareWX,
    	      	   			         "shareImg",
    	      	   			            "(Ljava/lang/String;Ljava/lang/String;)V");
    	   env->CallVoidMethod(obj, m_shareImage,jstrImagePath,jstrContent);
    	   break;
       case Share_FB:
    	   construction_id = env->GetStaticMethodID(m_shareFB, "getInstance", "()Lcom/game/gws/jump/share/FaceBookClient;");
    	   obj = env->CallStaticObjectMethod(m_shareFB, construction_id);
//    	   obj =getInstanceObj(env,m_shareFB);
    	   m_shareImage = env->GetMethodID(m_shareFB,
    	      	   			         "shareImg",
    	      	   			            "(Ljava/lang/String;)V");
    	   env->CallVoidMethod(obj, m_shareImage,jstrImagePath);
    	   break;

       }


		env->DeleteLocalRef(jstrImagePath);
		env->DeleteLocalRef(jstrContent);

}
void HHPlatform::showRank(){
	   JNIEnv *env;
		m_pVM->AttachCurrentThread(&env, NULL);
		jmethodID construction_id = env->GetStaticMethodID(m_googleClient, "getInstance", "()Lcom/game/gws/jump/google/GwsGooglePlayServiceClient;");
		jobject   	   obj = env->CallStaticObjectMethod(m_googleClient, construction_id);
//		jobject obj =getInstanceObj(env,m_googleClient);
		jmethodID googleRank = env->GetMethodID(m_googleClient,
		    	      	   			         "showLeaderBoards",
		    	      	   			            "()V");
	   env->CallVoidMethod(obj, googleRank);


}
