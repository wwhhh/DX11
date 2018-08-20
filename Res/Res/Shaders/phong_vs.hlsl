cbuffer WorldTransforms
{
	matrix WorldMatrix;
	matrix WorldViewProjMatrix;	
};

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float4 texcoord : TEXCOORDS;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float4 worldPos : POSITION;
	float3 normal   : NORMAL;
	float4 texcoord : TEXCOORDS;
};

VS_OUTPUT VSMain( in VS_INPUT input )
{
	VS_OUTPUT output;
	
	float3 NormalWS = mul( input.normal, (float3x3)WorldMatrix );
	output.normal = NormalWS;
	output.position = mul( float4( input.position, 1.0f ), WorldViewProjMatrix );
	output.texcoord = input.texcoord;
	
	return output;
}
