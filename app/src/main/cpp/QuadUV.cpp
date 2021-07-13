#include "QuadUV.h"

namespace
{
    /*
    2--3
    |  |
    0--1
 */

    constexpr float QuadUVData[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f};
}

QuadUV::QuadUV()
{
    WriteData(QuadUVData,8);
}