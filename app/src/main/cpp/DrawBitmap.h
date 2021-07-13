#ifndef GLES3JNI_DRAWBITMAP_H
#define GLES3JNI_DRAWBITMAP_H

#include"DrawObject.h"

class GLTexture;
class ShaderModule;

class DrawBitmap:public DrawObject
{
    GLTexture *texture;
    ShaderModule *shader;

    bool blend;

public:

    DrawBitmap(GLTexture *);

    void SetBlend(bool b){blend=b;}

    void Draw() override;
};
#endif //GLES3JNI_DRAWBITMAP_H
