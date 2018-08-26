cbuffer WorldTransforms
{
	matrix WorldMatrix;
	matrix WorldViewProjMatrix;	
};

Texture2D DiffuseMap 		: register(t0);
SamplerState AnisoSampler 	: register(s0);

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal   : NORMAL;
	float4 texcoord : TEXCOORDS;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float3 worldposition : POSITION;
	float3 normal   : NORMAL;
	float2 texcoord : TEXCOORDS;
};

struct PSOutput
{
	float4 Normal			: SV_Target0;
	float4 DiffuseAlbedo	: SV_Target1;
	float4 SpecularAlbedo	: SV_Target2;
	float4 Position			: SV_Target3;
};

VS_OUTPUT VS( in VS_INPUT input )
{
	VS_OUTPUT output;
	
	float3 NormalWS = mul( input.normal, (float3x3)WorldMatrix );
	output.normal = NormalWS;
	output.worldposition = mul(input.position, WorldMatrix);
	output.position = mul( float4( input.position, 1.0f ), WorldViewProjMatrix );
	output.texcoord = input.texcoord;
	
	return output;
}

PSOutput PS( in VS_OUTPUT input )
{
	float3 diffuse = DiffuseMap.Sample( AnisoSampler, input.texcoord ).rgb;
	
	PSOutput output;
	output.Normal = float4(input.normal, 1.0f);
	output.DiffuseAlbedo = float4(diffuse, 1.0f);
	output.SpecularAlbedo = float4( 0.7f, 0.7f, 0.7f, 64.0f );;
	output.Position = float4(input.worldposition, 1.0f);
	return output;
}