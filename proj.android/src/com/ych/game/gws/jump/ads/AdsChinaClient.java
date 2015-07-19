/*
 * @Title: AdsClient.java 
 * @Package com.ych.game.gws.jump.ads 
 * @Description:  
 * @author czj  
 * @date 2015年7月6日 下午8:12:49 
 * @version V1.0.0   
 */
package com.ych.game.gws.jump.ads;

import android.app.Activity;
import android.util.Log;

import com.qq.e.ads.AdListener;
import com.qq.e.ads.AdRequest;
import com.qq.e.ads.AdSize;
import com.qq.e.ads.AdView;
import com.qq.e.ads.InterstitialAd;
import com.qq.e.ads.InterstitialAdListener;

/**
 * @author czj
 * @Description: 处理国内广告的client
 * @date 2015年7月6日 下午8:12:49
 */
public class AdsChinaClient {
	public static final String TAG = AdsChinaClient.class.getSimpleName();
	private Activity mActivity;
	private static AdsChinaClient INSTANCE;
	private AdView adView;
	/** 1104440171 **/
	private String appId = "1104440171";
	private InterstitialAd interstitialAd;
	private AdRequest adr;

	public static AdsChinaClient getInstance() {
		if (null == INSTANCE) {
			INSTANCE = new AdsChinaClient();
		}
		return INSTANCE;
	}

	public AdsChinaClient() {
		super();
		// TODO Auto-generated constructor stub
	}

	public void initWithActivityOnCreate(final Activity mActivity) {
		Log.e(TAG, "initWithActivityOnCreate");
		this.mActivity = mActivity;

		// TODO Auto-generated method stub
		adView = new AdView(mActivity, AdSize.BANNER, appId, "9080205459412342");
		// 广告请求数据，可以设置广告轮播时间，默认为30s
		adr = new AdRequest();
		// 设置广告刷新时间，为30~120之间的数字，单位为s,0标识不自动刷新
		adr.setRefresh(30);
		// 在banner广告上展示关闭按钮
		adr.setShowCloseBtn(true);

		adView.setAdListener(new AdListener() {

			// 加载广告失败时的回调
			public void onNoAd() {
				Log.e(TAG, "onNoAd");
			}

			// 加载广告失败时的回调
			public void onNoAd(int errorCode) {
				Log.e(TAG, "onNoAd:" + errorCode);
			}

			// 加载广告成功时的回调
			public void onAdReceiv() {
				Log.e(TAG, "onAdReceiv");
				adView.invalidate();
				adView.getParent().requestLayout();
			}

			// Banner关闭时的回调，仅在展示Banner关闭按钮时有效
			public void onBannerClosed() {
				Log.e(TAG, "onBannerClosed");
			}

			// Banner广告曝光时的回调
			public void onAdExposure() {
				Log.e(TAG, "onAdExposure");
			}

			// 当广告点击时调用
			public void onAdClicked() {
				Log.e(TAG, "onAdClicked");
			};
		});
	}

	/**
	 * 展示插屏广告
	 */
	private void showInterstialAd() {
		interstitialAd = new InterstitialAd(mActivity, appId,
				"4010709419016323");
		interstitialAd.setAdListener(new InterstitialAdListener() {
			public void onFail() {
				// 广告出错时的回调
				Log.e(TAG, "onFail");
			}

			public void onFail(int errorCode) {
				// 广告出错时的回调
				Log.e(TAG, "onFail:" + errorCode);
			}

			@Override
			public void onBack() {
				// 广告关闭时的回调
				Log.e(TAG, "onBack");
				interstitialAd.destory();
				interstitialAd.loadAd();
				interstitialAd.show();
			}

			@Override
			public void onAdReceive() {
				// 广告数据收到时的回调。在收到广告后可以调用 InterstitialAd.show 方法展示插屏
				Log.e(TAG, "onAdReceive");
				interstitialAd.show(mActivity);
				interstitialAd.destory();
			}

			public void onExposure() {
				// 广告曝光时的回调
				Log.e(TAG, "onExposure");
			}

			public void onClicked() {
				// 广告点击时的回调
				Log.e(TAG, "onClicked");
			}
		});
		interstitialAd.loadAd();
	}

	/**
	 * 设置adView是否可见
	 * 
	 * @param visibility
	 */
	public void setAdViewVisibility(final int visibility) {
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				adView.fetchAd(adr);
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
				showInterstialAd();
			}
		});
	}

	public AdView getAdView() {
		return adView;
	}

	public void onDestroy() {
		adView.destroy();
		interstitialAd.destory();
	}
}
