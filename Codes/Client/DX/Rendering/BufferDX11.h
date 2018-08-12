#pragma once

#include "ResourceDX11.h"

class BufferDX11 : public ResourceDX11
{
public:
    BufferDX11();
    virtual ~BufferDX11();

    D3D11_BUFFER_DESC			GetActualDescription();
    D3D11_BUFFER_DESC			GetDesiredDescription();
    void						SetDesiredDescription(D3D11_BUFFER_DESC desc);

    UINT						GetByteWidth();
    void						SetByteWidth(UINT width);

    D3D11_USAGE					GetUsage();
    void						SetUsage(D3D11_USAGE usage);

    UINT						GetBindFlags();
    void						SetBindFlags(UINT flags);

    UINT						GetCPUAccessFlags();
    void						SetCPUAccessFlags(UINT flags);

    UINT						GetMiscFlags();
    void						SetMiscFlags(UINT flags);

    UINT						GetStructureByteStride();
    void						SetStructureByteStride(UINT stride);

    void*						Map();
    void						UnMap();

    virtual ID3D11Resource*				GetResource();

    virtual UINT						GetEvictionPriority();
    virtual void						SetEvictionPriority(UINT EvictionPriority);

protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer>		m_pBuffer;
    D3D11_BUFFER_DESC							m_DesiredDesc;
    D3D11_BUFFER_DESC							m_ActualDesc;

};