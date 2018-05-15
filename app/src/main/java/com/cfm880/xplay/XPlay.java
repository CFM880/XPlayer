package com.cfm880.xplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback{
    public XPlay(Context context) {
        super(context);
    }

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
    }
    @Override
    public void surfaceCreated(SurfaceHolder holder){
        // 与openegl通信
        initView(holder.getSurface());
    }



    public void surfaceChanged(SurfaceHolder holder, int format, int width,
                               int height){

    }

    public void surfaceDestroyed(SurfaceHolder holder){

    }


    private void initView(SurfaceHolder holder) {

    }

    public native void initView(Object surface);
}
