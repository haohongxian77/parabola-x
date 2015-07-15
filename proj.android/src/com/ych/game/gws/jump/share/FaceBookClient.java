/*
 * @Title: FaceBookClient.java 
 * @Package com.game.gws.jump.share 
 * @Description:  
 * @author czj  
 * @date 2015年5月17日 上午10:42:55 
 * @version V1.0.0   
 */
package com.ych.game.gws.jump.share;

import java.util.Arrays;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Log;

import com.facebook.FacebookAuthorizationException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.FacebookRequestError;
import com.facebook.Request;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;
import com.facebook.model.GraphObject;
import com.facebook.widget.FacebookDialog;
import com.ych.game.gws.jump.R;
import com.ych.game.gws.jump.share.ClientType.CurrentType;
import com.ych.game.gws.jump.ui.TransferActivity;

/**
 * @author czj
 * @Description: 使用facebook进行分享 {facebook 需要确定包名和签名（测试签名和正式签名）}
 *               分享的图片无要求必须放置到sdcard
 * @date 2015年5月17日 上午10:42:55
 */
public class FaceBookClient {
	private interface GraphObjectWithId extends GraphObject {
		String getId();
	}

	public static final String TAG = FaceBookClient.class.getSimpleName();
	private final String PENDING_ACTION_BUNDLE_KEY = "PendingAction";

	private static FaceBookClient INSTANCE;
	private Activity mActivity;
	// private PendingAction pendingAction = PendingAction.NONE;
	private boolean canPresentShareDialog;
	private boolean canPresentShareDialogWithPhotos;
	private static final String PERMISSION = "publish_actions";
	private int curStatus = -10;
	private String curFilePath;
	private PendingAction pendingAction = PendingAction.NONE;
	private UiLifecycleHelper uiHelper;
	private Session.StatusCallback callback = new Session.StatusCallback() {
		@Override
		public void call(Session session, SessionState state,
				Exception exception) {
			onSessionStateChange(session, state, exception);
		}
	};
	private FacebookDialog.Callback dialogCallback = new FacebookDialog.Callback() {
		@Override
		public void onError(FacebookDialog.PendingCall pendingCall,
				Exception error, Bundle data) {
			Log.d("HelloFacebook", String.format("Error: %s", error.toString()));
			TransferActivity.closeAct();
			ToastClient.getInstance().showToastShort(R.string.share_fail);
		}

		@Override
		public void onComplete(FacebookDialog.PendingCall pendingCall,
				Bundle data) {
			Log.d("HelloFacebook", "Success!");
			ToastClient.getInstance().showToastShort(R.string.share_success);
		}
	};

	private void onSessionStateChange(Session session, SessionState state,
			Exception exception) {
		if (pendingAction != PendingAction.NONE
				&& (exception instanceof FacebookOperationCanceledException || exception instanceof FacebookAuthorizationException)) {
			new AlertDialog.Builder(mActivity).setTitle(R.string.share_cancel)
					.setMessage(R.string.permission_not_granted)
					.setPositiveButton(R.string.ok, null).show();
			pendingAction = PendingAction.NONE;
		} else if (state == SessionState.OPENED_TOKEN_UPDATED) {
			handlePendingAction();
		}
	}

	private enum PendingAction {
		NONE, POST_PHOTO, POST_STATUS_UPDATE
	}

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

	public void onSaveInstanceState(Bundle outState) {
		uiHelper.onSaveInstanceState(outState);

		outState.putString(PENDING_ACTION_BUNDLE_KEY, pendingAction.name());
	}

	public void onResume() {
		if (ClientType.getInstance().getCurType() == CurrentType.FACEBOOK) {
			uiHelper.onResume();
		}

	}

	public void onPause() {
		if (ClientType.getInstance().getCurType() == CurrentType.FACEBOOK) {
			uiHelper.onPause();
		}
	}

	public void onDestroy() {
		if (ClientType.getInstance().getCurType() == CurrentType.FACEBOOK) {
			uiHelper.onDestroy();
		}
	}

	public void onActivityResult(final int requestCode, final int resultCode,
			final Intent data) {
		if (ClientType.getInstance().getCurType() == CurrentType.FACEBOOK) {
			uiHelper.onActivityResult(requestCode, resultCode, data,
					dialogCallback);
		}

	}

