#include "ShaderModule.h"

ShaderModule::~ShaderModule()
{
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
}

bool ShaderModule::Begin()
{
    glUseProgram(program);
}

void ShaderModule::End()
{
    glUseProgram(0);
}