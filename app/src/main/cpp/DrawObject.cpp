#include "DrawObject.h"
DrawObject::DrawObject(const char *tag):GLClass(tag)
{
    glGenVertexArrays(1,&vao);
}

DrawObject::~DrawObject()
{
    glDeleteVertexArrays(1,&vao);
}

void DrawObject::BindVAO()
{
    glBindVertexArray(vao);
}

void DrawObject::UnbindVAO()
{
    glBindVertexArray(0);
}

