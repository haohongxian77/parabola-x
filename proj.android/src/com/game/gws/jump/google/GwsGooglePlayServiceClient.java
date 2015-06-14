/*
 * @Title: GooglePlayServiceClient.java 
 * @Package com.game.gws.jump.share 
 * @Description:  
 * @author czj  
 * @date 2015年4月19日 上午11:45:43 
 * @version V1.0.0   
 */
package com.game.gws.jump.google;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.game.gws.jump.R;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.GamesActivityResultCodes;
import com.google.android.gms.plus.Plus;
import com.google.example.games.basegameutils.BaseGameUtils;

/**
 * @author czj
 * @Description: 用于google游戏服务的事物管理
 * @date 2015年4月19日 上午11:45:43
 */
public class GwsGooglePlayServiceClient implements
		GoogleApiClient.ConnectionCallbacks,
		GoogleApiClient.OnConnectionFailedListener {
	public static final String TAG = GwsGooglePlayServiceClient.class
			.getSimpleName();
	private static GwsGooglePlayServiceClient INSTANCE;
	private GoogleApiClient mGoogleApiClient;
	private Activity mActivity;
	public static int SIGN_IN_REQ = 9001;
	public static int LEADERBOARDER_SHOW_REQ = 9002;
	private boolean mResolvingConnectionFailure = false;
	private boolean mAutoStartSignInflow = true;
	private boolean mSignInClicked = false;
	private int curScore;
	private static ConnectRequestType curRequestType = ConnectRequestType.CONNECT_REQUEST_NULL;

	public enum ConnectRequestType {
		CONNECT_REQUEST_NULL,
		/** 为提交分数而连接 **/
		CONNECT_REQUEST_SCORE_COMMIT,
		/** 为进入排行榜而连接 **/
		CONNECT_REQUEST_SCORE_BOARD;
	}

	public static GwsGooglePlayServiceClient getInstance() {
		if (INSTANCE == null) {
			INSTANCE = new GwsGooglePlayServiceClient();
		}
		return INSTANCE;
	}

	public GwsGooglePlayServiceClient() {
		super();
	}

	public void registerApp(Activity mActivity) {
		this.mActivity = mActivity;
		mGoogleApiClient = new GoogleApiClient.Builder(mActivity)
				.addConnectionCallbacks(this)
				.addOnConnectionFailedListener(this).addApi(Games.API)
				.addScope(Games.SCOPE_GAMES).addApi(Plus.API)
				.addScope(Plus.SCOPE_PLUS_LOGIN)
				// add other APIs and scopes here as needed
				.build();
	}

	public void connect() {
		Log.d(TAG,
				"connect :" + mGoogleApiClient + "/"
						+ !mGoogleApiClient.isConnected());
		if (null != mGoogleApiClient && !mGoogleApiClient.isConnected()) {
			mGoogleApiClient.connect();
		}
		// mActivity.runOnUiThread(new Runnable() {
		//
		// @Override
		// public void run() {
		// // TODO Auto-generated method stub
		// if (null != mGoogleApiClient && !mGoogleApiClient.isConnected()) {
		// mGoogleApiClient.connect();
		// }
		// }
		// });

	}

	public void disConnect() {
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if (null != mGoogleApiClient) {
					mGoogleApiClient.disconnect();
				}
			}
		});

	}

	public void commitScore(final int score) {
		Log.e(TAG, "commitScore" + score);
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if (null != mGoogleApiClient && mGoogleApiClient.isConnected()) {
					Log.e(TAG, "commitScore" + score + "/commit");
					Games.Leaderboards.submitScoreImmediate(
							mGoogleApiClient,
							mActivity.getApplicationContext().getString(
									R.string.leaderboard_worldrank), score);
					// return true;
				} else {
					Log.e(TAG, "commitScore" + score + "/connect");
					curScore = score;
					curRequestType = ConnectRequestType.CONNECT_REQUEST_SCORE_COMMIT;
					connect();
					// return false;
				}
			}
		});

	}

	public void showLeaderBoards() {
		Log.e(TAG, "showLeaderBoards------------");
		mActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if (null != mGoogleApiClient && mGoogleApiClient.isConnected()) {
					mActivity.startActivityForResult(
							Games.Leaderboards
									.getLeaderboardIntent(
											mGoogleApiClient,
											mActivity
													.getApplicationContext()
													.getResources()
													.getString(
															R.string.leaderboard_worldrank)),
							LEADERBOARDER_SHOW_REQ);
				} else {
					curRequestType = ConnectRequestType.CONNECT_REQUEST_SCORE_BOARD;
					connect();
				}
			}
		});
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == SIGN_IN_REQ) {
			mSignInClicked = false;
			mResolvingConnectionFailure = false;
			if (resultCode == Activity.RESULT_OK) {
				mGoogleApiClient.connect();
			} else {
				// Bring up an error dialog to alert the user that sign-in
				// failed. The R.string.signin_failure should reference an error
				// string in your strings.xml file that tells the user they
				// could not be signed in, such as "Unable to sign in."
				BaseGameUtils.showActivityResultError(mActivity, requestCode,
						resultCode, R.string.signin_other_error);
				mGoogleApiClient.disconnect();
				// ToastClient.getInstance().showToastShort(
				// R.string.signin_other_error);
			}
		} else if (resultCode == GamesActivityResultCodes.RESULT_RECONNECT_REQUIRED) {
			mGoogleApiClient.disconnect();
		}
	}

	@Override
	public void onConnectionFailed(ConnectionResult connectionResult) {
		// TODO Auto-generated method stub

		if (mResolvingConnectionFailure) {
			// already resolving
			return;
		}
		// if the sign-in button was clicked or if auto sign-in is enabled,
		// launch the sign-in flow
		if (mSignInClicked || mAutoStartSignInflow) {
			mAutoStartSignInflow = true;
			mSignInClicked = true;
			mResolvingConnectionFailure = true;

			// Attempt to resolve the connection failure using BaseGameUtils.
			// The R.string.signin_other_error value should reference a generic
			// error string in your strings.xml file, such as "There was
			// an issue with sign-in, please try again later."

			if (!BaseGameUtils.resolveConnectionFailure(
					mActivity,
					mGoogleApiClient,
					connectionResult,
					SIGN_IN_REQ,
					mActivity.getApplicationContext().getResources()
							.getString(R.string.signin_other_error))) {
				mResolvingConnectionFailure = false;
			}
		}

		// Put code here to display the sign-in button

	}

	@Override
	public void onConnected(Bundle arg0) {
		// TODO Auto-generated method stub
		if (curRequestType == ConnectRequestType.CONNECT_REQUEST_SCORE_BOARD) {
			showLeaderBoards();
		} else if (curRequestType == ConnectRequestType.CONNECT_REQUEST_SCORE_COMMIT) {
			commitScore(curScore);
		}
		curRequestType = ConnectRequestType.CONNECT_REQUEST_NULL;
	}

	@Override
	public void onConnectionSuspended(int arg0) {
		// TODO Auto-generated method stub

	}

}
