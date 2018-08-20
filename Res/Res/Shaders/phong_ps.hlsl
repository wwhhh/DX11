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
	float4 worldPos : POSITION;
	float3 normal   : NORMAL;
	float4 texcoord : TEXCOORDS;
};

float4 PSMain( in PS_INPUT input ) : SV_Target
{
	float4 lightColor = float4(1.0f, 0.2f, 0.2f, 1.0f);
	float4 color = ModelTexture.Sample( ModelSampler, input.texcoord );
	
	float3 N = normalize(input.normal);
	float3 L = normalize(LightPosition.xyz - input.position.xyz);
	float3 V = normalize(ViewPosition.xyz - input.position.xyz);
	float3 R = normalize(reflect(-L, N));
	
	// ambient
	float4 ambient = Ia * lightColor;
	
	// diffuse
	float4 diffuse = Id * max(dot(L, N), 0) * lightColor;
	
	// specular
	float4 Kp = 32;
	float4 specular = Is * pow(max(dot(V, R), 0), Kp) * lightColor;
	
	float4 lighting = color * (ambient + diffuse + specular);
	
	return lighting;
}