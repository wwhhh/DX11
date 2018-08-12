#pragma once

#include "MaterialDX11.h"
#include "PipelineExecutorDX11.h"

class Renderable {
public:
    enum ENTITYTYPE
    {
        ALPHA,
        SKY,
        BACKGROUND,
        GEOMETRY,
        NUMPASSES
    };

    Renderable();
    ~Renderable();

    void SetMaterial(MaterialPtr pMaterial);
    MaterialPtr GetMaterial();

    void SetGeometry(ExecutorPtr pExecutor);
    ExecutorPtr GetGeometry();


    ENTITYTYPE				iPass;
    ExecutorPtr				Executor;
    MaterialPtr				Material;
};