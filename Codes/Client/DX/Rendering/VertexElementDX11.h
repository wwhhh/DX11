#pragma once

#include "PCH.h"
#include "Maths/Vector2f.h"
#include "Maths/Vector3f.h"
#include "Maths/Vector4f.h"

class VertexElementDX11
{

public:
    // Standard semantic names
    static std::string PositionSemantic;
    static std::string NormalSemantic;
    static std::string TexCoordSemantic;
    static std::string BoneIDSemantic;
	static std::string BoneWeightSemantic;
    static std::string TangentSemantic;

public:
	VertexElementDX11( int tuple, int elementCount );
	~VertexElementDX11( );
	
	int				SizeInBytes();
	int				Count();
	int				Tuple();

	void*			GetPtr( int i );

	float*			Get1f( int i );
	Vector2f*		Get2f( int i );
	Vector3f*		Get3f( int i );
	Vector4f*		Get4f( int i );

	int*			Get1i( int i );

	unsigned int*	Get1ui( int i );

	float*					operator[]( int i );
	const float*			operator[]( int i ) const;

	std::string						m_SemanticName;
	UINT							m_uiSemanticIndex;
	DXGI_FORMAT						m_Format;
	UINT							m_uiInputSlot;
	UINT							m_uiAlignedByteOffset;
	D3D11_INPUT_CLASSIFICATION		m_InputSlotClass;
	UINT							m_uiInstanceDataStepRate;

protected:
	VertexElementDX11();

	float*							m_pfData;
	int								m_iTuple;
	int								m_iCount;
};