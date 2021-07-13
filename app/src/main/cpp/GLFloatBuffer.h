#ifndef GLES3JNI_GLFLOATBUFFER_H
#define GLES3JNI_GLFLOATBUFFER_H

#include"GLClass.h"

class GLFloatBuffer:public GLClass
{
    GLuint buffer_id;
    uint32_t buffer_size;

public:

    GLFloatBuffer();
    virtual ~GLFloatBuffer();

    void Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER,buffer_id);
    }

    void WriteData(const float *data,const uint32_t count)
    {
        Bind();

        buffer_size=count*sizeof(float);

        glBufferData(GL_ARRAY_BUFFER,buffer_size,data,GL_STATIC_DRAW);
    }

    float *Map()
    {
        Bind();
        return (float *)glMapBufferRange(GL_ARRAY_BUFFER,0,buffer_size,GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    }

    void Unmap()
    {
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }
};//class GLFloatBuffer
#endif //GLES3JNI_GLFLOATBUFFER_H
