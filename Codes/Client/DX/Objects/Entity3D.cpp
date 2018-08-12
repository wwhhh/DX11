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
	// ���ʵ�����и��ڵ�Ļ����ȸ��¸��ڵ�
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
    // ����ͼ�κͲ����Ƿ�Ϊ��
    if ((Visual.Executor != NULL) && (Visual.Material != NULL))
    {
        if (Visual.Material->Params[view].bRender)
        {
            // ���ò��ʵĲ������ⲽ����Ҫ��ʵ��ʹ����Ⱦ����֮ǰ���������ض���ʵ�����ʹ���ض��Ĳ���
            Visual.Material->SetRenderParams(pParamManager, view);
            // ����ʵ�����
            this->SetRenderParams(pParamManager);
        
            // ���ù��߻��� Material �е� render effect ��ʵ
            Visual.Material->Params[view].pEffect->ConfigurePipeline(pPipelineManager, pParamManager);
            pPipelineManager->ApplyPipelineResources();

            // ���ù��ߵ�����ͻ�������
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