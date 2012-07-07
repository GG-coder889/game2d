package org.game2d;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;

public class GameActivity extends Cocos2dxActivity {
	/** Called when the activity is first created. */
	private Cocos2dxGLSurfaceView mGLView;

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		String packageName = getApplication().getPackageName();
		super.setPackageName(packageName);
		mGLView = new Cocos2dxGLSurfaceView(this);
		setContentView(mGLView);
	}

	@Override
	protected void onPause() {
		super.onPause();
		mGLView.onPause();
	}

	@Override
	protected void onResume() {
		super.onResume();
		mGLView.onResume();
	}

	static {
		System.loadLibrary("jsengine");
	}
}