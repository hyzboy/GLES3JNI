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

        libyuv::ARGBToNV21(ptr,vc_width*4,
                           nv21_data,   vc_width,
                           nv21_vu,     vc_width,
                           vc_width,    vc_height);

        CopyDataToSystem((char *)ptr,vc_yuv_bytes);
    }

    class TempBuffer
    {
        uint8_t *buffer;

    public:

        TempBuffer()
        {
            buffer=nullptr;
        }

        TempBuffer(uint8_t *buf)
        {
            buffer=buf;
        }

        TempBuffer(const size_t size)
        {
            buffer=new uint8_t[size];
        }

        ~TempBuffer()
        {
            delete[] buffer;        //"delete[] nullptr" isn't error
        }

        operator uint8_t *(){return buffer;}

        uint8_t * operator = (uint8_t *buf)
        {
            buffer=buf;
            return buffer;
        }

        uint8_t *alloc(const size_t size)
        {
            buffer=new uint8_t[size];
            return buffer;
        }
    };

    JNIEXPORT void JNICALL Java_com_android_vci_vci_ABGR2NV21(JNIEnv* env, jobject obj,
                                                              jbyteArray argb,jint argb_w,jint argb_h,
                                                              jbyteArray nv21,jint nv21_w,jint nv21_h,
                                                              jint ang)
    {
        jboolean is_copy=false;

        uint8_t *y_ptr=(uint8_t *)(env->GetByteArrayElements(nv21,&is_copy));
        uint8_t *vu_ptr=y_ptr+nv21_w*nv21_h;

        uint8_t *origin_ptr=(uint8_t *)(env->GetByteArrayElements(argb,&is_copy));
        TempBuffer argb_ptr;

        libyuv::RotationMode rotate;

        if(ang== 90)rotate=libyuv::kRotate90;else
        if(ang==180)rotate=libyuv::kRotate180;else
        if(ang==270)rotate=libyuv::kRotate270;else
                    rotate=libyuv::kRotate0;

        if(argb_w==nv21_w
         &&argb_h==nv21_h)
        {
            if(rotate!=libyuv::kRotate0)
            {
                argb_ptr.alloc(nv21_w*nv21_h*4);

                libyuv::ARGBRotate( origin_ptr, nv21_w*4,
                                    argb_ptr,   nv21_w*4,
                                    nv21_w,     nv21_h,
                                    rotate);
            }
            else
            {
                argb_ptr=origin_ptr;
            }
        }
        else
        {
            if(rotate!=libyuv::kRotate0)
            {
                TempBuffer scale_ptr(nv21_w*nv21_h*4);

                libyuv::ARGBScale(  origin_ptr, argb_w*4,   argb_w, argb_h,
                                    scale_ptr,  nv21_w*4,   nv21_w, nv21_h,
                                    libyuv::FilterMode::kFilterBox);

                argb_ptr.alloc(nv21_w*nv21_h*4);

                libyuv::ARGBRotate( scale_ptr,  nv21_w*4,
                                    argb_ptr,   nv21_w*4,
                                    nv21_w,     nv21_h,
                                    rotate);
            }
            else
            {
                argb_ptr.alloc(nv21_w*nv21_h*4);

                libyuv::ARGBScale(  origin_ptr,argb_w*4,   argb_w, argb_h,
                                    argb_ptr,  nv21_w*4,   nv21_w, nv21_h,
                                    libyuv::FilterMode::kFilterBox);
            }
        }

        libyuv::ABGRToNV21( argb_ptr,nv21_w*4,
                            y_ptr,   nv21_w,
                            vu_ptr,  nv21_w,
                            nv21_w,  nv21_h);
    }

    JNIEXPORT void JNICALL Java_com_android_vci_vci_close(JNIEnv* env, jobject obj)
    {
        __system_property_set("opengl.run","0");
        CloseSystemData();
    }
}
