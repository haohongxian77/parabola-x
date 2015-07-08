/*
 * @Title: FaceBookClient.java 
 * @Package com.game.gws.jump.share 
 * @Description:  
 * @author czj  
 * @date 2015年5月17日 上午10:42:55 
 * @version V1.0.0   
 */
package com.game.gws.jump.share;

import java.util.ArrayList;
import java.util.Arrays;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.text.TextUtils;
import android.util.Log;

import com.facebook.AccessToken;
import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookSdk;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;
import com.facebook.share.ShareApi;
import com.facebook.share.Sharer;
import com.facebook.share.Sharer.Result;
import com.facebook.share.model.SharePhoto;
import com.facebook.share.model.SharePhotoContent;
import com.facebook.share.widget.ShareDialog;
import com.game.gws.jump.R;
import com.game.gws.jump.share.ClientType.CurrentType;
import com.game.gws.jump.ui.TransferActivity;

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
	// private PendingAction pendingAction = PendingAction.NONE;
	private boolean canPresentShareDialog;
	private boolean canPresentShareDialogWithPhotos;
	private static final String PERMISSION = "publish_actions";
	private int curStatus = -10;
	private String curFilePath;

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

	public void registerApp(final Activity mActivity) {
		Log.e(TAG, "registerApp");
		this.mActivity = mActivity;

		// TODO Auto-generated method stub
		FacebookSdk.sdkInitialize(mActivity.getApplicationContext());
		callbackManager = CallbackManager.Factory.create();
		shareDialog = new ShareDialog(mActivity);
		shareDialog.registerCallback(callbackManager,
				new FacebookCallback<Sharer.Result>() {

					@Override
					public void onSuccess(Result result) {
						// TODO Auto-generated method stub
						// ToastClient.getInstance().showToastShort(
						// R.string.share_success);
						TransferActivity.closeAct();
					}

					@Override
					public void onError(FacebookException error) {
						// TODO Auto-generated method stub
						TransferActivity.closeAct();
						ToastClient.getInstance().showToastShort(
								R.string.share_fail);
					}

					@Override
					public void onCancel() {
						// TODO Auto-generated method stub
						TransferActivity.closeAct();
						ToastClient.getInstance().showToastShort(
								R.string.share_cancel);
					}
				});
		// Can we present the share dialog for photos?
		canPresentShareDialogWithPhotos = ShareDialog
				.canShow(SharePhotoContent.class);
		LoginManager.getInstance().registerCallback(callbackManager,
				new FacebookCallback<LoginResult>() {

					@Override
					public void onSuccess(LoginResult result) {
						// TODO Auto-generated method stub
						if (curStatus != -10 && !TextUtils.isEmpty(curFilePath)) {
							shareImg(curStatus, curFilePath);
						}

					}

					@Override
					public void onError(FacebookException error) {
						// TODO Auto-generated method stub
						TransferActivity.closeAct();
						ToastClient.getInstance().showToastShort(
								R.string.share_fail);
					}

					@Override
					public void onCancel() {
						// TODO Auto-generated method stub
						TransferActivity.closeAct();
						ToastClient.getInstance().showToastShort(
								R.string.share_cancel);
					}
				});

	}

	/**
	 * facebook分享图片
	 * 
	 * @param imgAbsPath
	 */
	public void shareImg(final int status, final String filePath) {
		// TODO Auto-generated method stub
		ClientType.getInstance().setCurType(CurrentType.FACEBOOK);
		// TODO Auto-generated method stub
		if (!canPresentShareDialogWithPhotos) {
			ToastClient.getInstance().showToastShort(R.string.install_facebook);
			TransferActivity.closeAct();
			return;
		}
		AccessToken accessToken = AccessToken.getCurrentAccessToken();
		if (accessToken != null) {
			// pendingAction = PendingAction.POST_PHOTO;
			if (hasPublishPermission()) {
				// We can do the action right away.
				startToShare(status, filePath);
				return;
			} else {
				// We need to get new permissions, then complete the
				// action when
				// we get called back.
				LoginManager.getInstance().logInWithPublishPermissions(
						mActivity, Arrays.asList(PERMISSION));
				return;
			}
		}

		if (canPresentShareDialogWithPhotos) {
			// pendingAction = PendingAction.POST_PHOTO;
			startToShare(status, filePath);
		}

	}

	private boolean hasPublishPermission() {
		AccessToken accessToken = AccessToken.getCurrentAccessToken();
		return accessToken != null
				&& accessToken.getPermissions().contains("publish_actions");
	}

	private void startToShare(final int status, final String filePath) {
		curStatus = status;
		curFilePath = filePath;
		Bitmap image;
		if (status == -1) {
			image = BitmapFactory.decodeResource(mActivity.getResources(),
					R.drawable.icon);
		} else {
			image = BitmapFactory.decodeFile(filePath);
		}
		SharePhoto sharePhoto = new SharePhoto.Builder().setBitmap(image)
				.build();
		ArrayList<SharePhoto> photos = new ArrayList<SharePhoto>();
		photos.add(sharePhoto);

		SharePhotoContent sharePhotoContent = new SharePhotoContent.Builder()
				.setPhotos(photos).build();
		if (canPresentShareDialogWithPhotos) {
			shareDialog.show(sharePhotoContent);
		} else if (hasPublishPermission()) {
			ShareApi.share(sharePhotoContent,
					new FacebookCallback<Sharer.Result>() {

						@Override
						public void onSuccess(Result result) {
							// TODO Auto-generated method stub
							// ToastClient.getInstance().showToastShort(
							// R.string.share_success);
							TransferActivity.closeAct();
						}

						@Override
						public void onError(FacebookException error) {
							// TODO Auto-generated method stub
							TransferActivity.closeAct();
							ToastClient.getInstance().showToastShort(
									R.string.share_fail);
						}

						@Override
						public void onCancel() {
							// TODO Auto-generated method stub
							TransferActivity.closeAct();
							ToastClient.getInstance().showToastShort(
									R.string.share_cancel);
						}
					});
		} else {
			// pendingAction = PendingAction.POST_PHOTO;
		}
	}

	public void onActivityResult(final int requestCode, final int resultCode,
			final Intent data) {
		callbackManager.onActivityResult(requestCode, resultCode, data);

	}

}
