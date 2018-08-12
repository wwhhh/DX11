#pragma once

#include "PCH.h"
#include "Maths/Vector3f.h"
#include "Maths/Vector4f.h"
#include "Maths/Matrix3f.h"
#include "Maths/Matrix4f.h"

class Transform3D
{
public:
	Transform3D( );
	~Transform3D( );

	Vector3f& Position( );
	Matrix3f& Rotation( );
	Vector3f& Scale( );

	void UpdateLocal( );
	void UpdateWorld( const Matrix4f& parent );
	void UpdateWorld( );

	const Matrix4f& LocalMatrix( ) const;
	const Matrix4f& WorldMatrix( ) const;
	Matrix4f& LocalMatrix( );
	Matrix4f& WorldMatrix( );

	Matrix4f GetView( ) const;

	Vector4f LocalToWorldSpace( const Vector4f& input );
	Vector4f WorldToLocalSpace( const Vector4f& input );
	Vector3f LocalVectorToWorldSpace( const Vector3f& input );
	Vector3f LocalPointToWorldSpace( const Vector3f& input );
	Vector3f WorldVectorToLocalSpace( const Vector3f& input );
	Vector3f WorldPointToLocalSpace( const Vector3f& input );

protected:

	Vector3f m_vTranslation;	// The translation and rotation varaibles are updated
	Matrix3f m_mRotation;		// during the update phase and used to generate the
	Vector3f m_vScale;			// local matrix.  Then, the world matrix is updated
	Matrix4f m_mWorld;			// with the new local matrix and the entity's parent
	Matrix4f m_mLocal;			// world matrix.

};