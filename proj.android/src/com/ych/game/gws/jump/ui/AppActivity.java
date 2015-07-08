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
package com.ych.game.gws.jump.ui;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.WindowManager;
import android.widget.RelativeLayout;
import android.widget.RelativeLayout.LayoutParams;

import com.facebook.appevents.AppEventsLogger;
import com.ych.game.gws.jump.ads.AdsChinaClient;
import com.ych.game.gws.jump.google.AdsClient;
import com.ych.game.gws.jump.google.GwsGooglePlayServiceClient;
import com.ych.game.gws.jump.share.ClientType;
import com.ych.game.gws.jump.share.ClientType.CurrentType;
import com.ych.game.gws.jump.share.ToastClient;
import com.ych.game.gws.jump.system.MyApp;

public class AppActivity extends Cocos2dxActivity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		ToastClient.getInstance().registerClient(this, MyApp.PACKAGE_NAME);
		GwsGooglePlayServiceClient.getInstance().registerApp(this);
		AdsClient.getInstance().initWithActivityOnCreate(this);
		AdsChinaClient.getInstance().initWithActivityOnCreate(this);
		RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(
				LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT);
		RelativeLayout containerView = new RelativeLayout(this);
		addContentView(containerView, lp);
		RelativeLayout.LayoutParams adLp = new RelativeLayout.LayoutParams(
				LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		adLp.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
		containerView.removeAllViews();
		containerView.addView(AdsChinaClient.getInstance().getAdView(), adLp);
		// getKeyHash();
	}

	// public void getKeyHash() {
	//
	// // Add code to print out the key hash
	// try {
	// PackageInfo info = this.getPackageManager().getPackageInfo(
	// "com.ych.game.gws.jump", // 替换成你游戏的包名
	// PackageManager.GET_SIGNATURES);
	// for (Signature signature : info.signatures) {
	// MessageDigest md = MessageDigest.getInstance("SHA");
	// md.update(signature.toByteArray());
	// Log.d("KeyHash:",
	// Base64.encodeToString(md.digest(), Base64.DEFAULT));
	// }
	// } catch (Exception e) {
	//
	// }
	// }

	@Override
	protected void onStart() {
		// TODO Auto-generated method stub
		super.onStart();
		// GwsGooglePlayServiceClient.getInstance().connect();
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
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		// TODO Auto-generated method stub
		super.onActivityResult(requestCode, resultCode, data);
		if (ClientType.getInstance().getCurType() == CurrentType.GOOGLE) {
			GwsGooglePlayServiceClient.getInstance().onActivityResult(
					requestCode, resultCode, data);
		}
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		AdsClient.getInstance().onDestroy();
		AdsChinaClient.getInstance().onDestroy();
		GwsGooglePlayServiceClient.getInstance().disConnect();
	}
}