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

    void SetPosition(const Vector3f& vec);
    void SetColor(const Vector3f& vec);
    void SetDirection(const Vector3f& vec);
    void SetSpotAngles(const Vector2f& vec);
    void SetLightRange(const Vector3f& vec);

    Vector4f GetDiffuse() const;
    Vector4f GetAmbient() const;
    Vector4f GetSpecular() const;

    Vector4f GetPosition() const;
    Vector4f GetColor() const;
    Vector4f GetDirection() const;
    Vector4f GetSpotAngles() const;
    Vector4f GetLightRange() const;

    ParameterContainer Parameters;
protected:

    VectorParameterWriterDX11* m_DiffuseWriter;
    VectorParameterWriterDX11* m_AmbientWriter;
    VectorParameterWriterDX11* m_SpecularWriter;

    VectorParameterWriterDX11* m_PositionWriter;
    VectorParameterWriterDX11* m_ColorWriter;
    VectorParameterWriterDX11* m_DirectionWriter;
    VectorParameterWriterDX11* m_SpotAnglesWriter;
    VectorParameterWriterDX11* m_LightRangeWriter;
};