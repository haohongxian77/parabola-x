/*
 * Copyright 2014 Garena Online Pvt Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __beetalk_msdk__HHPlatform__
#define __beetalk_msdk__HHPlatform__
#include <jni.h>
#include <string.h>
#include <set>
#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_com_game_korea_tstore_HHPayClientActivity_OnPurchaseNotify(JNIEnv *, jclass,jstring ,jobject,jstring);
#ifdef __cplusplus
}
#endif
#include "cocos2d.h"

using namespace cocos2d;
using  std::set;
class HHIAPServiceDelegate {
public:
	HHIAPServiceDelegate() {}

    ~HHIAPServiceDelegate() {}

//	virtual void OnHHPurchaseNotify(int errorCode,std::string errorInfos,PurchaseInfo purInfo){};
//	virtual void OnHHLoginNotify(){};
//	virtual void OnHHInitGoogle(){};       //��ʼ���ȸ����
//	virtual void OnHHPurchaseFinish(){};     //�������
};

class HHPlatform :public CCObject ,public HHIAPServiceDelegate
{
public:
	HHPlatform(){
		setVM();
		registerDelegate(this);
	};
	~HHPlatform(){
       unRegisterDelegate(this);
		};
	static HHPlatform* m_pInst;

	JavaVM* m_pVM;
private :
	std::set<HHIAPServiceDelegate*> __delegate_list;
public :
	static HHPlatform* GetInstance();
	void setVM();
	void registerDelegate(HHIAPServiceDelegate* delegate);
	void unRegisterDelegate(HHIAPServiceDelegate* delegate);
    set<HHIAPServiceDelegate*> getDelegateSet();

	void notifyPayObserver(int errorCode,std::string errorInfos,PurchaseInfo purInfo);
	void notifyLoginObserver(UserInfo  loginUser);

	void share(std::string absPath);
};

#endif /* defined(__beetalk_msdk__HHPlatform__) */
