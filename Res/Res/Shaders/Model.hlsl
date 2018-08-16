cbuffer WorldAndClipTransforms
{
	matrix WorldMatrix;
	matrix WorldViewProjMatrix;
};

Texture2D       ModelTexture : register( t0 );
SamplerState	ModelSampler : register( s0 ); 

struct VS_INPUT
{
	float3 position 		: POSITION;
	float3 normal			: NORMAL;
	float3 texcoord			: TEXCOORDS;
};

struct VS_OUTPUT
{
    float4 position			: SV_Position;
	float4 color			: COLOR;
	float3 texcoord			: TEXCOORDS;
};

VS_OUTPUT VSMain( in VS_INPUT input )
{
	VS_OUTPUT output;
	
	output.position = mul( float4( input.position, 1.0f ), WorldViewProjMatrix );
	output.texcoord = input.texcoord;
	
	return output;
}

float4 PSMain( in VS_OUTPUT input ) : SV_Target
{
	float4 color = ModelTexture.Sample( ModelSampler, input.texcoord );;
	
	return( color );
}

