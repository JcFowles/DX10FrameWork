//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
matrix World			: WORLD;
matrix View				: VIEW;
matrix Projection		: PROJECTION;

float DeltaTime : TIME;

Texture2D Texture;

//--------------------------------------------------------------------------------------
// Sample States 
//--------------------------------------------------------------------------------------
SamplerState SampleType // The sampler state allows us to modify how the pixels are written to the polygon face when shaded.
{
	Filter = MIN_MAG_MIP_LINEAR; // Filter will determine how it decides which pixels will be used or combined to create the final look of the texture on the polygon face
	AddressU = Wrap;
	AddressV = Wrap;
};

//--------------------------------------------------------------------------------------
// Structs
//--------------------------------------------------------------------------------------
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
};

// For transparency values
BlendState SrcAlphaBlendingAdd
{
	BlendEnable[0] = TRUE;
	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;
	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
	RenderTargetWriteMask[0] = 0x0F;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(float4 Pos : POSITION, float2 Tex : TEXCOORD0)
{
	PS_INPUT output;

	// Change the position vector to be 4 units for proper matrix calculations.
	Pos.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.Pos = mul(Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	// Store the texture coordinates for the pixel shader.
	output.Tex = Tex;

	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT _input) : SV_Target
{
	float4 textureColor;

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = Texture.Sample(SampleType, _input.Tex);

	return textureColor;
}

//--------------------------------------------------------------------------------------
// Technique
//--------------------------------------------------------------------------------------
technique10 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));

		// For transparency values
		SetBlendState(SrcAlphaBlendingAdd, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}