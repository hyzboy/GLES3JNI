#ifndef GLES3JNI_GLCLASS_H
#define GLES3JNI_GLCLASS_H

#include "Log.h"
#include <GLES3/gl32.h>

#define ENUM_CLASS_RNAGE(begin,end) BEGIN=begin,END=end,RANGE=END-BEGIN+1

class GLClass:public Log
{
public:

    GLClass(const char *tag):Log(tag){}
    virtual ~GLClass()=default;

    void ClearGLError();
    bool GetGLError();
};//class GLClass
#endif //GLES3JNI_GLCLASS_H
