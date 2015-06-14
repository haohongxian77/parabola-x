/*
 * @Title: ToastUtils.java 
 * @Package com.game.gws.jump.share 
 * @Description:  
 * @author czj  
 * @date 2015年6月1日 下午10:32:20 
 * @version V1.0.0   
 */
package com.game.gws.jump.share;

import java.util.List;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningTaskInfo;
import android.content.Context;
import android.text.TextUtils;
import android.widget.Toast;

/**
 * @author czj
 * @Description:
 * @date 2015年6月1日 下午10:32:20
 */
public class ToastClient {
	private static final String TAG = ToastClient.class.getSimpleName();
	private Toast toast;
	private Activity mActivity;
	private String packageName;
	private int version = android.os.Build.VERSION.SDK_INT;
	private final int MAX_NEED_CANCEL_VERSION = 10;
	private static ToastClient INSTANCE;

	public ToastClient() {
		super();
		// TODO Auto-generated constructor stub
	}

	public static ToastClient getInstance() {
		if (null == INSTANCE) {
			INSTANCE = new ToastClient();
		}
		return INSTANCE;
	}

	public void registerClient(Activity activity, String packageName) {
		this.mActivity = activity;
		this.packageName = packageName;
	}

	public void showToastLong(final String text) {
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if (!isTopActivity(mActivity, packageName)) {
					return;
				}
				if (toast == null) {
					if (mActivity != null) {
						toast = Toast.makeText(mActivity, text,
								Toast.LENGTH_SHORT);
					}
				}
				toast.setText(text);
				if (version <= MAX_NEED_CANCEL_VERSION) {
					toast.cancel();
				}
				toast.show();
			}
		});

	}

	public void showToastLongOutUiThread(final String text) {
		// if (!isTopActivity(mActivity, packageName)) {
		// return;
		// }
		if (toast == null) {
			if (mActivity != null) {
				toast = Toast.makeText(mActivity, text, Toast.LENGTH_SHORT);
			}
		}
		toast.setText(text);
		if (version <= MAX_NEED_CANCEL_VERSION) {
			toast.cancel();
		}
		toast.show();
	}

	public void showToastShort(final String text) {
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if (!isTopActivity(mActivity, packageName)) {
					return;
				}
				if (toast == null) {
					if (mActivity != null) {
						toast = Toast.makeText(mActivity, text,
								Toast.LENGTH_SHORT);
					}
				}
				toast.setText(text);
				if (version <= MAX_NEED_CANCEL_VERSION) {
					toast.cancel();
				}
				toast.show();
			}
		});

	}

	public void showToastShortOutUiThread(final String text) {
		if (!isTopActivity(mActivity, packageName)) {
			return;
		}
		if (toast == null) {
			if (mActivity != null) {
				toast = Toast.makeText(mActivity, text, Toast.LENGTH_SHORT);
			}
		}
		toast.setText(text);
		if (version <= MAX_NEED_CANCEL_VERSION) {
			toast.cancel();
		}
		toast.show();

	}

	public void showToastShort(final int textRes) {
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if (!isTopActivity(mActivity, packageName)) {
					return;
				}
				String text = mActivity.getResources().getString(textRes);
				if (toast == null) {
					if (mActivity != null) {
						toast = Toast.makeText(mActivity, text,
								Toast.LENGTH_SHORT);
					}
				}
				toast.setText(text);
				if (version <= MAX_NEED_CANCEL_VERSION) {
					toast.cancel();
				}
				toast.show();
			}
		});

	}

	private boolean isTopActivity(Context context, String packageName) {
		if (context == null || TextUtils.isEmpty(packageName)) {
			return false;
		}

		ActivityManager activityManager = (ActivityManager) context
				.getSystemService(Context.ACTIVITY_SERVICE);
		List<RunningTaskInfo> tasksInfo = activityManager.getRunningTasks(1);
		if (tasksInfo == null || tasksInfo.size() == 0) {
			return false;
		}
		try {
			return packageName.equals(tasksInfo.get(0).topActivity
					.getPackageName());
		} catch (Exception e) {
			return false;
		}
	}
}
