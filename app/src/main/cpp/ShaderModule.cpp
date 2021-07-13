#include "ShaderModule.h"

ShaderModule::~ShaderModule()
{
    glDeleteShader(fragment_shader);
    glDeleteProgram(program);
}
