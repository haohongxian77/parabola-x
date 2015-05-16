/*
 * @Title: SinaClient.java 
 * @Package org.cocos2dx.cpp.share 
 * @Description:  
 * @author czj  
 * @date 2015年4月18日 上午10:59:01 
 * @version V1.0.0   
 */
package com.game.gws.jump.share;

import android.app.Activity;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;

import com.game.gws.jump.R;
import com.sina.weibo.sdk.api.ImageObject;
import com.sina.weibo.sdk.api.TextObject;
import com.sina.weibo.sdk.api.WeiboMultiMessage;
import com.sina.weibo.sdk.api.share.BaseResponse;
import com.sina.weibo.sdk.api.share.IWeiboHandler.Response;
import com.sina.weibo.sdk.api.share.IWeiboShareAPI;
import com.sina.weibo.sdk.api.share.SendMultiMessageToWeiboRequest;
import com.sina.weibo.sdk.api.share.WeiboShareSDK;
import com.sina.weibo.sdk.auth.AuthInfo;
import com.sina.weibo.sdk.auth.Oauth2AccessToken;
import com.sina.weibo.sdk.auth.WeiboAuthListener;
import com.sina.weibo.sdk.constant.WBConstants;
import com.sina.weibo.sdk.exception.WeiboException;

/**
 * @author czj
 * @Description: 用于处理新浪第三方的事物(sina,需要确定包名，不需要确定签名)
 * @date 2015年4月18日 上午10:59:01
 */
public class SinaClient {
	private static final String TAG = SinaClient.class.getSimpleName();
	private static SinaClient INSTANCE;
	private Activity mActivity;
	public final String APP_KEY_SINA = "3893042256"; // 应用的APP_KEY
	public final String REDIRECT_URL_SINA = "http://www.sina.com";// 应用的回调页
	public final String SCOPE_SINA = // 应用申请的高级权限
	"email,direct_messages_read,direct_messages_write,"
			+ "friendships_groups_read,friendships_groups_write,statuses_to_me_read,"
			+ "follow_app_official_microblog," + "invitation_write";
	private static IWeiboShareAPI mWeiboShareAPI;

	public static SinaClient getInstance() {
		if (INSTANCE == null) {
			INSTANCE = new SinaClient();
		}
		return INSTANCE;
	}

	public SinaClient() {
		super();
	}

	public void registerApp(Activity mActivity) {
		this.mActivity = mActivity;
		mWeiboShareAPI = WeiboShareSDK.createWeiboAPI(mActivity, APP_KEY_SINA);
		mWeiboShareAPI.registerApp();
	}

	/**
	 * 
	 * @param shareText
	 * @return 文本消息
	 */
	private TextObject getTextObj(String shareText) {
		TextObject textObject = new TextObject();
		textObject.text = shareText;
		return textObject;
	}

	/**
	 * 
	 * @param absPath
	 * @return 图片消息
	 */

	private ImageObject getImgObj(String absPath) {
		ImageObject imageObject = new ImageObject();
		imageObject.setImageObject(BitmapFactory.decodeFile(absPath));
		return imageObject;
	}

	public void callShare(String imgAbsPath, String content) {//
		Log.e(TAG, "callShare   :====================");// + imgAbsPath + "/" +
														// content);
		SinaClient.getInstance().shareImgAndContent(imgAbsPath, content);
	}

	/**
	 * 分享图片和内容
	 * 
	 * @param imgAbsPath
	 *            图片的绝对路径
	 * @param content
	 */
	public void shareImgAndContent(String imgAbsPath, String content) {
		// 1. 初始化微博的分享消息
		WeiboMultiMessage weiboMessage = new WeiboMultiMessage();
		if (!TextUtils.isEmpty(content)) {
			weiboMessage.textObject = getTextObj(content);
		}
		if (!TextUtils.isEmpty(imgAbsPath)) {
			weiboMessage.imageObject = getImgObj(imgAbsPath);
		}
		// 2. 初始化从第三方到微博的消息请求
		SendMultiMessageToWeiboRequest request = new SendMultiMessageToWeiboRequest();
		// 用transaction唯一标识一个请求
		request.transaction = String.valueOf(System.currentTimeMillis());
		request.multiMessage = weiboMessage;

		AuthInfo authInfo = new AuthInfo(mActivity, APP_KEY_SINA,
				REDIRECT_URL_SINA, SCOPE_SINA);
		Oauth2AccessToken accessToken = AccessTokenKeeper
				.readAccessToken(mActivity.getApplicationContext());
		String token = "";
		if (accessToken != null) {
			token = accessToken.getToken();
		}
		mWeiboShareAPI.sendRequest(mActivity, request, authInfo, token,
				new WeiboAuthListener() {

					@Override
					public void onWeiboException(WeiboException arg0) {
					}

					@Override
					public void onComplete(Bundle bundle) {
						// TODO Auto-generated method stub
						Oauth2AccessToken newToken = Oauth2AccessToken
								.parseAccessToken(bundle);
						AccessTokenKeeper.writeAccessToken(
								mActivity.getApplicationContext(), newToken);
						Toast.makeText(
								mActivity.getApplicationContext(),
								"onAuthorizeComplete token = "
										+ newToken.getToken(), 0).show();
					}

					@Override
					public void onCancel() {
					}
				});

	}

	/**
	 * 放置在activity的onNewIntent当中
	 * 
	 * @param intent
	 * @param response
	 */
	public void handleWeiboResponse(Intent intent, Response response) {
		mWeiboShareAPI.handleWeiboResponse(intent, response);
	}

	/**
	 * 放置在activity的onResponse当中 （activity implements IWeiboHandler.Response）
	 * 
	 * @param baseResp
	 */
	public void onResponse(BaseResponse baseResp) {
		if (null != baseResp) {
			switch (baseResp.errCode) {
			case WBConstants.ErrorCode.ERR_OK:
				Toast.makeText(mActivity,
						R.string.weibosdk_toast_share_success,
						Toast.LENGTH_LONG).show();
				break;
			case WBConstants.ErrorCode.ERR_CANCEL:
				Toast.makeText(mActivity,
						R.string.weibosdk_toast_share_canceled,
						Toast.LENGTH_LONG).show();
				break;
			case WBConstants.ErrorCode.ERR_FAIL:
				Toast.makeText(
						mActivity,
						mActivity
								.getString(R.string.weibosdk_toast_share_failed)
								+ "Error Message: " + baseResp.errMsg,
						Toast.LENGTH_LONG).show();
				break;
			}
		}
	}

}
