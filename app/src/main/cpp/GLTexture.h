#ifndef GLES3JNI_GLTEXTURE_H
#define GLES3JNI_GLTEXTURE_H

#include"GLClass.h"
class GLTexture:public GLClass
{
    GLenum texture_type;
    GLuint texture_id;

    uint32_t width,height;
    GLenum format;

public:

    GLTexture(GLenum type=GL_TEXTURE_2D);
    virtual ~GLTexture();

    const GLuint GetTextureID()const{return texture_id;}

    void Bind();
    void Bind(GLuint);
    void Unbind(GLuint);

    void SetBitmap(const GLenum vf,const void *data,const uint32_t w,const uint32_t h,const GLenum f,const GLenum t=GL_UNSIGNED_BYTE);

    void SetLum (const uint8_t *data,const uint32_t w,const uint32_t h){SetBitmap(GL_R8,    data,w,h,GL_RED,    GL_UNSIGNED_BYTE);}
    void SetRGB (const uint8_t *data,const uint32_t w,const uint32_t h){SetBitmap(GL_RGB8,  data,w,h,GL_RGB,    GL_UNSIGNED_BYTE);}
    void SetRGBA(const uint8_t *data,const uint32_t w,const uint32_t h){SetBitmap(GL_RGBA8, data,w,h,GL_RGBA,   GL_UNSIGNED_BYTE);}
};//class GLTexture
#endif //GLES3JNI_GLTEXTURE_H
