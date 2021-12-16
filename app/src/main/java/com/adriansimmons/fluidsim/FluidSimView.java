package com.adriansimmons.fluidsim;


import android.content.Context;
import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class FluidSimView extends GLSurfaceView{

    public FluidSimView(Context ctx){
        super(ctx);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        setEGLContextClientVersion(1);
        setRenderer(new Renderer());
    }

    private static class Renderer implements GLSurfaceView.Renderer {
        public void onDrawFrame(GL10 gl){ FluidSimNativeLib.step(); FluidSimNativeLib.display(); }
        public void onSurfaceChanged(GL10 gl, int w, int h){ FluidSimNativeLib.resize(w,h); }
        public void onSurfaceCreated(GL10 gl, EGLConfig cfg){ FluidSimNativeLib.init(4096); }
    }
}
