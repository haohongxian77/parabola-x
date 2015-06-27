/*
 * @Title: AdsClient.java 
 * @Package com.game.gws.jump.google 
 * @Description:  
 * @author czj  
 * @date 2015年5月17日 下午2:12:33 
 * @version V1.0.0   
 */
package com.game.gws.jump.google;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import android.app.Activity;
import android.provider.Settings;
import android.util.Log;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

/**
 * @author czj
 * @Description: 广告的逻辑处理
 * @date 2015年5月17日 下午2:12:33
 */
public class AdsClient {
	public static final String TAG = AdsClient.class.getSimpleName();
	private Activity mActivity;
	private static AdsClient INSTANCE;
	/** 广告条 **/
	private AdView adView;
	/** 插页广告 **/
	private InterstitialAd interstitial;
	private static final String AD_BANNER_00 = "ca-app-pub-7081761992709780/6152533754";
	private static final String AD_INSERT_00 = "ca-app-pub-7081761992709780/8315533757";

	public static AdsClient getInstance() {
		if (null == INSTANCE) {
			INSTANCE = new AdsClient();
		}
		return INSTANCE;
	}

	public AdsClient() {
		super();
		// TODO Auto-generated constructor stub
	}

	public void initWithActivityOnCreate(Activity mActivity) {
		this.mActivity = mActivity;
		adView = new AdView(mActivity);
		adView.setAdUnitId(AD_BANNER_00);
		adView.setAdSize(com.google.android.gms.ads.AdSize.SMART_BANNER);

		AdRequest adRequest = new AdRequest.Builder().addTestDevice(
				getDeviceId()).build();
		adView.loadAd(adRequest);
		adView.setAdListener(new AdListener() {
			@Override
			public void onAdLoaded() {
				// TODO Auto-generated method stub
				super.onAdLoaded();
				Log.e(TAG, "onAdLoaded");
				if (null != adView.getParent()) {
					adView.getParent().requestLayout();
				}

			}

			@Override
			public void onAdFailedToLoad(int errorCode) {
				// TODO Auto-generated method stub
				super.onAdFailedToLoad(errorCode);
				Log.e(TAG, "onAdFailedToLoad:" + errorCode);
			}
		});
		interstitial = new InterstitialAd(mActivity);
		interstitial.setAdUnitId(AD_INSERT_00);
		interstitial.loadAd(new AdRequest.Builder()
				.addTestDevice(getDeviceId()).build());
		interstitial.setAdListener(new AdListener() {
			@Override
			public void onAdLoaded() {
				// TODO Auto-generated method stub
				super.onAdLoaded();
			}

			@Override
			public void onAdClosed() {
				// TODO Auto-generated method stub
				super.onAdClosed();
				interstitial.loadAd(new AdRequest.Builder().addTestDevice(
						getDeviceId()).build());
			}
		});
	}

	/**
	 * 展示插页广告
	 */
	public void showInsertAd() {
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				Log.e(TAG, "interstitial.isLoaded():" + interstitial.isLoaded());
				if (interstitial.isLoaded()) {
					interstitial.show();
				}
			}
		});

	}

	public AdView getAdView() {
		return adView;
	}

	public void onPause() {
		adView.pause();
	}

	public void onResume() {
		adView.resume();
	}

	public void onDestroy() {
		adView.destroy();
	}

	public String getDeviceId() {
		String android_id = Settings.Secure.getString(
				mActivity.getContentResolver(), Settings.Secure.ANDROID_ID);
		String deviceId = md5(android_id).toUpperCase();
		return deviceId;
	}

	public static final String md5(final String s) {
		try {
			// Create MD5 Hash
			MessageDigest digest = java.security.MessageDigest
					.getInstance("MD5");
			digest.update(s.getBytes());
			byte messageDigest[] = digest.digest();

			// Create Hex String
			StringBuffer hexString = new StringBuffer();
			for (int i = 0; i < messageDigest.length; i++) {
				String h = Integer.toHexString(0xFF & messageDigest[i]);
				while (h.length() < 2)
					h = "0" + h;
				hexString.append(h);
			}
			return hexString.toString();

		} catch (NoSuchAlgorithmException e) {
			Log.e(TAG, e.getMessage());
		}
		return "";
	}

}
