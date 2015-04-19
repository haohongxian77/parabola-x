/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package com.game.gws.jump.ui;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Intent;
import android.os.Bundle;

import com.game.gws.jump.share.GwsGooglePlayServiceClient;
import com.game.gws.jump.share.SinaClient;
import com.game.gws.jump.share.TencentClient;
import com.game.gws.jump.share.WxClient;
import com.game.gws.jump.wxapi.WXManager;
import com.game.gws.jump.wxapi.WXManager.OnWxListener;
import com.sina.weibo.sdk.api.share.BaseResponse;
import com.sina.weibo.sdk.api.share.IWeiboHandler;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;

public class AppActivity extends Cocos2dxActivity implements
		IWeiboHandler.Response, OnWxListener {
	/**
	 * wx,需要确定包名和签名 facebook需要确定包名和签名（测试签名和正式签名）
	 */
	private SinaClient sinaClient;
	private TencentClient tencentClient;
	private WxClient wxClient;
	private GwsGooglePlayServiceClient psClient;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		sinaClient = new SinaClient(this);
		// if (null != savedInstanceState) {
		// sinaClient.handleWeiboResponse(getIntent(), this);
		// }
		tencentClient = new TencentClient(this);
		wxClient = new WxClient(this);
		psClient = new GwsGooglePlayServiceClient(this);
		WXManager.getInstance().registerWxListener(this);
	}

	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
		psClient.connect();
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		/**
		 * facebook start
		 */
		// Logs 'install' and 'app activate' App Events.
		// AppEventsLogger.activateApp(this);
		/**
		 * facebook end
		 */
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		/**
		 * facebook start
		 */
		// Logs 'app deactivate' App Event.
		// AppEventsLogger.deactivateApp(this);
		/**
		 * facebook end
		 */

	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		psClient.disConnect();
		WXManager.getInstance().unRegisterWxListener(this);
	}

	@Override
	protected void onNewIntent(Intent intent) {
		// TODO Auto-generated method stub
		super.onNewIntent(intent);
		sinaClient.handleWeiboResponse(intent, this);
	}

	@Override
	public void onResponse(BaseResponse arg0) {
		// TODO Auto-generated method stub
		sinaClient.onResponse(arg0);
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);
		if (requestCode == GwsGooglePlayServiceClient.SIGN_IN_REQ
				|| requestCode == GwsGooglePlayServiceClient.LEADERBOARDER_SHOW_REQ) {
			psClient.onActivityResult(requestCode, resultCode, data);
		} else {
			tencentClient.onActivityResult(requestCode, resultCode, data);
		}

	}

	@Override
	public void onResp(BaseResp resp) {
		// TODO Auto-generated method stub
		wxClient.handleResp(resp);
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

}
