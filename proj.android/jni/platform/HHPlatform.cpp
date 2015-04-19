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

static jclass m_shareSina;
HHPlatform* HHPlatform::m_pInst;


HHPlatform* HHPlatform::GetInstance() {
	if (m_pInst == NULL) {
		CCLog("HHPlatform::GetInstance");
		m_pInst = new HHPlatform();
	}
	return m_pInst;
}

void HHPlatform::setVM(){
	    m_pVM = JniHelper::getJavaVM();
	    JNIEnv *env;
	    m_pVM->AttachCurrentThread(&env, NULL);

	    jclass cls_All = env->FindClass("com/game/gws/jump/share/SinaClient");
	    m_shareSina = (jclass) env->NewGlobalRef(cls_All);
	    env->DeleteLocalRef(cls_All);

}
void HHPlatform::share(std::string absPath){
	   JNIEnv *env;
		m_pVM->AttachCurrentThread(&env, NULL);

		jmethodID m_shareImage = env->GetStaticMethodID(m_shareSina,
			         "shareImgAndContent",
			            "(Ljava/lang/String;Ljava/lang/String)V");
		jstring jstrImagePath = env->NewStringUTF(absPath.c_str());
		jstring jstrContent = env->NewStringUTF("content");
		env->CallStaticVoidMethod(m_shareSina, m_shareImage,jstrImagePath,jstrContent);
		env->DeleteLocalRef(jstrImagePath);
		env->DeleteLocalRef(jstrContent);

}
