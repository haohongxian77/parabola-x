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
import android.view.WindowManager;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

import com.facebook.appevents.AppEventsLogger;
import com.game.gws.jump.google.AdsClient;
import com.game.gws.jump.google.GwsGooglePlayServiceClient;
import com.game.gws.jump.share.FaceBookClient;
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
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		SinaClient.getInstance().registerApp(this);
		TencentClient.getInstance().registerApp(this);
		WxClient.getInstance().registerApp(this);
		FaceBookClient.getInstance().registerApp(this);

		GwsGooglePlayServiceClient.getInstance().registerApp(this);
		AdsClient.getInstance().initWithActivityOnCreate(this);

		WXManager.getInstance().registerWxListener(this);
		RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(
				LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
		RelativeLayout containerView = new RelativeLayout(this);
		addContentView(containerView, lp);
		RelativeLayout.LayoutParams adLp = new RelativeLayout.LayoutParams(
				LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		adLp.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
		containerView.addView(AdsClient.getInstance().getAdView(), adLp);
	}

	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
		GwsGooglePlayServiceClient.getInstance().connect();
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
		AdsClient.getInstance().onResume();
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
		AdsClient.getInstance().onPause();

	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		AdsClient.getInstance().onDestroy();
		GwsGooglePlayServiceClient.getInstance().disConnect();
		WXManager.getInstance().unRegisterWxListener(this);
	}

	@Override
	protected void onNewIntent(Intent intent) {
		// TODO Auto-generated method stub
		super.onNewIntent(intent);
		SinaClient.getInstance().handleWeiboResponse(intent, this);
	}

	@Override
	public void onResponse(BaseResponse arg0) {
		// TODO Auto-generated method stub
		SinaClient.getInstance().onResponse(arg0);
	}

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);
		if (requestCode == GwsGooglePlayServiceClient.SIGN_IN_REQ
				|| requestCode == GwsGooglePlayServiceClient.LEADERBOARDER_SHOW_REQ) {
			GwsGooglePlayServiceClient.getInstance().onActivityResult(
					requestCode, resultCode, data);
		} else {
			TencentClient.getInstance().onActivityResult(requestCode,
					resultCode, data);
			FaceBookClient.getInstance().onActivityResult(requestCode,
					resultCode, data);
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

}
