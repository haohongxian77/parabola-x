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
public class ToastUtils {

	private static Toast toast;
	private static Activity mActivity;
	private static String packageName;
	private static int version = android.os.Build.VERSION.SDK_INT;
	private static final int MAX_NEED_CANCEL_VERSION = 10;

	public static void initToastPackage(Activity activity, String packageName) {
		ToastUtils.packageName = packageName;
		mActivity = activity;
	}

	/**
	 * 
	 * @param context
	 * @param resId
	 */
	public static void ToastShort(int resId) {
		initToast(resId);
		showToast();
	}

	/**
	 * 
	 * @param context
	 * @param resId
	 */
	public static void ToastShortAnyWhere(int resId) {
		initToast(resId);
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				toast.show();
			}
		});

	}

	private static void showToast() {
		if (isTopActivity(mActivity, packageName)) {
			mActivity.runOnUiThread(new Runnable() {

				@Override
				public void run() {
					// TODO Auto-generated method stub
					toast.show();
				}
			});
		}
	}

	/**
	 * 
	 * @param context
	 * @param text
	 */
	public static void ToastShort(String text) {
		initToast(text);
		showToast();
	}

	/**
	 * 
	 * @param context
	 * @param text
	 */
	public static void ToastShortAnyWhere(String text) {
		initToast(text);
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				toast.show();
			}
		});
	}

	/**
	 * 
	 * @param context
	 * @param resId
	 */
	public static void ToastLong(int resId) {
		initToast(resId);
		toast.setDuration(Toast.LENGTH_LONG);
		showToast();
	}

	/**
	 * 
	 * @param context
	 * @param text
	 */
	public static void ToastLong(String text) {
		initToast(text);
		toast.setDuration(Toast.LENGTH_LONG);
		showToast();
	}

	/**
     * 
     */
	public static void hide() {
		if (toast == null) {
			return;
		}
		toast.cancel();
	}

	/**
	 * 
	 * @param context
	 * @param resId
	 */
	private static void initToast(int resId) {
		initToast(mActivity.getResources().getString(resId));
	}

	/**
	 * 
	 * @param context
	 * @param text
	 */
	private static void initToast(String text) {
		if (toast == null) {
			if (mActivity != null) {
				toast = Toast.makeText(mActivity, text, Toast.LENGTH_SHORT);
			}
		}
		toast.setText(text);
		if (version <= MAX_NEED_CANCEL_VERSION) {
			toast.cancel();
		}
	}

	public static boolean isTopActivity(Context context, String packageName) {
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
