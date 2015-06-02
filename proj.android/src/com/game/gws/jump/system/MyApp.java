/*
 * @Title: MyApp.java 
 * @Package com.game.gws.jump.system 
 * @Description:  
 * @author czj  
 * @date 2015年4月18日 下午3:21:47 
 * @version V1.0.0   
 */
package com.game.gws.jump.system;

import android.app.Application;
import android.os.Handler;

/**
 * @author czj
 * @Description:
 * @date 2015年4月18日 下午3:21:47
 */
public class MyApp extends Application {
	private static MyApp INSTANCE;
	public static final String PACKAGE_NAME = "com.game.gws.jump";
	private Thread mUiThread;
	private Handler handler = new Handler();

	public static MyApp getInstance() {
		return INSTANCE;
	}

	public MyApp() {
		super();
		INSTANCE = this;
	}

	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		mUiThread = Thread.currentThread();
	}

	public final void runOnUiThread(Runnable action) {
		if (Thread.currentThread() != mUiThread) {
			handler.post(action);
		} else {
			action.run();
		}
	}

}
