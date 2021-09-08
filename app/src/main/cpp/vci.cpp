//
// Created by HuYingzhuo on 2021-09-08.
//

#include <jni.h>

extern int OpenSystemData(int length);
extern int CopyDataToSystem(char *source,int length);
extern int CloseSystemData();

namespace
{
    static int vc_width=0;
    static int vc_height=0;

    static int vc_yuv_bytes=0;
}

extern "C"
{
    JNIEXPORT void JNICALL Java_com_android_vci_init(JNIEnv* env, jobject obj,jint w,jint h)
    {
        vc_width=w;
        vc_height=h;

        vc_yuv_bytes=vc_width*vc_height*1.5;

        OpenSystemData(vc_yuv_bytes);
    }

    JNIEXPORT void JNICALL Java_com_android_vci_copy(JNIEnv* env, jobject obj,jbyteArray data)
    {
        jboolean is_copy=false;

        char *ptr=(char*)(env->GetByteArrayElements(data,&is_copy));

        CopyDataToSystem(ptr,vc_yuv_bytes);
    }

    JNIEXPORT void JNICALL Java_com_android_vci_close(JNIEnv* env, jobject obj)
    {
        CloseSystemData();
    }
}