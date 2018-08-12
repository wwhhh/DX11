
// This file is a portion of the Hieroglyph 3 Rendering Engine.  It is distributed
// under the MIT License, available in the root of this distribution and 
// at the following URL:
#include "PCH.h"
#include "Entity3D.h"
#include "Utils/Log.h"
#include "RenderParameterDX11.h"
#include "IParameterManager.h"
#include "Node3D.h"

Entity3D::Entity3D() :
	m_pParent( nullptr ),
	m_Name( L"" ),
	//m_bHidden( false ),
	//m_bPickable( true ),
	m_pUserData( nullptr ),
    Controllers(this)
{
	//Sphere3f* pBoundingSphere = new Sphere3f();
	//pBoundingSphere->Center.MakeZero();
	//pBoundingSphere->Radius = 1.0f;
	//Shape.AddShape( pBoundingSphere );
}

Entity3D::~Entity3D()
{
}

//void Entity3D::SetHidden( bool bHide )
//{
//	m_bHidden = bHide;
//}

//bool Entity3D::IsHidden() const
//{
//	return( m_bHidden );
//}

//void Entity3D::SetPickable( bool bPickable )
//{
//	m_bPickable = bPickable;
//}

//bool Entity3D::IsPickable() const
//{
//	return( m_bPickable );
//}

Node3D* Entity3D::GetParent()
{
	return( m_pParent );
}

//Node3D* Entity3D::GetRoot( )
//{
//	if ( m_pParent )
//		return( m_pParent->GetRoot() );
//	else
//		return( nullptr ); // Not attached to a node!
//}

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
	// If the entity has a parent, then update its world matrix accordingly.

	if (m_pParent)
		Transform.UpdateWorld( m_pParent->Transform.WorldMatrix() );
	else
		Transform.UpdateWorld( );
}

//CompositeShape Entity3D::GetWorldBounds() const
//{
//	// Transform the bounding sphere and return it on the fly.  This is done to 
//	// eliminate a member variable (for the world bounding sphere), and to remove
//	// the calculation from the update phase if the world sphere isn't used.
//
//	Vector4f worldposition = Transform.WorldMatrix() * Vector4f( m_ModelBoundingSphere.Center, 1.0f );
//	return( Sphere3f( worldposition.xyz(), m_ModelBoundingSphere.Radius ) );
//}

//int Entity3D::GraphDepth( )
//{
//	if ( m_pParent == NULL )
//		return( 0 );
//	else
//		return( m_pParent->GraphDepth() + 1 );
//}

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

void Entity3D::SetUserData( void* pData )
{
	m_pUserData = pData;
}

void* Entity3D::GetUserData() const
{
	return( m_pUserData );
}

