/*
 * @Title: SinaClient.java 
 * @Package org.cocos2dx.cpp.share 
 * @Description:  
 * @author czj  
 * @date 2015年4月18日 上午10:59:01 
 * @version V1.0.0   
 */
package com.ych.game.gws.jump.share;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.text.TextUtils;

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
import com.sina.weibo.sdk.auth.sso.SsoHandler;
import com.sina.weibo.sdk.constant.WBConstants;
import com.sina.weibo.sdk.exception.WeiboException;
import com.ych.game.gws.jump.R;
import com.ych.game.gws.jump.share.ClientType.CurrentType;
import com.ych.game.gws.jump.share.ShareUtil.ScreenShotType;
import com.ych.game.gws.jump.system.MyApp;
import com.ych.game.gws.jump.ui.TransferActivity;

/**
 * @author czj
 * @Description: 用于处理新浪第三方的事物(sina,需要确定包名，不需要确定签名) 分享的图片无要求必须放置到sdcard
 * @date 2015年4月18日 上午10:59:01
 */
public class SinaClient {
	private static final String TAG = SinaClient.class.getSimpleName();
	private static SinaClient INSTANCE;
	private Activity mActivity;
	public final String APP_KEY_SINA = "3893042256"; // 应用的APP_KEY
	public final String REDIRECT_URL_SINA = "http://open.weibo.com/apps/3893042256/info/advanced";// 应用的回调页
	public final String SCOPE_SINA = // 应用申请的高级权限
	"email,direct_messages_read,direct_messages_write,"
			+ "friendships_groups_read,friendships_groups_write,statuses_to_me_read,"
			+ "follow_app_official_microblog," + "invitation_write";
	private IWeiboShareAPI mWeiboShareAPI;
	private AuthInfo mAuthInfo;
	private SsoHandler mSsoHandler;
	private int curStatus;
	private String curFilePath;

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
		mAuthInfo = new AuthInfo(mActivity, APP_KEY_SINA, REDIRECT_URL_SINA,
				SCOPE_SINA);
		mSsoHandler = new SsoHandler(mActivity, mAuthInfo);
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

	// /**
	// *
	// * @param status
	// * -1分享本地图片;1分享截屏
	// * @param content
	// */
	// public void callShare(int status) {//
	// Log.e(TAG, "callShare   :====================");// + imgAbsPath + "/" +
	// // content);
	// SinaClient.getInstance().shareImgAndContent(status);
	// }

	/**
	 * 分享图片和内容
	 * 
	 * @param status
	 *            -1,本地图片;1,截屏
	 * @param content
	 */
	public void shareImgAndContent(int status, String filePath) {
		// 1. 初始化微博的分享消息
		ClientType.getInstance().setCurType(CurrentType.SINA);
		curStatus = status;
		curFilePath = filePath;
		Oauth2AccessToken accessToken = AccessTokenKeeper.readAccessToken(MyApp
				.getInstance().getApplicationContext());
		String token = "";
		if (accessToken != null && accessToken.isSessionValid()) {
			token = accessToken.getToken();
			start2Share(curStatus, curFilePath, token);
		} else {
			mSsoHandler.authorize(new AuthListener());
		}

	}

