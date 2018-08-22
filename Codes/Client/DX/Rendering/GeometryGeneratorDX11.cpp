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

void GeometryGeneratorDX11::GenerateAxisGeometry(GeometryPtr pGeometry)
{
    // The axis geometry requires to have at positions plus colors.

    VertexElementDX11* pPositions = new VertexElementDX11(3, 5 * 3);
    pPositions->m_SemanticName = "POSITION";
    pPositions->m_uiSemanticIndex = 0;
    pPositions->m_Format = DXGI_FORMAT_R32G32B32_FLOAT;
    pPositions->m_uiInputSlot = 0;
    pPositions->m_uiAlignedByteOffset = 0;
    pPositions->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    pPositions->m_uiInstanceDataStepRate = 0;

    VertexElementDX11* pColors = new VertexElementDX11(4, 5 * 3);
    pColors->m_SemanticName = "COLOR";
    pColors->m_uiSemanticIndex = 0;
    pColors->m_Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    pColors->m_uiInputSlot = 0;
    pColors->m_uiAlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
    pColors->m_InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    pColors->m_uiInstanceDataStepRate = 0;

    Vector3f* pPos = pPositions->Get3f(0);
    Vector4f* pCols = pColors->Get4f(0);

    float fThickness = 0.001f;
    float fLength = 10.0f;

    Vector4f XBase = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
    Vector4f XEnd = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
    Vector4f YBase = Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
    Vector4f YEnd = Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
    Vector4f ZBase = Vector4f(0.0f, 0.0f, 1.0f, 1.0f);
    Vector4f ZEnd = Vector4f(0.0f, 0.0f, 1.0f, 1.0f);


    // Create the X-Axis
    pPos[0] = Vector3f(0.0f, fThickness, fThickness);
    pCols[0] = XBase;
    pPos[1] = Vector3f(0.0f, -fThickness, fThickness);
    pCols[1] = XBase;
    pPos[2] = Vector3f(0.0f, -fThickness, -fThickness);
    pCols[2] = XBase;
    pPos[3] = Vector3f(0.0f, fThickness, -fThickness);
    pCols[3] = XBase;
    pPos[4] = Vector3f(fLength, 0.0f, 0.0f);
    pCols[4] = XEnd;

    // Next is the Y-Axis.
    pPos[5] = Vector3f(fThickness, 0.0f, fThickness);
    pCols[5] = YBase;
    pPos[6] = Vector3f(-fThickness, 0.0f, fThickness);
    pCols[6] = YBase;
    pPos[7] = Vector3f(-fThickness, 0.0f, -fThickness);
    pCols[7] = YBase;
    pPos[8] = Vector3f(fThickness, 0.0f, -fThickness);
    pCols[8] = YBase;
    pPos[9] = Vector3f(0.0f, fLength, 0.0f);
    pCols[9] = YEnd;

    // Next is the Z-Axis.
    pPos[10] = Vector3f(fThickness, fThickness, 0.0f);
    pCols[10] = ZBase;
    pPos[11] = Vector3f(-fThickness, fThickness, 0.0f);
    pCols[11] = ZBase;
    pPos[12] = Vector3f(-fThickness, -fThickness, 0.0f);
    pCols[12] = ZBase;
    pPos[13] = Vector3f(fThickness, -fThickness, 0.0f);
    pCols[13] = ZBase;
    pPos[14] = Vector3f(0.0f, 0.0f, fLength);
    pCols[14] = ZEnd;

    // Generate and add each line segment.
    TriangleIndices tri;

    tri.i1 = 0;
    tri.i2 = 1;
    tri.i3 = 4;
    pGeometry->AddFace(tri);

    tri.i1 = 1;
    tri.i2 = 2;
    tri.i3 = 4;
    pGeometry->AddFace(tri);

    tri.i1 = 2;
    tri.i2 = 3;
    tri.i3 = 4;
    pGeometry->AddFace(tri);

    tri.i1 = 3;
    tri.i2 = 0;
    tri.i3 = 4;
    pGeometry->AddFace(tri);


    tri.i1 = 5;
    tri.i2 = 6;
    tri.i3 = 9;
    pGeometry->AddFace(tri);

    tri.i1 = 6;
    tri.i2 = 7;
    tri.i3 = 9;
    pGeometry->AddFace(tri);

    tri.i1 = 7;
    tri.i2 = 8;
    tri.i3 = 9;
    pGeometry->AddFace(tri);

    tri.i1 = 8;
    tri.i2 = 5;
    tri.i3 = 9;
    pGeometry->AddFace(tri);


    tri.i1 = 10;
    tri.i2 = 11;
    tri.i3 = 14;
    pGeometry->AddFace(tri);

    tri.i1 = 11;
    tri.i2 = 12;
    tri.i3 = 14;
    pGeometry->AddFace(tri);

    tri.i1 = 12;
    tri.i2 = 13;
    tri.i3 = 14;
    pGeometry->AddFace(tri);

    tri.i1 = 13;
    tri.i2 = 10;
    tri.i3 = 14;
    pGeometry->AddFace(tri);

    // Add the vertex elements to the geometry object.
    pGeometry->AddElement(pPositions);
    pGeometry->AddElement(pColors);
}