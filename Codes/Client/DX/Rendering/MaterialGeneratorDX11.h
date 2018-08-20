#pragma once

#include "MaterialDX11.h"

// 材质生成类
class MaterialGeneratorDX11
{
public:
    static MaterialPtr GenerateBaseMaterial(RendererDX11& Renderer);
    static MaterialPtr GenerateModelMaterial(RendererDX11& Renderer);
    static MaterialPtr GeneratePhongMaterial(RendererDX11& Renderer);

private:
    MaterialGeneratorDX11();
};