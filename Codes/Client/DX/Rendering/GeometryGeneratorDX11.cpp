#include "GeometryGeneratorDX11.h"

GeometryGeneratorDX11::GeometryGeneratorDX11()
{
}

void GeometryGeneratorDX11::GenerateSphere(GeometryPtr pGeometry, unsigned int URes, unsigned int VRes, float Radius) 
{
    _ASSERT(VRes >= 3);
    _ASSERT(URes >= 4);
    _ASSERT(Radius > 0.0f);

    if (pGeometry == nullptr)
    {
        _ASSERT(pGeometry);
        return;
    }

    const unsigned int NumVertexRings = VRes - 2;
    const unsigned int NumVerts = NumVertexRings * URes + 2;
    const unsigned int NumTriangleRings = VRes - 1;
    const unsigned int NumTriangles = (NumTriangleRings + 1) * URes * 2;
    const unsigned int NumIndices = NumTriangles * 3;

    VertexElementDX11* pPositions = new VertexElementDX11(3, NumVerts);
    pPositions->m_SemanticName = "POSITION";
    pPositions->m_uiSemanticIndex = 0;
    pPositions->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
    pPositions->m_uiInputSlot = 0;
    pPositions->m_uiAlignedByteOffset = 0;
    pPositions->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    pPositions->m_uiInstanceDataStepRate = 0;

    // Calculate all of the vertex positions
    Vector3f* pVerts = pPositions->Get3f(0);
    int currVert = 0;

    // First vertex will be at the top pole
    pVerts[currVert++] = Vector3f(0.0f, Radius, 0.0f);

    // Add in the vertical rings of vertices
    for (unsigned int v = 1; v <= NumVertexRings; ++v)
    {
        for (unsigned int u = 0; u < URes; ++u)
        {
            float uAngle = u / static_cast<float>(URes) * 3.14159f * 2.0f;
            float vAngle = v / static_cast<float>(VRes - 1) * 3.14159f;

            float x = sinf(vAngle) * cosf(uAngle) * Radius;
            float y = cosf(vAngle) * Radius;
            float z = -sinf(vAngle) * sinf(uAngle) * Radius;
            pVerts[currVert++] = Vector3f(x, y, z);
        }
    }

    // Last vertex is the bottom pole
    pVerts[currVert++] = Vector3f(0.0f, -Radius, 0.0f);
    _ASSERT(currVert == NumVerts);

    pGeometry->AddElement(pPositions);

    // Now we'll add the triangles
    TriangleIndices face;

    // Top ring first
    for (unsigned int u = 0; u < URes; ++u)
    {
        const unsigned int currentU = u;
        const unsigned int nextU = (u + 1) % URes;
        face = TriangleIndices(0, u + 1, nextU + 1);
        pGeometry->AddFace(face);
    }

    // Now the middle rings
    for (unsigned int v = 1; v < VRes - 2; ++v)
    {
        const unsigned int top = 1 + ((v - 1) * URes);
        const unsigned int bottom = top + URes;
        for (unsigned int u = 0; u < URes; ++u)
        {
            const unsigned int currentU = u;
            const unsigned int nextU = (u + 1) % URes;
            const unsigned int currTop = top + currentU;
            const unsigned int nextTop = top + nextU;
            const unsigned int currBottom = bottom + currentU;
            const unsigned int nextBottom = bottom + nextU;

            _ASSERT(currTop <= NumVerts);
            _ASSERT(currBottom <= NumVerts);
            _ASSERT(nextBottom <= NumVerts);
            _ASSERT(nextTop <= NumVerts);


            face = TriangleIndices(currTop, currBottom, nextBottom);
            pGeometry->AddFace(face);

            face = TriangleIndices(nextBottom, nextTop, currTop);
            pGeometry->AddFace(face);
        }
    }

    // Now the bottom ring
    const unsigned int top = 1 + ((NumVertexRings - 1) * URes);
    const unsigned int bottom = NumVerts - 1;
    for (unsigned int u = 0; u < URes; ++u)
    {
        const unsigned int currentU = u;
        const unsigned int nextU = (u + 1) % URes;
        const unsigned int currTop = top + currentU;
        const unsigned int nextTop = top + nextU;

        _ASSERT(currTop <= NumVerts);
        _ASSERT(bottom <= NumVerts);
        _ASSERT(nextTop <= NumVerts);

        face = TriangleIndices(currTop, bottom, nextTop);
        pGeometry->AddFace(face);
    }
}