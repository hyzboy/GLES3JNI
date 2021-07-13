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

void GLFloatBuffer::BindToShader(int shader_location)
{
    Bind();
    glVertexAttribPointer(shader_location,2,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(shader_location);
}