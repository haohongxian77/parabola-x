/*
 * @Title: WXManager.java 
 * @Package com.game.gws.jump.wxapi 
 * @Description:  
 * @author czj  
 * @date 2015年4月18日 下午3:16:24 
 * @version V1.0.0   
 */
package com.game.gws.jump.wxapi;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import com.game.gws.jump.system.MyApp;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;

/**
 * @author czj
 * @Description: 添加观察者模式，进行微信消息的分发
 * @date 2015年4月18日 下午3:16:24
 */
public class WXManager {

	private ArrayList<OnWxListener> mOnWxListenerList;

	public interface OnWxListener {
		/**
		 * 搜狐视频向微信发送请求，微信的响应将回调这里
		 */
		public void onResp(BaseResp resp);

		/**
		 * 微信向搜狐视频发送的请求将调用这里
		 */
		public void onReq(BaseReq req);

		/**
		 * 是否要在onResp之后UnRegister
		 * 
		 * @return
		 */
		public boolean shouldUnRegisterAfterResp();
	};

	private static WXManager INSTANCE;

	private WXManager() {

	}

	public synchronized static WXManager getInstance() {
		if (INSTANCE == null) {
			INSTANCE = new WXManager();
		}
		return INSTANCE;
	}

	/**
	 * 增加观察者
	 * 
	 * @param listener
	 */
	public synchronized void registerWxListener(OnWxListener listener) {
		if (mOnWxListenerList == null) {
			mOnWxListenerList = new ArrayList<OnWxListener>();
		}

		mOnWxListenerList.add(listener);
	}

	/**
	 * 删除观察者
	 * 
	 * @param listener
	 */
	public synchronized void unRegisterWxListener(OnWxListener listener) {
		if (listener == null || isEmpty(mOnWxListenerList)) {
			return;
		}

		mOnWxListenerList.remove(listener);
	}

	/**
	 * 分发微信对搜狐视频客户端的请求
	 * 
	 * @param user
	 */
	public void dispatchWxReq(final BaseReq req) {
		if (isEmpty(mOnWxListenerList)) {
			return;
		}

		MyApp.getInstance().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				for (OnWxListener listener : mOnWxListenerList) {
					if (listener != null) {
						listener.onReq(req);
					}
				}
			}
		});
	}

	/**
	 * 分发微信对搜狐视频客户端请求的回应
	 * 
	 * @param user
	 */
	public void dispatchWxResp(final BaseResp resp) {
		if (isEmpty(mOnWxListenerList)) {
			return;
		}

		MyApp.getInstance().runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Iterator<OnWxListener> it = mOnWxListenerList.iterator();
				while (it.hasNext()) {
					OnWxListener listener = it.next();
					if (listener != null) {
						listener.onResp(resp);
						if (listener.shouldUnRegisterAfterResp()) {
							it.remove();
						}
					}
				}
			}
		});
	}

	private <V> boolean isEmpty(List<V> sourceList) {
		return (sourceList == null || sourceList.isEmpty());
	}
}
