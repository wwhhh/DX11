#pragma once

#include "GeometryDX11.h"

class GeometryGeneratorDX11
{
public:
    static void GenerateSphere(GeometryPtr pGeometry, unsigned int URes,
        unsigned int VRes, float Radius);

private:
    GeometryGeneratorDX11();
};
