#include "ShaderModule.h"

ShaderModule::ShaderModule(const char *tag,int p,int vs,int fs):GLClass(tag)
{
    program=p;
    vertex_shader=vs;
    fragment_shader=fs;

    position_location=glGetAttribLocation(program,"position");
    texcoord_location=glGetAttribLocation(program,"texcoord");
    texture_location=glGetUniformLocation(program,"tex");
}

ShaderModule::~ShaderModule()
{
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
}

bool ShaderModule::Begin()
{
    ClearGLError();
    glUseProgram(program);

    glUniform1i(GetTextureLocation(),0);
    return GetGLError();
}

void ShaderModule::End()
{
    glUseProgram(0);
}