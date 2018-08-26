#include "Light.h"

Light::Light() :
    Parameters(),
    m_DiffuseWriter(nullptr),
    m_AmbientWriter(nullptr),
    m_SpecularWriter(nullptr)
{
    m_DiffuseWriter = Parameters.SetVectorParameter(L"Id", Vector4f(0.5f, 0.5f, 0.5f, 1.0f));
    m_AmbientWriter = Parameters.SetVectorParameter(L"Ia", Vector4f(0.01f, 0.01f, 0.01f, 1.0f));
    m_SpecularWriter = Parameters.SetVectorParameter(L"Is", Vector4f(1.0f, 1.0f, 1.0f, 1.0f));

    m_DiffuseWriter = Parameters.SetVectorParameter(L"LightPosition", Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
    m_AmbientWriter = Parameters.SetVectorParameter(L"LightColor", Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
    m_SpecularWriter = Parameters.SetVectorParameter(L"LightDirection", Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
    m_AmbientWriter = Parameters.SetVectorParameter(L"SpotlightAngles", Vector4f(30.0f, 60.0f, 1.0f, 1.0f));
    m_SpecularWriter = Parameters.SetVectorParameter(L"LightRange", Vector4f(10.0f, 10.0f, 10.0f, 1.0f));
}

Light::~Light()
{

}

void Light::SetAmbient(const Vector4f& color)
{
    m_AmbientWriter->SetValue(color);
}

void Light::SetDiffuse(const Vector4f& color)
{
    m_DiffuseWriter->SetValue(color);
}

void Light::SetSpecular(const Vector4f& color)
{
    m_SpecularWriter->SetValue(color);
}

void Light::SetPosition(const Vector3f& vec)
{
    m_PositionWriter->SetValue(Vector4f(vec, 1.0f));
}

void Light::SetColor(const Vector3f& vec)
{
    m_ColorWriter->SetValue(Vector4f(vec, 1.0f));
}

void Light::SetDirection(const Vector3f& vec)
{
    m_DirectionWriter->SetValue(Vector4f(vec, 1.0f));
}

void Light::SetSpotAngles(const Vector2f& vec)
{
    m_SpotAnglesWriter->SetValue(Vector4f(vec.x, vec.y, 1.0f, 1.0f));
}

void Light::SetLightRange(const Vector3f& vec)
{
    m_LightRangeWriter->SetValue(Vector4f(vec, 1.0f));
}


Vector4f Light::GetDiffuse() const { return m_DiffuseWriter->GetValue(); }
Vector4f Light::GetAmbient() const { return m_AmbientWriter->GetValue(); }
Vector4f Light::GetSpecular() const { return m_SpecularWriter->GetValue(); }

Vector4f Light::GetPosition() const { return m_PositionWriter->GetValue(); }
Vector4f Light::GetColor() const { return m_ColorWriter->GetValue(); }
Vector4f Light::GetDirection() const { return m_DirectionWriter->GetValue(); }
Vector4f Light::GetSpotAngles() const { return m_SpotAnglesWriter->GetValue(); }
Vector4f Light::GetLightRange() const { return m_LightRangeWriter->GetValue(); }