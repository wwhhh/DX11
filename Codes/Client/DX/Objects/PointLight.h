#include "Light.h"
#include "PositionExtractorController.h"

class PointLight : public Light
{
public:
    PointLight();
    virtual ~PointLight();

protected:
    VectorParameterWriterDX11 * m_PositionWriter;
};