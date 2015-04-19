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
	 CCLog("JNICALL Java_com_game_korea_activity_HHPayClientActivity_OnPurchaseNotify");
			int errorCode = (int)jerrorCode;
			 const char* errorInfo = new char[100];

			PurchaseInfo purchaseInfo;
			CCLog("JNICALL Java_com_game_korea_activity_HHPayClientActivity_OnPurchaseNotify=====111%s",errorCode);
			if(errorCode  == 0){

				jclass jPurchaseRetClass = env->GetObjectClass(jPurchaseInfo);
				CCLog("JNICALL Java_com_game_korea_activity_HHPayClientActivity_OnPurchaseNotify=====222");
				JniGetAndSetStringField(api_version, "api_version", jPurchaseRetClass, jPurchaseInfo, purchaseInfo);
				JniGetAndSetStringField(identifier,"identifier", jPurchaseRetClass, jPurchaseInfo, purchaseInfo);
				JniGetAndSetStringField(code,"code", jPurchaseRetClass, jPurchaseInfo, purchaseInfo);
				JniGetAndSetStringField(tid, "tid", jPurchaseRetClass, jPurchaseInfo, purchaseInfo);
				JniGetAndSetStringField(receipt,"receipt", jPurchaseRetClass, jPurchaseInfo, purchaseInfo);
				JniGetAndSetStringField(productInfos,"productInfos", jPurchaseRetClass, jPurchaseInfo, purchaseInfo);
			}else{
				CCLog("JNICALL Java_com_game_korea_activity_HHPayClientActivity_OnPurchaseNotify=====333");
				errorInfo = env->GetStringUTFChars(jErrorInfos, NULL);
			}

			CCLog("JNICALL Java_com_game_korea_activity_HHPayClientActivity_OnPurchaseNotify=====222");

			HHPlatform::GetInstance()->notifyPayObserver(errorCode,errorInfo,purchaseInfo);
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
void HHPlatform::registerDelegate(HHIAPServiceDelegate* delegate){
	CCLog("HHPlatform::registerDelegate %s",delegate);
	__delegate_list.insert(delegate);
}
void HHPlatform::unRegisterDelegate(HHIAPServiceDelegate* delegate){
	CCLog("unRegisterDelegate    ===============");
	__delegate_list.erase(delegate);
}
 std::set<HHIAPServiceDelegate*> HHPlatform::getDelegateSet(){
	return  __delegate_list;
}
void HHPlatform::notifyLoginObserver(UserInfo  loginUser){
	m_LoginUser = loginUser;
    std::set<HHIAPServiceDelegate *> __set;
	for (set<HHIAPServiceDelegate*>::iterator it = __delegate_list.begin();
		 it != __delegate_list.end(); it++) {
		__set.insert(*it);
	}

	for (set<HHIAPServiceDelegate*>::iterator it = __set.begin();
		 it != __set.end(); it++) {

		CCLOG("[BAGAZIINCPULS] notifyLoginObserver set   notifyLoginObserver  ++++ ");
		(*it)->OnHHLoginNotify();
	}
	//m_delegate->OnHHLoginNotify(loginUser);
}

void HHPlatform::notifyPayObserver(int errorCode,std::string errorInfos,PurchaseInfo purInfo){
	    set<HHIAPServiceDelegate *> __set;
		for (set<HHIAPServiceDelegate*>::iterator it = __delegate_list.begin();
			 it != __delegate_list.end(); it++) {
			__set.insert(*it);
		}

		for (set<HHIAPServiceDelegate*>::iterator it = __set.begin();
			 it != __set.end(); it++) {

			CCLOG("[BAGAZIINCPULS] notifyLoginObserver set   notifyLoginObserver  ++++ ");
			(*it)->OnHHPurchaseNotify(errorCode,errorInfos,purInfo);
		}
	//m_delegate->OnHHPurchaseNotify();

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
