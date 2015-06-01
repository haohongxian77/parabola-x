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
	private static String packageName;
	private static int version = android.os.Build.VERSION.SDK_INT;
	private static final int MAX_NEED_CANCEL_VERSION = 10;

	public static void initToast(String packageName) {
		ToastUtils.packageName = packageName;
	}

	/**
	 * 
	 * @param context
	 * @param resId
	 */
	public static void ToastShort(Context context, int resId) {
		initToast(context, resId);
		showToast(context);
	}

	/**
	 * 
	 * @param context
	 * @param resId
	 */
	public static void ToastShortAnyWhere(Context context, int resId) {
		initToast(context, resId);
		toast.show();
	}

	private static void showToast(Context context) {
		if (isTopActivity(context, packageName)) {
			toast.show();
		}
	}

	/**
	 * 
	 * @param context
	 * @param text
	 */
	public static void ToastShort(Context context, String text) {
		initToast(context, text);
		showToast(context);
	}

	/**
	 * 
	 * @param context
	 * @param text
	 */
	public static void ToastShortAnyWhere(Context context, String text) {
		initToast(context, text);
		toast.show();
	}

	/**
	 * 
	 * @param context
	 * @param resId
	 */
	public static void ToastLong(Context context, int resId) {
		initToast(context, resId);
		toast.setDuration(Toast.LENGTH_LONG);
		showToast(context);
	}

	/**
	 * 
	 * @param context
	 * @param text
	 */
	public static void ToastLong(Context context, String text) {
		initToast(context, text);
		toast.setDuration(Toast.LENGTH_LONG);
		showToast(context);
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
	private static void initToast(Context context, int resId) {
		initToast(context, context.getResources().getString(resId));
	}

	/**
	 * 
	 * @param context
	 * @param text
	 */
	private static void initToast(Context context, String text) {
		if (toast == null) {
			if (context != null) {
				toast = Toast.makeText(context, text, Toast.LENGTH_SHORT);
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
