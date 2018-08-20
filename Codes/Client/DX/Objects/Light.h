#pragma once

#include "Actor.h"
#include "Rendering/ParameterContainer.h"

class Light : public Actor
{
public:
    Light();
    virtual ~Light();

    void SetAmbient(const Vector4f& color);
    void SetDiffuse(const Vector4f& color);
    void SetSpecular(const Vector4f& color);

    Vector4f GetDiffuse() const;
    Vector4f GetAmbient() const;
    Vector4f GetSpecular() const;

    ParameterContainer Parameters;
protected:

    VectorParameterWriterDX11* m_DiffuseWriter;
    VectorParameterWriterDX11* m_AmbientWriter;
    VectorParameterWriterDX11* m_SpecularWriter;
    VectorParameterWriterDX11* m_PositionWriter;
};