/*
 * @Title: TencentClient.java 
 * @Package org.cocos2dx.cpp.share 
 * @Description:  
 * @author czj  
 * @date 2015年4月18日 上午10:59:57 
 * @version V1.0.0   
 */
package com.game.gws.jump.share;

import java.io.File;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

import com.game.gws.jump.R;
import com.game.gws.jump.share.ShareUtil.ScreenShotType;
import com.tencent.connect.share.QQShare;
import com.tencent.tauth.IUiListener;
import com.tencent.tauth.Tencent;
import com.tencent.tauth.UiError;

/**
 * @author czj
 * @Description: 用于处理qq的第三方事物(分享 qq,不需要确定包名和签名) 分享的图片要求必须放置到sdcard
 * @date 2015年4月18日 上午10:59:57
 */
public class TencentClient {
	public static final String TAG = TencentClient.class.getSimpleName();
	public static TencentClient INSTANCE;
	private final String APP_ID = "1104440171";
	private final String APP_KEY = "xVJqmHS1g1orgU8g";
	private final String APP_NAME = "完美抛物线";
	private Activity mActivity;
	private Tencent mTencent;

	public static TencentClient getInstance() {
		if (null == INSTANCE) {
			INSTANCE = new TencentClient();
		}
		return INSTANCE;
	}

	public TencentClient() {
		super();
	}

	public void registerApp(Activity mActivity) {
		this.mActivity = mActivity;
		mTencent = Tencent.createInstance(APP_ID,
				mActivity.getApplicationContext());
	}

	/**
	 * 纯图分享
	 * 
	 * @param status
	 *            -1,分享本地图片;1,分享截屏图片
	 */
	public void shareImg(int status) {
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
		imgAbsPath = Environment.getExternalStorageDirectory()
				.getAbsolutePath()
				+ File.separator
				+ "czj"
				+ File.separator
				+ "test.png";
		Log.e(TAG, "imgAbsPath:" + imgAbsPath);

		// TODO Auto-generated method stub
		Looper.prepare();
		Bundle params = new Bundle();
		params.putInt(QQShare.SHARE_TO_QQ_KEY_TYPE,
				QQShare.SHARE_TO_QQ_TYPE_IMAGE);
		params.putString(QQShare.SHARE_TO_QQ_IMAGE_LOCAL_URL, imgAbsPath);
		params.putString(QQShare.SHARE_TO_QQ_APP_NAME, APP_NAME);
		params.putInt(QQShare.SHARE_TO_QQ_EXT_INT,
				QQShare.SHARE_TO_QQ_FLAG_QZONE_AUTO_OPEN);
		mTencent.shareToQQ(mActivity, params, new IUiListener() {

			@Override
			public void onError(UiError error) {
				// TODO Auto-generated method stub
				Toast.makeText(mActivity.getApplicationContext(),
						"onError:" + error.errorMessage, Toast.LENGTH_SHORT)
						.show();
			}

			@Override
			public void onComplete(Object arg0) {
				// TODO Auto-generated method stub
				Toast.makeText(mActivity.getApplicationContext(), "分享成功",
						Toast.LENGTH_SHORT).show();
			}

			@Override
			public void onCancel() {
				// TODO Auto-generated method stub
				Toast.makeText(mActivity.getApplicationContext(), "cancel",
						Toast.LENGTH_SHORT).show();
			}
		});

	}

	/**
	 * 放置到activity的onActivityResult当中
	 * 
	 * @param requestCode
	 * @param resultCode
	 * @param data
	 */
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (null != mTencent) {
			mTencent.onActivityResult(requestCode, resultCode, data);
		}
	};

}
