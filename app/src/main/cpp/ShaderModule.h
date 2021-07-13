#ifndef GLES3JNI_SHADERMODULE_H
#define GLES3JNI_SHADERMODULE_H

#include"GLClass.h"

class ShaderModule:public GLClass
{
protected:

    int program;
    int vertex_shader;
    int fragment_shader;

    int position_location;
    int texcoord_location;
    int texture_location;

public:

    const int GetPositionLocation()const{return position_location;}
    const int GetTexCoordLocation()const{return texcoord_location;}

    const int GetTextureLocation()const{return texture_location;}

public:

    ShaderModule(const char *tag,int p,int vs,int fs);
    virtual ~ShaderModule();

    bool Begin();
    void End();
};//class ShaderModule

enum class InlineShader
{
    SimpleTexture,             //简单贴图渲染

    ENUM_CLASS_RNAGE(SimpleTexture,SimpleTexture)
};//enum class InlineShader

bool InitShaderModule();
void CloseShaderModule();

ShaderModule *GetShaderModule(const InlineShader);           ///<创建一个Shader模块

#endif //GLES3JNI_SHADERMODULE_H