	private void start2Share(int status, String filePath, String token) {
		String content = mActivity.getString(R.string.challenge_me);
		WeiboMultiMessage weiboMessage = new WeiboMultiMessage();
		if (!TextUtils.isEmpty(content)) {
			weiboMessage.textObject = getTextObj(content);
		}
		Bitmap bitmap;
		if (status == -1) {
			bitmap = BitmapFactory.decodeResource(mActivity.getResources(),
					R.drawable.icon);
		} else {
			bitmap = BitmapFactory.decodeFile(filePath);
		}
		boolean flag = ShareUtil.saveScreenShot(
				status == -1 ? ScreenShotType.GAME_SCREEN_SHOT
						: ScreenShotType.SCORE_SCREEN_SHOT, bitmap);
		if (!flag) {
			ToastClient.getInstance().showToastShort(
					R.string.share_sdcard_error);
			return;
		}
		String imgAbsPath = ShareUtil
				.getAbsPath(status == -1 ? ScreenShotType.GAME_SCREEN_SHOT
						: ScreenShotType.SCORE_SCREEN_SHOT);
		if (!TextUtils.isEmpty(imgAbsPath)) {
			weiboMessage.imageObject = getImgObj(imgAbsPath);
		}
		// 2. 初始化从第三方到微博的消息请求
		SendMultiMessageToWeiboRequest request = new SendMultiMessageToWeiboRequest();
		// 用transaction唯一标识一个请求
		request.transaction = String.valueOf(System.currentTimeMillis());
		request.multiMessage = weiboMessage;
		// mWeiboShareAPI.sendRequest(arg0, arg1, arg2, arg3, arg4)
		mWeiboShareAPI.sendRequest(mActivity, request, mAuthInfo, token,
				new WeiboAuthListener() {

					@Override
					public void onWeiboException(WeiboException arg0) {
						TransferActivity.closeAct();
						ToastClient.getInstance().showToastShort(
								R.string.share_fail);
					}

					@Override
					public void onComplete(Bundle bundle) {
						// TODO Auto-generated method stub
						TransferActivity.closeAct();
						Oauth2AccessToken newToken = Oauth2AccessToken
								.parseAccessToken(bundle);
						AccessTokenKeeper.writeAccessToken(MyApp.getInstance()
								.getApplicationContext(), newToken);
						ToastClient.getInstance().showToastShort(
								R.string.share_success);
					}

					@Override
					public void onCancel() {
						TransferActivity.closeAct();
						ToastClient.getInstance().showToastShort(
								R.string.share_cancel);
					}
				});
	}

	/**
	 * 当 SSO 授权 Activity 退出时，该函数被调用。
	 * 
	 * @see {@link Activity#onActivityResult}
	 */
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		// SSO 授权回调
		// 重要：发起 SSO 登陆的 Activity 必须重写 onActivityResult
		if (mSsoHandler != null) {
			mSsoHandler.authorizeCallBack(requestCode, resultCode, data);
		}
	}

	/**
	 * 微博认证授权回调类。 1. SSO 授权时，需要在 {@link #onActivityResult} 中调用
	 * {@link SsoHandler#authorizeCallBack} 后， 该回调才会被执行。 2. 非 SSO
	 * 授权时，当授权结束后，该回调就会被执行。 当授权成功后，请保存该 access_token、expires_in、uid 等信息到
	 * SharedPreferences 中。
	 */
	class AuthListener implements WeiboAuthListener {

		@Override
		public void onCancel() {
			// TODO Auto-generated method stub
			TransferActivity.closeAct();
			ToastClient.getInstance().showToastShort(R.string.share_cancel);
		}

		@Override
		public void onComplete(Bundle bundle) {
			// TODO Auto-generated method stub
			Oauth2AccessToken newToken = Oauth2AccessToken
					.parseAccessToken(bundle);
			AccessTokenKeeper.writeAccessToken(MyApp.getInstance()
					.getApplicationContext(), newToken);
			start2Share(curStatus, curFilePath, newToken.getToken());
		}

		@Override
		public void onWeiboException(WeiboException arg0) {
			// TODO Auto-generated method stub
			ToastClient.getInstance().showToastShort(R.string.share_fail);
			TransferActivity.closeAct();
		}

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
				ToastClient.getInstance()
						.showToastShort(R.string.share_success);
				break;
			case WBConstants.ErrorCode.ERR_CANCEL:
				ToastClient.getInstance().showToastShort(R.string.share_cancel);
				break;
			case WBConstants.ErrorCode.ERR_FAIL:
				ToastClient.getInstance().showToastShort(R.string.share_fail);
				break;
			}
		}
	}

}
