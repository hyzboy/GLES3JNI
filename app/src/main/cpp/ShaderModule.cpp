#include "ShaderModule.h"

ShaderModule::~ShaderModule()
{
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
}

bool ShaderModule::Begin()
{
    ClearGLError();
    glUseProgram(program);
    return GetGLError();
}

void ShaderModule::End()
{
    glUseProgram(0);
}