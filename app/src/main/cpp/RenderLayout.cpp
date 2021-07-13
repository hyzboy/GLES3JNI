#include "RenderLayout.h"

void RenderLayout::Set(float l,float t,float w,float h)
{
    l *= 2;
    t *= 2;
    w *= 2;
    h *= 2;

    l -= 1;
    t -= 1;

    float b = -(t + h);
    float r = l + w;

    t *= -1;

    float vertices_data[8];

    vertices_data[0] = l;
    vertices_data[1] = b;
    vertices_data[2] = r;
    vertices_data[3] = b;
    vertices_data[4] = l;
    vertices_data[5] = t;
    vertices_data[6] = r;
    vertices_data[7] = t;

    WriteData(vertices_data,8);
}