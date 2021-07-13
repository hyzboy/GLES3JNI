#include "GLTexture.h"
#include<GLES3/gl32.h>

GLTexture::GLTexture(GLenum type):GLClass("GLTexture")
{
    texture_type=type;
    glGenTextures(1,&texture_id);

    glBindTexture(texture_type,texture_id);

    glTexParameteri(texture_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(texture_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(texture_type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(texture_type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    width=height=0;
    format=0;
}

GLTexture::~GLTexture()
{
    glDeleteTextures(1,&texture_id);
}

void GLTexture::Bind()
{
    glEnable(texture_type);
    glBindTexture(texture_type,texture_id);
}

void GLTexture::Bind(GLuint index)
{
    glActiveTexture(GL_TEXTURE0+index);
    Bind();
}

void GLTexture::Unbind(GLuint index)
{
    glActiveTexture(GL_TEXTURE0+index);
    glBindTexture(texture_type,0);
    glDisable(texture_type);
}

void GLTexture::SetBitmap(const GLenum vf,const void *data,const uint32_t w,const uint32_t h,const GLenum f,const GLenum t)
{
    if(!data)
        return;

    if(w==0||h==0)
        return;

    width=w;
    height=h;
    format=vf;

    Bind();
    glTexImage2D(texture_type,0,vf,width,height,0,f,t,data);
}