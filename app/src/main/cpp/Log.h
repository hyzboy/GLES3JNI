//
// Created by huyingzhuo on 2021-10-29.
//

#ifndef GLES3JNI_LOG_H
#define GLES3JNI_LOG_H

#include <android/log.h>
#include <string.h>

constexpr size_t LOG_TAG_MAX_LENGTH=256;

class Log
{
    char log_tag[LOG_TAG_MAX_LENGTH];

public:

    const char *GetTag()const{return log_tag;}

public:

    Log(const char *name)
    {
        strcpy(log_tag,name);
    }

    virtual ~Log()=default;

public:

    template<typename ...ARGS> void out_debug   (ARGS...args){__android_log_print(ANDROID_LOG_DEBUG,    log_tag,args...);}
    template<typename ...ARGS> void out_info    (ARGS...args){__android_log_print(ANDROID_LOG_INFO,     log_tag,args...);}
    template<typename ...ARGS> void out_warn    (ARGS...args){__android_log_print(ANDROID_LOG_WARN,     log_tag,args...);}
    template<typename ...ARGS> void out_error   (ARGS...args){__android_log_print(ANDROID_LOG_ERROR,    log_tag,args...);}
    template<typename ...ARGS> void out_fatal   (ARGS...args){__android_log_print(ANDROID_LOG_FATAL,    log_tag,args...);}
};//class Log
#endif //GLES3JNI_LOG_H
