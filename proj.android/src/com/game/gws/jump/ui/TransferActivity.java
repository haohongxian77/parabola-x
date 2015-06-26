/*
 * @Title: TransferActivity.java 
 * @Package com.game.gws.jump.ui 
 * @Description:  
 * @author czj  
 * @date 2015年6月24日 下午9:57:34 
 * @version V1.0.0   
 */
package com.game.gws.jump.ui;

import java.util.Stack;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;

import com.facebook.appevents.AppEventsLogger;
import com.game.gws.jump.R;
import com.game.gws.jump.share.ClientType;
import com.game.gws.jump.share.ClientType.CurrentType;
import com.game.gws.jump.share.FaceBookClient;
import com.game.gws.jump.share.SinaClient;
import com.game.gws.jump.share.TencentClient;
import com.game.gws.jump.share.WxClient;
import com.game.gws.jump.system.MyApp;
import com.game.gws.jump.wxapi.WXManager;
import com.game.gws.jump.wxapi.WXManager.OnWxListener;
import com.sina.weibo.sdk.api.share.BaseResponse;
import com.sina.weibo.sdk.api.share.IWeiboHandler;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;

/**
 * @author czj
 * @Description:中间跳转承载的activity
 * @date 2015年6月24日 下午9:57:34
 */
public class TransferActivity extends Activity implements
		IWeiboHandler.Response, OnWxListener {
	public static final String TAG = TransferActivity.class.getSimpleName();
	private static Stack<TransferActivity> sActivities = new Stack<TransferActivity>();
	private boolean isTopActivity = true;

	public static void closeAct() {
		if (!sActivities.empty()) {
			Log.e(TAG, "closeAct");
			for (TransferActivity activity : sActivities) {
				if (activity != null && !activity.isFinishing())
					activity.finish();
			}
			sActivities.clear();
		}
	}

	public static void startAct() {
		Intent jumpIntent = new Intent(MyApp.getInstance()
				.getApplicationContext(), TransferActivity.class);
		jumpIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		MyApp.getInstance().startActivity(jumpIntent);
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.transfer);
		sActivities.push(this);
		SinaClient.getInstance().registerApp(this);
		TencentClient.getInstance().registerApp(this);
		WxClient.getInstance().registerApp(this);
		FaceBookClient.getInstance().registerApp(this);
		WXManager.getInstance().registerWxListener(this);
		switch (ClientType.getInstance().getCurType()) {
		case SINA:
			SinaClient.getInstance().shareImgAndContent(
					ClientType.getInstance().getStatus(),
					ClientType.getInstance().getFilePath());
			break;
		case TENCENT:
			TencentClient.getInstance().shareImg(
					ClientType.getInstance().getStatus(),
					ClientType.getInstance().getFilePath());
			break;
		case WX:
			WxClient.getInstance().shareImg(
					ClientType.getInstance().getStatus(),
					ClientType.getInstance().getFilePath());
			break;
		case FACEBOOK:
			FaceBookClient.getInstance().shareImg(
					ClientType.getInstance().getStatus(),
					ClientType.getInstance().getFilePath());
			break;
		default:
			closeAct();
			break;
		}
	}

	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
	}

	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
		isTopActivity = false;
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		/**
		 * facebook start
		 */
		// Logs 'install' and 'app activate' App Events.
		AppEventsLogger.activateApp(this);
		/**
		 * facebook end
		 */
		if (!isTopActivity) {
			closeAct();
		}
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		/**
		 * facebook start
		 */
		// Logs 'app deactivate' App Event.
		AppEventsLogger.deactivateApp(this);
		/**
		 * facebook end
		 */
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();

		WXManager.getInstance().unRegisterWxListener(this);
		isTopActivity = true;
	}

	@Override
	protected void onNewIntent(Intent intent) {
		// TODO Auto-generated method stub
		super.onNewIntent(intent);
		if (ClientType.getInstance().getCurType() == CurrentType.SINA) {
			SinaClient.getInstance().handleWeiboResponse(intent, this);
		}
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);
		switch (ClientType.getInstance().getCurType()) {
		case SINA:
			SinaClient.getInstance().onActivityResult(requestCode, resultCode,
					data);
			break;
		case WX:
			break;
		case FACEBOOK:
			FaceBookClient.getInstance().onActivityResult(requestCode,
					resultCode, data);
			break;
		case TENCENT:
			TencentClient.getInstance().onActivityResult(requestCode,
					resultCode, data);
			break;
		default:
			break;
		}
	}

	@Override
	public void onResp(BaseResp resp) {
		// TODO Auto-generated method stub
		WxClient.getInstance().handleResp(resp);
	}

	@Override
	public void onReq(BaseReq req) {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean shouldUnRegisterAfterResp() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void onResponse(BaseResponse arg0) {
		// TODO Auto-generated method stub
		if (ClientType.getInstance().getCurType() == CurrentType.SINA) {
			SinaClient.getInstance().onResponse(arg0);
		}
	}

}
