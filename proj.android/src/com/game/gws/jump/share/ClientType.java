/*
 * @Title: ClientType.java 
 * @Package com.game.gws.jump.share 
 * @Description:  
 * @author czj  
 * @date 2015年6月18日 下午9:37:44 
 * @version V1.0.0   
 */
package com.game.gws.jump.share;

/**
 * @author czj
 * @Description:
 * @date 2015年6月18日 下午9:37:44
 */
public class ClientType {
	private static ClientType INSTANCE;
	private CurrentType curType = CurrentType.NONE;

	public CurrentType getCurType() {
		return curType;
	}

	public void setCurType(CurrentType curType) {
		this.curType = curType;
	}

	public enum CurrentType {
		SINA, TENCENT, WX, FACEBOOK, GOOGLE, NONE;
	}

	public ClientType() {
		super();
		// TODO Auto-generated constructor stub
	}

	public static ClientType getInstance() {
		if (null == INSTANCE) {
			INSTANCE = new ClientType();
		}
		return INSTANCE;
	}

}
