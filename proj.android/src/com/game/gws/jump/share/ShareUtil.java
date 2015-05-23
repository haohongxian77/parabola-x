/*
 * @Title: ShareUtil.java 
 * @Package com.game.gws.jump.share 
 * @Description:  
 * @author czj  
 * @date 2015年5月9日 下午12:23:06 
 * @version V1.0.0   
 */
package com.game.gws.jump.share;

import java.io.File;
import java.io.FileOutputStream;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Rect;
import android.os.Environment;
import android.view.Display;
import android.view.View;

/**
 * @author czj
 * @Description: 分享的工具类
 * @date 2015年5月9日 下午12:23:06
 */
public class ShareUtil {
	public enum ScreenShotType {
		/** 游戏开始时分享 **/
		GAME_SCREEN_SHOT,
		/** 游戏停止时分享 **/
		SCORE_SCREEN_SHOT;
	}

	private static final String SHOT_NAME_DIR = "game_shot_dir";
	/** 游戏开始时分享的文件名字 **/
	private static final String SHOT_NAME_GAME = "game_shot_name";
	/** 游戏停止时分享的文件名字 **/
	private static final String SHOT_NAME_SCORE = "game_shot_score";

	public static Bitmap getScreenShot(Activity activity) {
		// 获取windows中最顶层的view
		View view = activity.getWindow().getDecorView();
		view.buildDrawingCache();

		// 获取状态栏高度
		Rect rect = new Rect();
		view.getWindowVisibleDisplayFrame(rect);
		int statusBarHeights = rect.top;
		Display display = activity.getWindowManager().getDefaultDisplay();

		// 获取屏幕宽和高
		int widths = display.getWidth();
		int heights = display.getHeight();

		// 允许当前窗口保存缓存信息
		view.setDrawingCacheEnabled(true);

		// 去掉状态栏
		Bitmap bmp = Bitmap.createBitmap(view.getDrawingCache(), 0,
				statusBarHeights, widths, heights - statusBarHeights);

		// 销毁缓存信息
		view.destroyDrawingCache();

		return bmp;
	}

	/**
	 * 保存图片到sdcard
	 * 
	 * @param curType
	 * @param bmp
	 * @return
	 */
	public static boolean saveScreenShot(ScreenShotType curType, Bitmap bmp) {
		if (!android.os.Environment.getExternalStorageState().equals(
				android.os.Environment.MEDIA_MOUNTED)) {
			return false;
		}
		String dirStr = Environment.getExternalStorageDirectory()
				.getAbsolutePath() + File.separator + SHOT_NAME_DIR;
		File fileDir = new File(dirStr);
		try {
			if (!fileDir.exists()) {
				fileDir.createNewFile();
			}
			String fileName = "";
			if (curType == ScreenShotType.GAME_SCREEN_SHOT) {
				fileName = SHOT_NAME_GAME;
			} else {
				fileName = SHOT_NAME_SCORE;
			}
			File shotFile = new File(dirStr + File.separator + fileName);
			// 判断文件是否存在，不存在则创建
			if (!shotFile.exists()) {
				shotFile.createNewFile();
			}
			FileOutputStream fos = null;
			fos = new FileOutputStream(shotFile);
			if (fos != null) {
				// 第一参数是图片格式，第二个是图片质量，第三个是输出流
				bmp.compress(Bitmap.CompressFormat.PNG, 100, fos);
				// 用完关闭
				fos.flush();
				fos.close();
			}
			return true;
		} catch (Exception e) {
			// TODO: handle exception
			return false;
		}

	}

	/**
	 * 获取文件绝对路径
	 * 
	 * @param curShotType
	 * @return
	 */
	public static String getAbsPath(ScreenShotType curShotType) {
		if (!android.os.Environment.getExternalStorageState().equals(
				android.os.Environment.MEDIA_MOUNTED)) {
			return "";
		}
		String dirStr = Environment.getExternalStorageDirectory()
				.getAbsolutePath() + File.separator + SHOT_NAME_DIR;
		File fileDir = new File(dirStr);
		if (!fileDir.exists()) {
			return "";
		}
		if (curShotType == ScreenShotType.GAME_SCREEN_SHOT) {
			String path = dirStr + File.separator + SHOT_NAME_GAME;
			File file = new File(path);
			if (file.exists() && !file.isDirectory()) {
				return path;
			}

		} else {
			String path = dirStr + File.separator + SHOT_NAME_SCORE;
			File file = new File(path);
			if (file.exists() && !file.isDirectory()) {
				return path;
			}
		}
		return "";
	}
}
