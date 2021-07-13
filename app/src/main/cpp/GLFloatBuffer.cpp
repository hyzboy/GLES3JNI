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

void GLFloatBuffer::BindToShader(int sampler_location)
{
    Bind();
    glVertexAttribPointer(sampler_location,2,GL_FLOAT,false,0,0);
    glEnableVertexAttribArray(sampler_location);
}