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

Vector4f Light::GetDiffuse() const
{
    return m_DiffuseWriter->GetValue();
}

Vector4f Light::GetAmbient() const
{
    return m_AmbientWriter->GetValue();
}

Vector4f Light::GetSpecular() const
{
    return m_SpecularWriter->GetValue();
}