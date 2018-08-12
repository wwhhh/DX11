#include "PCH.h"
#include "Entity3D.h"
#include "Utils/Log.h"
#include "RenderParameterDX11.h"
#include "IParameterManager.h"
#include "Node3D.h"

Entity3D::Entity3D() :
	m_pParent( nullptr ),
	m_Name( L"" ),
    Controllers(this)
{

}

Entity3D::~Entity3D()
{
}

Node3D* Entity3D::GetParent()
{
	return( m_pParent );
}

void Entity3D::AttachParent( Node3D* Parent )
{
	m_pParent = Parent;
}

void Entity3D::DetachParent( )
{
	m_pParent = nullptr;
}

void Entity3D::Update( float time )
{
	UpdateLocal( time );
	UpdateWorld( );
}

void Entity3D::UpdateLocal( float fTime )
{
    Controllers.Update(fTime);

	Transform.UpdateLocal();
}

void Entity3D::UpdateWorld( )
{
	// 如果实体类有父节点的话，先更新父节点
	if (m_pParent)
		Transform.UpdateWorld( m_pParent->Transform.WorldMatrix() );
	else
		Transform.UpdateWorld( );
}

void Entity3D::SetRenderParams(IParameterManager* pParamManager)
{
    pParamManager->SetWorldMatrixParameter(&Transform.WorldMatrix());
}

void Entity3D::PreRender(RendererDX11* pRenderer, VIEWTYPE view)
{
    if (Visual.Material != NULL)
        Visual.Material->PreRender(pRenderer, view);
}

void Entity3D::Render(PipelineManagerDX11* pPipelineManager, IParameterManager* pParamManager, VIEWTYPE view)
{
    // 测试图形和材质是否为空
    if ((Visual.Executor != NULL) && (Visual.Material != NULL))
    {
        if (Visual.Material->Params[view].bRender)
        {
            // 设置材质的参数。这步操作要在实体使用渲染参数之前，这样子特定的实体可以使用特定的参数
            Visual.Material->SetRenderParams(pParamManager, view);
            // 设置实体参数
            this->SetRenderParams(pParamManager);
        
            // 配置管线会让 Material 中的 render effect 落实
            Visual.Material->Params[view].pEffect->ConfigurePipeline(pPipelineManager, pParamManager);
            pPipelineManager->ApplyPipelineResources();

            // 配置管线的输入和绘制命令
            Visual.Executor->Execute(pPipelineManager, pParamManager);
        }
    }
}

std::wstring Entity3D::toString( )
{
	std::wstringstream objString;

	//for ( int i = 0; i < GraphDepth( this ); i++ )
	//{
	//	if ( i < GraphDepth( this ) - 1 )
	//		objString << L"| ";
	//	else
	//		objString << L"+-";
	//}

	objString << L"Entity3D ID:" << this << L", Name:" << GetName() << L"\n";

	return( objString.str() );
}


void Entity3D::SetName( const std::wstring& name )
{
	m_Name = name;
}

std::wstring Entity3D::GetName() const
{
	return( m_Name );
}