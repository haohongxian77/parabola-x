/*
 * @Title: WXEntryActivity.java 
 * @Package com.game.gws.jump.wxapi 
 * @Description:  
 * @author czj  
 * @date 2015年4月18日 下午1:42:02 
 * @version V1.0.0   
 */
package com.game.gws.jump.wxapi;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Window;

import com.game.gws.jump.share.WxClient;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;

/**
 * @author czj
 * @Description:所有微信的回调都会进这个activity
 * @date 2015年4月18日 下午1:42:02
 */
public class WXEntryActivity extends Activity implements IWXAPIEventHandler {
	private boolean isTopActivity = true;
	private WxClient wxClient;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		Intent intent = getIntent();
		Bundle bundle = null;
		if (intent != null) {
			bundle = intent.getExtras();
		}
		if (bundle == null) {
			return;
		}
		wxClient = new WxClient(this);
		wxClient.handleIntent(getIntent(), this);

	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		if (!isTopActivity) {
			finish();
		}
	}

	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
		isTopActivity = false;
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		isTopActivity = true;
		if (null != wxClient) {
			wxClient.unregisterApp();
		}
	}

	@Override
	protected void onNewIntent(Intent intent) {
		// TODO Auto-generated method stub
		super.onNewIntent(intent);
		setIntent(intent);
		Bundle bundle = null;
		if (intent != null) {
			bundle = intent.getExtras();
		}
		if (bundle == null) {
			return;
		}
		if (wxClient != null) {
			wxClient.handleIntent(intent, this);
		}
	}

	@Override
	public void onReq(BaseReq req) {
		// TODO Auto-generated method stub
		WXManager.getInstance().dispatchWxReq(req);
	}

	@Override
	public void onResp(BaseResp resp) {
		// TODO Auto-generated method stub
		WXManager.getInstance().dispatchWxResp(resp);
		finish();
	}

}
