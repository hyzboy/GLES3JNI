#ifndef GLES3JNI_GLCLASS_H
#define GLES3JNI_GLCLASS_H

#include <android/log.h>
#include <GLES3/gl32.h>

#define ENUM_CLASS_RNAGE(begin,end) BEGIN=begin,END=end,RANGE=END-BEGIN+1

class GLClass
{
    char log_tag[256];

public:

    GLClass(const char *tag);
    virtual ~GLClass()=default;

    template<typename ...ARGS> void out_verbose (ARGS...args){__android_log_print(ANDROID_LOG_VERBOSE,  log_tag,args...);}
    template<typename ...ARGS> void out_debug   (ARGS...args){__android_log_print(ANDROID_LOG_DEBUG,    log_tag,args...);}
    template<typename ...ARGS> void out_info    (ARGS...args){__android_log_print(ANDROID_LOG_INFO,     log_tag,args...);}
    template<typename ...ARGS> void out_warn    (ARGS...args){__android_log_print(ANDROID_LOG_WARN,     log_tag,args...);}
    template<typename ...ARGS> void out_error   (ARGS...args){__android_log_print(ANDROID_LOG_ERROR,    log_tag,args...);}
    template<typename ...ARGS> void out_fatal   (ARGS...args){__android_log_print(ANDROID_LOG_FATAL,    log_tag,args...);}

    void ClearGLError();
    bool GetGLError();
};//class GLClass
#endif //GLES3JNI_GLCLASS_H
