#include "BufferConfigDX11.h"

BufferConfigDX11::BufferConfigDX11()
{
    SetDefaults();
}

BufferConfigDX11::~BufferConfigDX11()
{
}

void BufferConfigDX11::SetDefaults()
{
    m_State.ByteWidth = 1;
    m_State.Usage = D3D11_USAGE_DEFAULT;
    m_State.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    m_State.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    m_State.MiscFlags = 0;
    m_State.StructureByteStride = 0;
}

void BufferConfigDX11::SetDefaultConstantBuffer(UINT size, bool dynamic)
{
	m_State.ByteWidth = size;
    m_State.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    m_State.MiscFlags = 0;
    m_State.StructureByteStride = 0;

	if ( dynamic )
	{
		m_State.Usage = D3D11_USAGE_DYNAMIC;
		m_State.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		m_State.Usage = D3D11_USAGE_IMMUTABLE;
		m_State.CPUAccessFlags = 0;
	}
}

void BufferConfigDX11::SetDefaultVertexBuffer(UINT size, bool dynamic)
{
    m_State.ByteWidth = size;
    m_State.BindFlags = D3D11_BIND_INDEX_BUFFER;
    m_State.MiscFlags = 0;
    m_State.StructureByteStride = 0;

    if (dynamic)
    {
        m_State.Usage = D3D11_USAGE_DYNAMIC;
        m_State.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }
    else
    {
        m_State.Usage = D3D11_USAGE_IMMUTABLE;
        m_State.CPUAccessFlags = 0;
    }
}

void BufferConfigDX11::SetDefaultIndexBuffer(UINT size, bool dynamic)
{
    m_State.ByteWidth = size;
    m_State.BindFlags = D3D11_BIND_INDEX_BUFFER;
    m_State.MiscFlags = 0;
    m_State.StructureByteStride = 0;

    if (dynamic)
    {
        m_State.Usage = D3D11_USAGE_DYNAMIC;
        m_State.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }
    else
    {
        m_State.Usage = D3D11_USAGE_IMMUTABLE;
        m_State.CPUAccessFlags = 0;
    }
}

void BufferConfigDX11::SetDefaultStructuredBuffer(UINT size, UINT structsize)
{
    m_State.ByteWidth = size * structsize;
    m_State.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
    m_State.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    m_State.StructureByteStride = structsize;

    m_State.Usage = D3D11_USAGE_DEFAULT;
    m_State.CPUAccessFlags = 0;
}

void BufferConfigDX11::SetDefaultByteAddressBuffer(UINT size)
{
    m_State.ByteWidth = size;
    m_State.Usage = D3D11_USAGE_DEFAULT;
    m_State.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
    m_State.CPUAccessFlags = 0;
    m_State.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
    m_State.StructureByteStride = 0;
}

void BufferConfigDX11::SetDefaultIndirectArgsBuffer(UINT size)
{
    m_State.ByteWidth = size;
    m_State.Usage = D3D11_USAGE_DEFAULT;
    m_State.BindFlags = 0;
    m_State.CPUAccessFlags = 0;
    m_State.MiscFlags = D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS;
    m_State.StructureByteStride = 0;
}

void BufferConfigDX11::SetDefaultStagingBuffer(UINT size)
{
    m_State.ByteWidth = size;
    m_State.Usage = D3D11_USAGE_STAGING;
    m_State.BindFlags = 0;
    m_State.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    m_State.MiscFlags = 0;
    m_State.StructureByteStride = 0;
}

void BufferConfigDX11::SetByteWidth(UINT state)
{
    m_State.ByteWidth = state;
}

void BufferConfigDX11::SetUsage(D3D11_USAGE state)
{
    m_State.Usage = state;
}

void BufferConfigDX11::SetBindFlags(UINT state)
{
    m_State.BindFlags = state;
}

void BufferConfigDX11::SetCPUAccessFlags(UINT state)
{
    m_State.CPUAccessFlags = state;
}

void BufferConfigDX11::SetMiscFlags(UINT state)
{
    m_State.MiscFlags = state;
}

void BufferConfigDX11::SetStructureByteStride(UINT state)
{
    m_State.StructureByteStride = state;
}

D3D11_BUFFER_DESC BufferConfigDX11::GetBufferDesc()
{
    return(m_State);
}