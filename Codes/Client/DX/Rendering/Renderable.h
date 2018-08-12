#pragma once

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
};