#include "GLClass.h"
#include<string.h>

GLClass::GLClass(const char *tag)
{
    strcpy(log_tag,tag);
}

void GLClass::ClearGLError()
{
    glGetError();
}

bool GLClass::GetGLError()
{
    int err=glGetError();

    if(err==GL_NO_ERROR)
        return(true);

    out_error("glError: %d",err);
    return(false);
}
