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

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.BitmapFactory;
import android.text.TextUtils;
import android.widget.Toast;

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
 * @Description: 用于处理微信的第三方事物
 * @date 2015年4月18日 上午11:00:50
 */
public class WxClient {
	private static final int THUMB_SIZE = 150;
	public static final String APP_ID = "wx644a5864a554f4f2";
	public static final String APP_SECRET = "b7a42c91be34da26fd9f2843bf7d6371";
	public static final String APP_TRANSATION = "wx_transaction";
	/** IWXAPI 是第三方app和微信通信的openapi接口 **/
	private static IWXAPI iwxapi;
	private static Activity mActivity;

	public WxClient(Activity mActivity) {
		super();
		if (null != mActivity) {
			this.mActivity = mActivity;
			iwxapi = WXAPIFactory.createWXAPI(mActivity, APP_ID, false);
			iwxapi.registerApp(APP_ID);
		}
	}

	/***
	 * 将纯图分享到朋友圈
	 * 
	 * @param imgAbsPath
	 */
	public static void shareImg(String imgAbsPath, String content) {
		WXImageObject imgObj = new WXImageObject();
		imgObj.setImagePath(imgAbsPath);

		WXMediaMessage msg = new WXMediaMessage();
		msg.mediaObject = imgObj;
		msg.description = content;

		Bitmap bmp = BitmapFactory.decodeFile(imgAbsPath);
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
			Toast.makeText(mActivity.getApplicationContext(), response.errStr,
					Toast.LENGTH_LONG).show();
		}
	}

	public static byte[] bmpToByteArray(final Bitmap bmp,
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
