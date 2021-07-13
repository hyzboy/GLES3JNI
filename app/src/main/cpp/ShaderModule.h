#ifndef GLES3JNI_SHADERMODULE_H
#define GLES3JNI_SHADERMODULE_H

#include"GLClass.h"

class ShaderModule:public GLClass
{
protected:

    int program;
    int vertex_shader;
    int fragment_shader;

public:

    const int GetPositionLocation()const{return 0;}
    const int GetTexCoordLocation()const{return 1;}

    const int GetTextureLocation()const{return 0;}

public:

    ShaderModule(const char *tag,int p,int vs,int fs):GLClass(tag)
    {
        program=p;
        vertex_shader=vs;
        fragment_shader=fs;
    }
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
