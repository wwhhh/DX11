cbuffer Transforms
{
	matrix WorldViewProjMatrix;	
};

struct VS_INPUT
{
	float4 position : Position;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
};

VS_OUTPUT VSMain( in VS_INPUT v )
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	o.position = mul(v.position, WorldViewProjMatrix);

	return o;
}

float4 PSMain( in VS_OUTPUT input ) : SV_Target
{
	float4 rColor = 1.0f;
	return( rColor );
}