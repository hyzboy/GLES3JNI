//
// Created by HuYingzhuo on 2021-09-08.
//

#include <jni.h>
#include <sys/system_properties.h>
#include <libyuv.h>

extern int OpenSystemData(int length);
extern int CopyDataToSystem(char *source,int length);
extern int CloseSystemData();

namespace
{
    static int vc_width=0;
    static int vc_height=0;

    static int vc_yuv_bytes=0;
    static uint8_t *nv21_data=nullptr;
    static uint8_t *nv21_vu=nullptr;
}

extern "C"
{
    JNIEXPORT void JNICALL Java_com_android_vci_vci_init(JNIEnv* env, jobject obj,jint w,jint h)
    {
        vc_width=w;
        vc_height=h;

        vc_yuv_bytes=vc_width*vc_height*1.5;

        nv21_data=new uint8_t[vc_yuv_bytes];
        nv21_vu=nv21_data+w*h;

        OpenSystemData(vc_yuv_bytes);
        __system_property_set("opengl.run","1");
    }

    JNIEXPORT void JNICALL Java_com_android_vci_vci_copy(JNIEnv* env, jobject obj,jbyteArray data)
    {
        jboolean is_copy=false;

        uint8_t *ptr=(uint8_t *)(env->GetByteArrayElements(data,&is_copy));

        libyuv::ABGRToNV21(ptr,vc_width*4,
                           nv21_data,   vc_width,
                           nv21_vu,     vc_width,
                           vc_width,    vc_height);

        CopyDataToSystem((char *)ptr,vc_yuv_bytes);
    }

    JNIEXPORT void JNICALL Java_com_android_vci_vci_close(JNIEnv* env, jobject obj)
    {
        __system_property_set("opengl.run","0");
        CloseSystemData();
        delete[] nv21_data;
        nv21_data=nullptr;
        nv21_vu=nullptr;
    }
}