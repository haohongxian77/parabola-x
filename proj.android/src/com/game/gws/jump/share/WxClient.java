/*
 * @Title: WxClient.java 
 * @Package org.cocos2dx.cpp.share 
 * @Description:  
 * @author czj  
 * @date 2015年4月18日 上午11:00:50 
 * @version V1.0.0   
 */
package com.game.gws.jump.share;

import java.io.ByteArrayOutputStream;
import java.io.File;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;

import com.game.gws.jump.R;
import com.game.gws.jump.share.ShareUtil.ScreenShotType;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.modelmsg.SendMessageToWX;
import com.tencent.mm.sdk.modelmsg.SendMessageToWX.Resp;
import com.tencent.mm.sdk.modelmsg.WXImageObject;
import com.tencent.mm.sdk.modelmsg.WXMediaMessage;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

/**
 * @author czj
 * @Description: 用于处理微信的第三方事物(必须安装微信客户端) wx,需要确定包名和签名; 分享的图片无要求必须放置到sdcard
 * @date 2015年4月18日 上午11:00:50
 */
public class WxClient {
	public static final String TAG = WxClient.class.getSimpleName();
	public static WxClient INSTANCE;
	private final int THUMB_SIZE = 150;
	public static final String APP_ID = "wx644a5864a554f4f2";
	public final String APP_SECRET = "b7a42c91be34da26fd9f2843bf7d6371";
	public final String APP_TRANSATION = "wx_transaction";
	private String mImgAbsPath = "";
	private String mContent = "";
	/** IWXAPI 是第三方app和微信通信的openapi接口 **/
	private static IWXAPI iwxapi;
	private Activity mActivity;

	public static WxClient getInstance() {
		if (null == INSTANCE) {
			INSTANCE = new WxClient();
		}
		return INSTANCE;
	}

	public WxClient() {
		super();
	}

	public void registerApp(Activity mActivity) {
		this.mActivity = mActivity;
		iwxapi = WXAPIFactory.createWXAPI(mActivity, APP_ID);
		iwxapi.registerApp(APP_ID);
	}

	/***
	 * 将纯图分享到朋友圈
	 * 
	 * @param imgAbsPath
	 */
	public void shareImg(int status, final String content) {

		if (!iwxapi.isWXAppInstalled() || !iwxapi.isWXAppSupportAPI()) {
			Toast.makeText(mActivity, "请安装最新版微信后重试", Toast.LENGTH_LONG).show();
			return;
		}
		Bitmap bitmap;
		if (status == -1) {
			bitmap = BitmapFactory.decodeResource(mActivity.getResources(),
					R.drawable.icon);
		} else {
			bitmap = ShareUtil.getScreenShot(mActivity);
		}
		boolean flag = ShareUtil.saveScreenShot(
				status == -1 ? ScreenShotType.GAME_SCREEN_SHOT
						: ScreenShotType.SCORE_SCREEN_SHOT, bitmap);
		if (!flag) {
			Toast.makeText(mActivity, R.string.share_sdcard_error,
					Toast.LENGTH_LONG).show();
			return;
		}
		String imgAbsPath = ShareUtil
				.getAbsPath(status == -1 ? ScreenShotType.GAME_SCREEN_SHOT
						: ScreenShotType.SCORE_SCREEN_SHOT);
		Log.e(TAG, "shareImg:" + imgAbsPath);
		mImgAbsPath = Environment.getExternalStorageDirectory()
				.getAbsolutePath()
				+ File.separator
				+ "czj"
				+ File.separator
				+ "test.png";
		mContent = content;
		Log.e(TAG, "imgAbsPath:" + mImgAbsPath);
		WXImageObject imgObj = new WXImageObject();
		imgObj.setImagePath(mImgAbsPath);

		WXMediaMessage msg = new WXMediaMessage();
		msg.mediaObject = imgObj;
		msg.description = content;

		Bitmap bmp = BitmapFactory.decodeFile(mImgAbsPath);
		Bitmap thumbBmp = Bitmap.createScaledBitmap(bmp, THUMB_SIZE,
				THUMB_SIZE, true);
		bmp.recycle();
		msg.thumbData = bmpToByteArray(thumbBmp, true);

		SendMessageToWX.Req req = new SendMessageToWX.Req();
		req.transaction = APP_TRANSATION;
		req.message = msg;
		req.scene = SendMessageToWX.Req.WXSceneTimeline;
		if (null == iwxapi) {
			return;
		}
		iwxapi.sendReq(req);

	}

	public void handleIntent(Intent intent, IWXAPIEventHandler handler) {
		if (null == iwxapi) {
			return;
		}
		iwxapi.handleIntent(intent, handler);

	}

	public void unregisterApp() {
		if (null == iwxapi) {
			return;
		}
		iwxapi.unregisterApp();
	}

	/**
	 * 处理微信的响应
	 * 
	 * @param resp
	 */
	public void handleResp(BaseResp resp) {
		if (null == resp) {// 失败
			Toast.makeText(mActivity.getApplicationContext(), "分享失败",
					Toast.LENGTH_LONG).show();
			return;
		}
		String transation = resp.transaction;
		if (!TextUtils.isEmpty(transation)
				&& transation.equalsIgnoreCase(APP_TRANSATION)
				&& resp instanceof SendMessageToWX.Resp) {
			SendMessageToWX.Resp response = (Resp) resp;
			int result = 0;

			switch (resp.errCode) {
			case BaseResp.ErrCode.ERR_OK:
				result = R.string.errcode_success;
				break;
			case BaseResp.ErrCode.ERR_USER_CANCEL:
				result = R.string.errcode_cancel;
				break;
			case BaseResp.ErrCode.ERR_AUTH_DENIED:
				result = R.string.errcode_deny;
				break;
			default:
				result = R.string.errcode_unknown;
				break;
			}

			Toast.makeText(mActivity, result, Toast.LENGTH_LONG).show();
		}
	}

	private static byte[] bmpToByteArray(final Bitmap bmp,
			final boolean needRecycle) {
		ByteArrayOutputStream output = new ByteArrayOutputStream();
		bmp.compress(CompressFormat.PNG, 100, output);
		if (needRecycle) {
			bmp.recycle();
		}

		byte[] result = output.toByteArray();
		try {
			output.close();
		} catch (Exception e) {
			e.printStackTrace();
		}

		return result;
	}

}
