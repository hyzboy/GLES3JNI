#ifndef GLES3JNI_DRAWOBJECT_H
#define GLES3JNI_DRAWOBJECT_H

#include"GLClass.h"
#include"QuadUV.h"
#include"RenderLayout.h"

class DrawObject:public GLClass
{
protected:

    QuadUV texture_uv;
    RenderLayout render_layout;

public:

    DrawObject(const char *tag):GLClass(tag){}
    virtual ~DrawObject()=default;

    void SetLayout(float l,float t,float w,float h){render_layout.Set(l,t,w,h);}

    virtual void Draw()=0;
};//class DrawObject
#endif //GLES3JNI_DRAWOBJECT_H