	public void registerApp(final Activity mActivity,
			final Bundle savedInstanceState) {
		Log.e(TAG, "registerApp");
		this.mActivity = mActivity;
		// TODO Auto-generated method stub
		if (null == mActivity) {
			return;
		}
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				uiHelper = new UiLifecycleHelper(mActivity, callback);
				uiHelper.onCreate(savedInstanceState);
				if (savedInstanceState != null) {
					String name = savedInstanceState
							.getString(PENDING_ACTION_BUNDLE_KEY);
					Log.e("-----------", "内容===" + name);
					pendingAction = PendingAction.valueOf(name);
				}
				// Can we present the share dialog for regular links?
				canPresentShareDialog = FacebookDialog.canPresentShareDialog(
						mActivity,
						FacebookDialog.ShareDialogFeature.SHARE_DIALOG);
				// Can we present the share dialog for photos?
				canPresentShareDialogWithPhotos = FacebookDialog
						.canPresentShareDialog(mActivity,
								FacebookDialog.ShareDialogFeature.PHOTOS);
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
		curStatus = status;
		curFilePath = filePath;
		if (!canPresentShareDialogWithPhotos) {
			ToastClient.getInstance().showToastShort(R.string.install_facebook);
			TransferActivity.closeAct();
			return;
		}
		performPublish(PendingAction.POST_PHOTO,
				canPresentShareDialogWithPhotos);
	}

	private void performPublish(PendingAction action, boolean allowNoSession) {
		Session session = Session.getActiveSession();
		if (session != null) {
			pendingAction = action;
			if (hasPublishPermission()) {
				// We can do the action right away.
				handlePendingAction();
				return;
			} else if (session.isOpened()) {
				// We need to get new permissions, then complete the action when
				// we get called back.
				session.requestNewPublishPermissions(new Session.NewPermissionsRequest(
						mActivity, PERMISSION));
				return;
			}
		}

		if (allowNoSession) {
			pendingAction = action;
			handlePendingAction();
		}
	}

	private void handlePendingAction() {
		PendingAction previouslyPendingAction = pendingAction;
		// These actions may re-set pendingAction if they are still pending, but
		// we assume they
		// will succeed.
		pendingAction = PendingAction.NONE;

		switch (previouslyPendingAction) {
		case POST_PHOTO:
			postPhoto();
			break;
		case POST_STATUS_UPDATE:
			// postStatusUpdate();
			break;
		}
	}

	private void postPhoto() {
		if (null == mActivity) {
			return;
		}
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				Bitmap image;
				if (curStatus == -1) {
					image = BitmapFactory.decodeResource(
							mActivity.getResources(), R.drawable.icon);
				} else {
					image = BitmapFactory.decodeFile(curFilePath);
				}
				if (canPresentShareDialogWithPhotos) {
					FacebookDialog shareDialog = createShareDialogBuilderForPhoto(
							image).build();
					uiHelper.trackPendingDialogCall(shareDialog.present());
				} else if (hasPublishPermission()) {
					Request request = Request.newUploadPhotoRequest(
							Session.getActiveSession(), image,
							new Request.Callback() {
								@Override
								public void onCompleted(Response response) {
									showPublishResult(mActivity
											.getString(R.string.photo_post),
											response.getGraphObject(), response
													.getError());
								}
							});
					request.executeAsync();
				} else {
					pendingAction = PendingAction.POST_PHOTO;
				}
			}
		});

	}

	private void showPublishResult(String message, GraphObject result,
			FacebookRequestError error) {
		if (null == mActivity) {
			return;
		}
		String title = null;
		String alertMessage = null;
		if (error == null) {
			title = mActivity.getString(R.string.share_success);
			String id = result.cast(GraphObjectWithId.class).getId();
			alertMessage = mActivity.getString(R.string.share_success, message,
					id);
		} else {
			title = mActivity.getString(R.string.share_fail);
			alertMessage = error.getErrorMessage();
		}

		new AlertDialog.Builder(mActivity)
				.setTitle(title)
				.setMessage(alertMessage)
				.setPositiveButton(R.string.ok,
						new DialogInterface.OnClickListener() {

							@Override
							public void onClick(DialogInterface arg0, int arg1) {
								// TODO Auto-generated method stub
								TransferActivity.closeAct();
							}

						}).show();
	}

	private boolean hasPublishPermission() {
		Session session = Session.getActiveSession();
		return session != null
				&& session.getPermissions().contains("publish_actions");
	}

	private FacebookDialog.PhotoShareDialogBuilder createShareDialogBuilderForPhoto(
			Bitmap... photos) {
		return new FacebookDialog.PhotoShareDialogBuilder(mActivity)
				.addPhotos(Arrays.asList(photos));
	}
}
