#ifndef GLES3JNI_RENDERLAYOUT_H
#define GLES3JNI_RENDERLAYOUT_H

#include"GLFloatBuffer.h"
class RenderLayout:public GLFloatBuffer
{
public:

    RenderLayout()
    {
        Set(0,0,1,1);
    }

    /**
     * 设置布局<br>
     * 坐标使用左上角为0,0，右下角为1,1的数值范围。例如设置田字型格就是
     * 左坐标  上坐标   宽度     高度
     * 左上角格：   0.0     0.0     0.5     0.5
     * 左下角格：   0.0     0.5     0.5     0.5
     * 右上角格：   0.5     0.0     0.5     0.5
     * 右下角格：   0.5     0.5     0.5     0.5
     *
     * @param l     左坐标
     * @param t     上坐标
     * @param w     宽
     * @param h     高
     */
    void Set(float l,float t,float w,float h);
};//class RenderLayout
#endif //GLES3JNI_RENDERLAYOUT_H
