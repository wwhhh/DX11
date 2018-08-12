#pragma once

#include "PCH.h"
#include "Transform3D.h"
#include "IController.h"
#include "Rendering/RendererDX11.h"
#include "Rendering/ParameterContainer.h"
#include "Rendering/Renderable.h"
#include <string>
#include <vector>

class Node3D;

class Entity3D
{
public:
	Entity3D( );
	~Entity3D( );

	// 空间相关的数据和功能性质实现的地方

	void Update( float time );
	void UpdateLocal( float time );
	void UpdateWorld( );

    // 渲染相关的数据和功能
    //void SetRenderParams(IParameterManager* pParamManager);
    //void PreRender(RendererDX11* pRenderer, VIEWTYPE view);
    //void Render(PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager, VIEWTYPE view);

	std::wstring toString( );

	// Scene graph support is added by the following functions.  The graph is enforced
	// by allowing only a single parent, and only Entity3D will be leaf nodes.

	void AttachParent( Node3D* Parent );
	void DetachParent( );
	Node3D* GetParent( );

	void SetName( const std::wstring& name );
	std::wstring GetName() const;

	// Provide the ability for a user to add custom data to this entity.  There is no
	// usage of this pointer from within the entity - it is purely a convenience for
	// users.  This also means that the user has to ensure that the object pointed to
	// by pData must be properly managed (i.e. deleted or protected appropriately).

	void SetUserData( void* pData );
	void* GetUserData() const;

protected:

	Node3D* m_pParent;
	std::wstring m_Name;

public:
    Transform3D					Transform;
    ControllerPack<Entity3D>	Controllers;
    //Renderable					Visual;
	ParameterContainer			Parameters;

	void* m_pUserData;
};