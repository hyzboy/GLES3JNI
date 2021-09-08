package com.android.vci;

public class vci
{
    static {
        System.loadLibrary("vci");
    }

    public static native void init(int width,int height);
    public static native void copy(byte[] data);
    public static native void close();
}
