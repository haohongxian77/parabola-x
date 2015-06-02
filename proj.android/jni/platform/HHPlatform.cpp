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
static jclass m_ADClient;
static jclass m_Toast;

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

	  jclass cls_AD = env->FindClass("com/game/gws/jump/google/AdsClient");
	  m_ADClient = (jclass) env->NewGlobalRef(cls_AD);

	  jclass cls_Toast = env->FindClass("com/game/gws/jump/share/ToastUtils");
	  m_Toast = (jclass) env->NewGlobalRef(cls_Toast);

	  env->DeleteLocalRef(cls_AD);

}
void HHPlatform::share(int shareType,int shareFrom,std::string filepath){
	   JNIEnv *env;
		m_pVM->AttachCurrentThread(&env, NULL);
		jmethodID construction_id;
		jmethodID m_shareImage;
		jobject obj;
//		jmethodID shareClient;

		//jint shareFrom = env->NewStringUTF(absPath.c_str());
		jstring jstrImagePath = env->NewStringUTF(filepath.c_str());
       switch(shareType){
       case Share_SINA:
    	   construction_id = env->GetStaticMethodID(m_shareSina, "getInstance", "()Lcom/game/gws/jump/share/SinaClient;");
    	   obj = env->CallStaticObjectMethod(m_shareSina, construction_id);
//    	   obj =getInstanceObj(env,m_shareSina);

    	   m_shareImage = env->GetMethodID(m_shareSina,
    	   			         "shareImgAndContent",
    	   			            "(ILjava/lang/String;)V");
    	   env->CallVoidMethod(obj, m_shareImage,shareFrom,jstrImagePath);
    	   break;
       case Share_QQ:
    	   construction_id = env->GetStaticMethodID(m_shareQQ, "getInstance", "()Lcom/game/gws/jump/share/TencentClient;");
    	   obj = env->CallStaticObjectMethod(m_shareQQ, construction_id);
//    	   obj =getInstanceObj(env,m_shareQQ);
    	   m_shareImage = env->GetMethodID(m_shareQQ,
    	      	   			         "shareImg",
    	      	   			            "(ILjava/lang/String;)V");
    	   env->CallVoidMethod(obj, m_shareImage,shareFrom,jstrImagePath);
    	   break;
       case Share_WX:
    	   construction_id = env->GetStaticMethodID(m_shareWX, "getInstance", "()Lcom/game/gws/jump/share/WxClient;");
    	   obj = env->CallStaticObjectMethod(m_shareWX, construction_id);
//    	   obj =getInstanceObj(env,m_shareWX);
    	   m_shareImage = env->GetMethodID(m_shareWX,
    	      	   			         "shareImg",
    	      	   			            "(ILjava/lang/String;)V");
    	   env->CallVoidMethod(obj, m_shareImage,shareFrom,jstrImagePath);
    	   break;
       case Share_FB:
    	   construction_id = env->GetStaticMethodID(m_shareFB, "getInstance", "()Lcom/game/gws/jump/share/FaceBookClient;");
    	   obj = env->CallStaticObjectMethod(m_shareFB, construction_id);
//    	   obj =getInstanceObj(env,m_shareFB);
    	   m_shareImage = env->GetMethodID(m_shareFB,
    	      	   			         "shareImg",
    	      	   			            "(ILjava/lang/String;)V");
    	   env->CallVoidMethod(obj, m_shareImage,shareFrom,jstrImagePath);
    	   break;

       }


		env->DeleteLocalRef(jstrImagePath);
//		env->DeleteLocalRef(jstrContent);

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
void HHPlatform::showFullAD(){
	JNIEnv *env;
	m_pVM->AttachCurrentThread(&env, NULL);
	jmethodID construction_id = env->GetStaticMethodID(m_ADClient, "getInstance", "()Lcom/game/gws/jump/google/AdsClient;");
	jobject   	   obj = env->CallStaticObjectMethod(m_ADClient, construction_id);
	jmethodID adShow = env->GetMethodID(m_ADClient,
				    	      	   			         "showInsertAd",
				    	      	   			            "()V");
	env->CallVoidMethod(obj, adShow);

}
void HHPlatform::commitScore(int score){
	JNIEnv *env;
	m_pVM->AttachCurrentThread(&env, NULL);
	jmethodID construction_id = env->GetStaticMethodID(m_googleClient, "getInstance", "()Lcom/game/gws/jump/google/GwsGooglePlayServiceClient;");
	jobject   	   obj = env->CallStaticObjectMethod(m_googleClient, construction_id);
	//		jobject obj =getInstanceObj(env,m_googleClient);
	jmethodID googleCommitScore = env->GetMethodID(m_googleClient,
			    	      	   			         "commitScore",
			    	      	   			            "(I)V");
	env->CallVoidMethod(obj, googleCommitScore,score);
}
void HHPlatform::showToast(std::string content){
	JNIEnv *env;
	m_pVM->AttachCurrentThread(&env, NULL);
	jstring jstrContent = env->NewStringUTF(content.c_str());
	jmethodID toastShow_id = env->GetStaticMethodID(m_Toast, "ToastLong", "(Ljava/lang/String;)V");
	env->CallStaticVoidMethod(m_Toast, toastShow_id,jstrContent);
		env->DeleteLocalRef(jstrContent);
}







