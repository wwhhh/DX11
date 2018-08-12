#pragma once

#include "Transform3D.h"
#include "IController.h"
#include "Rendering/ParameterContainer.h"
#include "Rendering/SceneRenderTask.h"

class Entity3D;

class Node3D
{
public:
	Node3D();
	~Node3D();

    void PreRender(RendererDX11* pRenderer, VIEWTYPE view);
    void Render(PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager, VIEWTYPE view);

	void Update( float time );
	void UpdateLocal( float time );
	void UpdateWorld( );

	void AttachChild( Entity3D* Child );
	void AttachChild( Node3D* Child );
	void DetachChild( Entity3D* Child );
	void DetachChild( Node3D* Child );

	void AttachParent( Node3D* Parent );
	void DetachParent( );
	Node3D* GetParent( );

	//Entity3D* GetChild( unsigned int index );

	std::wstring toString( );
	void SetName( const std::wstring& name );
	std::wstring GetName() const;

	const std::vector<Entity3D*>& Leafs();
	const std::vector<Node3D*>& Nodes();

	Transform3D Transform;
    ControllerPack<Node3D> Controllers;

protected:
	std::wstring m_Name;

	std::vector< Entity3D* > m_Leafs;
	std::vector< Node3D* > m_Nodes;

	Node3D* m_pParent;
};