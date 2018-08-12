Texture2D       ColorMap00 : register( t0 );  
//-----------------------------------------------------------------------------
cbuffer Transforms
 {
	matrix WorldViewProjMatrix;	
};

//-----------------------------------------------------------------------------
struct VS_INPUT
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float4 color : COLOR;
};

struct GS_INPUTOUTPUT
{
	float4 position			: SV_Position;
	float4 color			: COLOR;
};

//-----------------------------------------------------------------------------
VS_OUTPUT VSMain( in VS_INPUT v )
{
	VS_OUTPUT o = (VS_OUTPUT)0;

	// Simply propogate attributes through
	o.position = mul(v.position, WorldViewProjMatrix);
	o.color = v.color;

	return o;
}

[maxvertexcount(6)]
void GSMain( triangle GS_INPUTOUTPUT input[3], inout TriangleStream<GS_INPUTOUTPUT> TriangleOutputStream )
{
	// Calculate the face normal
	float3 faceEdgeA = input[1].position.xyz - input[0].position.xyz;
	float3 faceEdgeB = input[2].position.xyz - input[0].position.xyz;
	float3 faceNormal = normalize( cross(faceEdgeA, faceEdgeB) );
	
	// Output vertices
	for (int i = 0; i < 3; i++) {
		GS_INPUTOUTPUT output;
		// Blow up the cube
		float4 position = input[i].position + float4(faceNormal/4, 0);
		
		// Transform the new position to clipspace.
		output.position = position;
		output.color = input[i].color;

		//TriangleOutputStream.Append(output);
	}
	//TriangleOutputStream.RestartStrip();
	
	float4 fp[3];
	fp[0] = 0.5f * (input[0].position + input[1].position);
	fp[1] = 0.5f * (input[0].position + input[2].position);
	fp[2] = 0.5f * (input[2].position + input[1].position);
	for (int i = 0; i < 3; i++) {
		GS_INPUTOUTPUT output;

		output.position = fp[i];
		output.color = input[i].color;

		TriangleOutputStream.Append(output);
	}
	TriangleOutputStream.RestartStrip();
	
	for (int i = 0; i < 3; i++) {
		GS_INPUTOUTPUT output;

		output.position = input[i].position;
		output.color = input[i].color;

		TriangleOutputStream.Append(output);
	}
	TriangleOutputStream.RestartStrip();
}

//-----------------------------------------------------------------------------
float4 PSMain( in GS_INPUTOUTPUT input ) : SV_Target
{
	//float4 color = input.color;
	//return( color );
	int3 screenspace = int3( input.position.x, input.position.y, 0 );
	float4 vSample = ColorMap00.Load( screenspace );
	return( vSample );
}
//-----------------------------------------------------------------------------