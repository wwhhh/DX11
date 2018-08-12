#pragma once

#include "RendererDX11.h"

class ResourceDX11
{
public:
    ResourceDX11();
    virtual ~ResourceDX11();

    virtual ResourceType        GetType() = 0;
    virtual ID3D11Resource*     GetResource() = 0;

    virtual UINT				GetEvictionPriority() = 0;
    virtual void				SetEvictionPriority(UINT EvictionPriority) = 0;

    unsigned short				GetInnerID();

    // 每个资源的 id
    unsigned short  			m_usInnerID;
    // 所有资源的 id 记录器
    static unsigned short		s_usResourceUID;
};