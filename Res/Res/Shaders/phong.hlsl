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
	float3 worldposition : POSITION;
	float3 normal   : NORMAL;
	float4 texcoord : TEXCOORDS;
};

cbuffer PointLightInfo
{
	float4 LightPosition;
	float4 Ia;
	float4 Id;
	float4 Is;
};

Texture2D       ModelTexture : register( t0 );
SamplerState	ModelSampler : register( s0 ); 

cbuffer SceneInfo
{
	float4 ViewPosition;
};

struct PS_INPUT
{
	float4 position : SV_Position;
	float3 worldposition : POSITION;
	float3 normal   : NORMAL;
	float4 texcoord : TEXCOORDS;
};

VS_OUTPUT VSMain( in VS_INPUT input )
{
	VS_OUTPUT output;
	
	float3 NormalWS = mul( input.normal, (float3x3)WorldMatrix );
	output.normal = NormalWS;
	output.worldposition = mul(input.position, WorldMatrix);
	output.position = mul( float4( input.position, 1.0f ), WorldViewProjMatrix );
	output.texcoord = input.texcoord;
	
	return output;
}

float4 PSMain( in PS_INPUT input ) : SV_Target
{
	float4 lightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float4 color = ModelTexture.Sample( ModelSampler, input.texcoord );
	
	float3 P = input.worldposition;
	float3 LP = LightPosition.xyz;
	float3 VP = ViewPosition.xyz;
	float3 N = normalize(input.normal);
	float3 L = normalize(LP - P);
	float3 V = normalize(VP - P);
	float3 R = normalize(reflect(-L, N));
	float3 H = normalize(L + V);
	
	// ambient
	float4 ambient = Ia * lightColor;
	// diffuse
	float4 diffuse = Id * max(dot(N, L), 0) * lightColor;
	// specular
	float4 Kp = 32;
	
	// phong
	float4 specular = Is * pow(max(dot(V, R), 0), Kp) * lightColor;
	
	// blinn-phong
	//float4 specular = Is * pow(max(dot(N, H), 0), Kp) * lightColor;
	
	float4 lighting = color * (ambient + diffuse + specular);
	
	return lighting;
}