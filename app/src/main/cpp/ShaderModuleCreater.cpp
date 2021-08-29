#include"ShaderModule.h"
#include<cstring>

namespace
{
    int CompileShader(const GLenum type, const char *source)
    {
        int id = glCreateShader(type);

        if (id <= 0)
            return -1;

        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        GLint status;
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);

        if (status)
            return id;

        GLint length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        GLint char_writen;
        char *log = new char[length];
        glGetShaderInfoLog(id, length, &char_writen, log);

        __android_log_print(ANDROID_LOG_ERROR, "CompileShader", "shader compile error: %s", log);

        delete[] log;
        glDeleteShader(id);
        return (-2);
    }

    int CreateShaderProgram(const GLint vs,const GLint fs)
    {
        int program = glCreateProgram();

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        GLint linked;

        glGetProgramiv(program, GL_LINK_STATUS, &linked);

        if (linked)
            return program;

        GLint log_length, char_written;
        char *log;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

        log = new char[log_length];

        glGetProgramInfoLog(program, log_length, &char_written, log);

        __android_log_print(ANDROID_LOG_ERROR, "LinkProgram", "Shader program link error: %s", log);

        delete[] log;
        return(-1);
    }

    constexpr char common_vertes_shader_source[] = R"(#version 300 es

        layout(location=0) in vec2 position;
        layout(location=1) in vec2 texcoord;

        out vec2 fs_texcoord;

        void main()
        {
            fs_texcoord=texcoord;

            gl_Position=vec4(position,0.0,1.0);
        })";

    constexpr char draw_texture_fragment_shader_source[]=R"(#version 300 es

        precision highp float;
        layout(location=0) uniform highp sampler2D tex;

        in vec2 fs_texcoord;

        layout(location=0) out highp vec4 outColor;

        void main()
        {
            highp vec4 color=texture(tex,fs_texcoord);

            outColor=color;
        })";

    using ShaderModulePointer=ShaderModule *;

    static GLint common_vertex_shader=-1;
    static ShaderModulePointer shader_module_list[(size_t)InlineShader::RANGE];
}//namespace

bool InitShaderModule()
{
    if(common_vertex_shader<0)
        common_vertex_shader = CompileShader(GL_VERTEX_SHADER, common_vertes_shader_source);

    if(common_vertex_shader < 0)return false;

    memset(shader_module_list,0,sizeof(shader_module_list));

    return(true);
}

void CloseShaderModule()
{
    for(int i =(int)InlineShader::BEGIN;
            i<=(int)InlineShader::END;
            i++)
    {
        if(shader_module_list[i])
        {
            delete shader_module_list[i];
            shader_module_list[i] = nullptr;
        }
    }

    if(common_vertex_shader>=0)
    {
        glDeleteShader(common_vertex_shader);
        common_vertex_shader = -1;
    }
}

ShaderModule *GetShaderModule(const InlineShader is)
{
    if(common_vertex_shader < 0)return(nullptr);

    ShaderModule *sm=shader_module_list[(size_t)is];

    if(sm)
        return sm;

    int fs = CompileShader(GL_FRAGMENT_SHADER, draw_texture_fragment_shader_source);

    if(fs<0)
        return(nullptr);

    int program=CreateShaderProgram(common_vertex_shader,fs);

    if(program<0)
    {
        glDeleteShader(fs);
        return(nullptr);
    }

    shader_module_list[0]=new ShaderModule("ShaderModule",program,common_vertex_shader,fs);

    return shader_module_list[0];
}


