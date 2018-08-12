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
    void SetRenderParams(IParameterManager* pParamManager);
    void PreRender(RendererDX11* pRenderer, VIEWTYPE view);
    void Render(PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager, VIEWTYPE view);

	std::wstring toString( );

	// 加入了 Scene graph 技术.  强制只能含有一个父节点, 并且只有 Entity3D 可以成为叶子节点
	void AttachParent( Node3D* Parent );
	void DetachParent( );
	Node3D* GetParent( );

	void SetName( const std::wstring& name );
	std::wstring GetName() const;

protected:

	Node3D* m_pParent;
	std::wstring m_Name;

public:
    Transform3D					Transform;
    ControllerPack<Entity3D>	Controllers;
    Renderable					Visual;
	ParameterContainer			Parameters;
};