/*
 * @Title: FaceBookClient.java 
 * @Package com.game.gws.jump.share 
 * @Description:  
 * @author czj  
 * @date 2015年5月17日 上午10:42:55 
 * @version V1.0.0   
 */
package com.game.gws.jump.share;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookSdk;
import com.facebook.share.Sharer;
import com.facebook.share.Sharer.Result;
import com.facebook.share.model.SharePhoto;
import com.facebook.share.model.SharePhotoContent;
import com.facebook.share.widget.ShareDialog;
import com.game.gws.jump.R;
import com.game.gws.jump.system.MyApp;

/**
 * @author czj
 * @Description: 使用facebook进行分享 {facebook 需要确定包名和签名（测试签名和正式签名）}
 *               分享的图片无要求必须放置到sdcard
 * @date 2015年5月17日 上午10:42:55
 */
public class FaceBookClient {
	public static final String TAG = FaceBookClient.class.getSimpleName();
	private static FaceBookClient INSTANCE;
	private Activity mActivity;
	private CallbackManager callbackManager;
	private ShareDialog shareDialog;
	private boolean canPresentShareDialogWithPhotos;

	public static FaceBookClient getInstance() {
		if (INSTANCE == null) {
			INSTANCE = new FaceBookClient();
		}
		return INSTANCE;
	}

	public FaceBookClient() {
		super();
		// TODO Auto-generated constructor stub
	}

	public void registerApp(Activity mActivity) {
		this.mActivity = mActivity;
		FacebookSdk.sdkInitialize(MyApp.getInstance());
		callbackManager = CallbackManager.Factory.create();
		shareDialog = new ShareDialog(mActivity);
		shareDialog.registerCallback(callbackManager,
				new FacebookCallback<Sharer.Result>() {

					@Override
					public void onSuccess(Result result) {
						// TODO Auto-generated method stub
						Log.d(TAG, "facebook onSuccess" + result.toString());
					}

					@Override
					public void onError(FacebookException error) {
						// TODO Auto-generated method stub
						Log.d(TAG, "facebook onError" + error.getMessage());
					}

					@Override
					public void onCancel() {
						// TODO Auto-generated method stub
						Log.d(TAG, "facebook onCancel");
					}
				}, 9901);
		// Can we present the share dialog for photos?
		canPresentShareDialogWithPhotos = ShareDialog
				.canShow(SharePhotoContent.class);
	}

	/**
	 * facebook分享图片
	 * 
	 * @param imgAbsPath
	 */
	public void shareImg(int status) {
		Bitmap image;
		if (status == -1) {
			image = BitmapFactory.decodeResource(mActivity.getResources(),
					R.drawable.icon);
		} else {
			image = ShareUtil.getScreenShot(mActivity);
		}
		// Bitmap image=BitmapFactory.decodeFile(imgAbsPath);
		SharePhoto photo = new SharePhoto.Builder().setBitmap(image).build();
		SharePhotoContent content = new SharePhotoContent.Builder().addPhoto(
				photo).build();
		if (shareDialog.canShow(SharePhotoContent.class)) {
			shareDialog.show(mActivity, content);
		}
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		callbackManager.onActivityResult(requestCode, resultCode, data);
	}

}
