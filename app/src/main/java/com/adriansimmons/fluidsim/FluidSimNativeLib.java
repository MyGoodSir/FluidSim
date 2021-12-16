package com.adriansimmons.fluidsim;

public class FluidSimNativeLib {
    static {
        System.loadLibrary("fluidsim");
    }

    public static native void init(int num_particles);
    public static native void resize(int width, int height);
    public static native void step();
    public static native void display();
    public static native void rotate(float theta);
}
