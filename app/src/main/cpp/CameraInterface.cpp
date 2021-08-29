#include "CameraInterface.h"
#include <sys/system_properties.h>
#include <string.h>
#include "GLTexture.h"

#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include <dlfcn.h>

namespace
{
    template<typename T>
    T *new_zero(const uint32_t count)
    {
        T *mem=new T[count];

        if(!mem)
            return(nullptr);

        memset(mem,0,count*sizeof(T));

        return mem;
    }

    struct HALSwapBuffer
    {
        uint32_t width,height;

        uint32_t y_bytes;
        uint32_t uv_bytes;
        uint32_t yuv_bytes;
        GLsizei rgba_bytes;

        uint8_t *from_hal;          //来自HAL层的数据
        uint8_t *to_hal;            //给HAL层的数据

        uint8_t *rgba;              //中间RGBA数据

    public:

        HALSwapBuffer(const uint32_t w,const uint32_t h)
        {
            width=w;
            height=h;

            y_bytes=w*h;
            uv_bytes=y_bytes>>2;
            yuv_bytes= y_bytes + uv_bytes + uv_bytes;
            rgba_bytes=y_bytes<<2;

            from_hal=new_zero<uint8_t>(yuv_bytes);
            to_hal=new_zero<uint8_t>(yuv_bytes);
            rgba=new_zero<uint8_t>(rgba_bytes);
        }

        ~HALSwapBuffer()
        {
            delete[] rgba;
            delete[] from_hal;
            delete[] to_hal;
        }
    };

    static HALSwapBuffer *swap_buffer=nullptr;
};

extern int OpenSystemData(int length);
extern int CopyDataToSystem(char *source,int length);
extern int CloseSystemData();

void CreateTestImage()
{
    uint8_t *p=swap_buffer->from_hal;

    for(uint32_t row=0;row<swap_buffer->height;row++)
    {
        for(uint32_t col=0;col<swap_buffer->width;col++)
        {
            *p=((row&1)^(col&1))?255:0;
            ++p;
        }
    }
}

void StartVirtualCameraInterface()
{
    swap_buffer=new HALSwapBuffer(1280,720);        //假设虚拟摄像头尺寸是1280x720

    CreateTestImage();

    OpenSystemData(swap_buffer->yuv_bytes);

    __system_property_set("opengl.run","1");
}

void StopVirtualCameraInterface()
{
    CloseSystemData();
    __system_property_set("opengl.run","0");
}

void GetVirtualCameraSize(uint32_t &w,uint32_t &h)
{
    w=swap_buffer->width;
    h=swap_buffer->height;
}

bool VirtualCamera2Texture(GLTexture *texture)
{
    if(!swap_buffer)
        return(false);

    if(!texture)
        return(false);

    texture->SetLum(swap_buffer->from_hal,swap_buffer->width,swap_buffer->height);
    return(true);
}

void RGBA2YUV()
{
    //为测试，这里将红色元素直接当Y写入,UV不管

    uint8_t *t=swap_buffer->to_hal;
    uint8_t *s=swap_buffer->rgba;

    for(uint32_t i=0;i<swap_buffer->y_bytes;i++)
    {
        *t=*s;
        ++t;
        s+=4;
    }
}

void SaveToQData()
{
    int fp=open("/dev/qdata",O_WRONLY);

    if(fp==-1)return;

    write(fp,swap_buffer->to_hal,swap_buffer->yuv_bytes);

    close(fp);
}

bool Texture2VirtualCamera()
{
    if(!swap_buffer)
        return(false);

    glReadnPixels(0,0,swap_buffer->width,swap_buffer->height,GL_RGBA,GL_UNSIGNED_BYTE,swap_buffer->rgba_bytes,(void *)(swap_buffer->rgba));

    RGBA2YUV();

    //SaveToQData();
    CopyDataToSystem((char *)(swap_buffer->to_hal),swap_buffer->yuv_bytes);

    return(true);
}