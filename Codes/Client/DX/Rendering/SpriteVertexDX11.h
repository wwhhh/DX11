#pragma once

#include "PCH.h"
#include "Maths/Vector2f.h"
#include "Maths/Vector4f.h"
#include "Maths/Matrix4f.h"

class SpriteVertexDX11
{

public:
	SpriteVertexDX11();
	~SpriteVertexDX11();

	struct SpriteDrawRect
	{
		float X;
		float Y;
		float Width;
		float Height;
	};

	struct InstanceData
	{
		Matrix4f Transform;
		Vector4f Color;
		SpriteDrawRect DrawRect;
	};

	struct VertexData
	{
		Vector2f Position;
		Vector2f TexCoord;
	};

	static unsigned int GetElementCount();
	static D3D11_INPUT_ELEMENT_DESC Elements[8];
};