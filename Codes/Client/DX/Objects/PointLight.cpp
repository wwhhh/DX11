#include "PointLight.h"

PointLight::PointLight()
{
    m_PositionWriter = Parameters.SetVectorParameter(L"LightPosition", Vector4f(0.0f, 0.0f, 0.0f, 1.0f));

    PositionExtractorController<Entity3D>* pController = new PositionExtractorController<Entity3D>();
    pController->SetParameterWriter(m_PositionWriter);

    GetBody()->Controllers.Attach(pController);
}

PointLight::~PointLight()
{
}