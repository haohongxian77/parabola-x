/*
 * @Title: ClientType.java 
 * @Package com.game.gws.jump.share 
 * @Description:  
 * @author czj  
 * @date 2015年6月18日 下午9:37:44 
 * @version V1.0.0   
 */
package com.ych.game.gws.jump.share;

import com.ych.game.gws.jump.ui.TransferActivity;

/**
 * @author czj
 * @Description:
 * @date 2015年6月18日 下午9:37:44
 */
public class ClientType {
	private static ClientType INSTANCE;
	private CurrentType curType = CurrentType.NONE;
	private int score;
	private int status;
	private String filePath;

	public int getScore() {
		return score;
	}

	public int getStatus() {
		return status;
	}

	public String getFilePath() {
		return filePath;
	}

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

	/**
	 * 
	 * @param type
	 * @param status
	 *            -1,本地图片;1,截屏
	 * @param filePath
	 */
	public void startShare(int type, int status, String filePath) {
		switch (type) {
		case 1:
			setCurType(CurrentType.SINA);
			break;
		case 2:
			setCurType(CurrentType.TENCENT);
			break;
		case 3:
			setCurType(CurrentType.WX);
			break;
		case 4:
			setCurType(CurrentType.FACEBOOK);
			break;
		default:
			setCurType(null);
			break;
		}
		if (null == getCurType()) {
			return;
		}

		this.status = status;
		this.filePath = filePath;
		TransferActivity.startAct();
	}

	public void commitScore(int score) {
		if (score <= 0) {
			return;
		}
		this.score = score;
		ClientType.getInstance().setCurType(CurrentType.GOOGLE);
		TransferActivity.startAct();
	}

	public void showLeaderBoards() {
		this.score = -1;
		ClientType.getInstance().setCurType(CurrentType.GOOGLE);
		TransferActivity.startAct();
	}

}
