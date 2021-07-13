#include "GLFloatBuffer.h"

GLFloatBuffer::GLFloatBuffer():GLClass("GLFloatBuffer")
{
    glGenBuffers(1,&buffer_id);

    buffer_size=0;
}

GLFloatBuffer::~GLFloatBuffer()
{
    glDeleteBuffers(1,&buffer_id);
}