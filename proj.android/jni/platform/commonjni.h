/* 
 * File:   GGCommon.h
 * Author: zhaocong
 *
 * Created on March 31, 2014, 4:39 PM
 */

#ifndef GGCOMMON_H
#define GGCOMMON_H


#include <string>
#include <vector>

typedef struct
{
    int type; //1 login token 2 refresh token
    std::string value;
    long long expiration;
} TokenRet;

typedef struct
{
    int flag;
    int platform;
    std::string openID;
    std::vector<TokenRet> token;
} LoginRet;

#ifdef ANDROID

typedef struct
{
    int flag;
    int transaction_status;
    int result_code;
    std::string name;
    std::string icon;
    int app_points;
    std::string buyer_id;
    std::string transaction_id;
    int error_code;
    std::string exception_message;

} PurchaseRet;
#endif

typedef struct
{
    int platform;
    int flag;
    std::string desc;
} ShareRet;

typedef struct
{
    std::string key;
    std::string value;
} KVPair;

typedef struct
{
    int flag;
    int platform;
    std::string openID;
    std::string media_tag_name;
    std::vector<KVPair> extInfo;
} WakeUpRet;

typedef struct
{
    int flag;
    std::string desc;
} GGCallbackFlag;

#ifdef __OBJC__

typedef struct
{
    std::string transaction_id;
    std::string product_id;
    int point_amount;
    int role_id;
    int server_id;
    int quantity;
    std::string varItem;
} IAPPayRequestInfo;
#endif

// Utility functions to get and set object fields
#ifdef ANDROID

typedef struct
{
    int flag;
    std::string user_id;
    std::string user_name;
    std::string name;
} FacebookInfo;

#define JniGetAndSetStringField(fieldName, fieldNameStr, jOriginClass, jOriginObj, targetObj) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "Ljava/lang/String;"); \
jstring j##fieldName##FieldValue = (jstring) (env->GetObjectField(jOriginObj, j##fieldName##FieldId)); \
if (j##fieldName##FieldValue == NULL) {\
    targetObj.fieldName = ""; \
} else { \
    char const * c##fieldName##FieldValue = env->GetStringUTFChars(j##fieldName##FieldValue, NULL); \
    targetObj.fieldName = c##fieldName##FieldValue; \
    APP_DISPLAY_LOG("c%sFieldValue %s", fieldNameStr, c##fieldName##FieldValue); \
    env->ReleaseStringUTFChars(j##fieldName##FieldValue, c##fieldName##FieldValue); \
} \
env->DeleteLocalRef(j##fieldName##FieldValue);


#define JniGetAndSetIntField(fieldName, fieldNameStr, jOriginClass, jOriginObj, targetObj) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "I"); \
targetObj.fieldName = (int) (env->GetIntField(jOriginObj, j##fieldName##FieldId));


#define JniGetAndSetLongField(fieldName, fieldNameStr, jOriginClass, jOriginObj, targetObj) \
jfieldID j##fieldName##FieldId = env->GetFieldID(jOriginClass, fieldNameStr, "J"); \
targetObj.fieldName = (int) (env->GetLongField(jOriginObj, j##fieldName##FieldId));
#endif

#endif  /* GGCOMMON_H */