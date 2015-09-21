//=============================================================================
// LitTex.fx                                                                                                   
//
// Transforms, lights, and textures geometry.
//=============================================================================

// Local Includes
#include "LightStructures.fx"

cbuffer cbPerFrame
{
	Light g_light;
	float3 g_eyePosW;

	float4x4 g_matView;
	float4x4 g_matProj;
};

cbuffer cbPerObject
{
	float4x4 g_matWorld;
	float4x4 g_matTex;
	float	 g_reduceAlpha;

	// Fog Variables
	float g_fogStart;
	float g_fogRange;
	float4 g_fogColor;
};

// Nonnumeric values cannot be added to a cbuffer.
Texture2D g_mapDiffuse;
Texture2D g_mapDiffuse2;
Texture2D g_mapSpec;

bool g_specularEnabled;

SamplerState g_triLinearSam
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

struct VS_IN
{
	float3 position		: POSITION;
	float3 normal		: NORMAL;
	float2 texCoord		: TEXCOORD;
};

struct VS_OUT
{
	float4 positionH    : SV_POSITION;
	float3 positionW    : POSITION;
	float3 normal		: NORMAL;
    float2 texCoord     : TEXCOORD;
};

struct VS_FOG_OUT
{
	float4 positionH    : SV_POSITION;
	float3 positionW    : POSITION;
	float3 normal		: NORMAL;
	float2 texCoord     : TEXCOORD;
	float fogLERP		: FOG;
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
 
VS_OUT TransformVert(VS_IN _inputVS);
float4 LightTexture(VS_OUT _inputPS);

VS_OUT VS_Standard(VS_IN _inputVS)
{
	VS_OUT	outputVS;

	// Transform to world space space.
	outputVS.positionW = mul(float4(_inputVS.position, 1.0f), g_matWorld).xyz;
	outputVS.normal = mul(float4(_inputVS.normal, 0.0f), g_matWorld).xyz;

	// Transform to homogeneous clip space.
	outputVS.positionH = mul(float4(_inputVS.position, 1.0f), g_matWorld);
	outputVS.positionH = mul(outputVS.positionH, g_matView);
	outputVS.positionH = mul(outputVS.positionH, g_matProj);

	// Output vertex attributes for interpolation across triangle.
	outputVS.texCoord = mul(float4(_inputVS.texCoord, 0.0f, 1.0f), g_matTex).xy;
	
	return outputVS;
}

float4 PS_Standard(VS_OUT _inputPS) : SV_Target
{
	// Get materials from texture maps.
	float4 diffuse = g_mapDiffuse.Sample(g_triLinearSam, _inputPS.texCoord);
	float4 spec = g_mapSpec.Sample(g_triLinearSam, _inputPS.texCoord);

	// Map [0,1] --> [0,256]
	spec.a *= 256.0f;

	// Interpolating normal can make it not be of unit length so normalize it.
	float3 normal = normalize(_inputPS.normal);

	// Compute the lit color for this pixel.
	SurfaceInfo surface = { _inputPS.positionW, normal, diffuse, spec };
	float3 litColor = ParallelLight(surface, g_light, g_eyePosW);

	// Calculate the lit texture color
	return float4(litColor, diffuse.a);
}

//--------------------------------------------------------------
// Standard Lit Texture Technique
//--------------------------------------------------------------

technique10 StandardTech
{
    pass P0
    {
		SetVertexShader(CompileShader(vs_4_0, VS_Standard()));
       	SetGeometryShader( NULL );
		SetPixelShader(CompileShader(ps_4_0, PS_Standard()));
    }
}

//--------------------------------------------------------------
// Fog Technique
//--------------------------------------------------------------

VS_FOG_OUT VS_Fog(VS_IN _inputVS)
{
	VS_FOG_OUT	outputVS;
	
	// Transform to world space space.
	outputVS.positionW = mul(float4(_inputVS.position, 1.0f), g_matWorld).xyz;
	outputVS.normal = mul(float4(_inputVS.normal, 0.0f), g_matWorld).xyz;

	// Transform to homogeneous clip space.
	outputVS.positionH = mul(float4(_inputVS.position, 1.0f), g_matWorld);
	outputVS.positionH = mul(outputVS.positionH, g_matView);
	outputVS.positionH = mul(outputVS.positionH, g_matProj);

	// Output vertex attributes for interpolation across triangle.
	outputVS.texCoord = mul(float4(_inputVS.texCoord, 0.0f, 1.0f), g_matTex).xy;
 
	// Calculate linear fog
	float distanceFromObj = distance(outputVS.positionW, g_eyePosW);
	outputVS.fogLERP = saturate((distanceFromObj - g_fogStart) / g_fogRange);

	return outputVS;
}

float4 PS_Fog(VS_FOG_OUT _inputPS) : SV_Target
{
	// Get materials from texture maps.
	float4 diffuse = g_mapDiffuse.Sample(g_triLinearSam, _inputPS.texCoord);
	float4 spec = g_mapSpec.Sample(g_triLinearSam, _inputPS.texCoord);

	// Map [0,1] --> [0,256]
	spec.a *= 256.0f;

	// Interpolating normal can make it not be of unit length so normalize it.
	float3 normal = normalize(_inputPS.normal);

	// Compute the lit color for this pixel.
	SurfaceInfo surface = { _inputPS.positionW, normal, diffuse, spec };
	float3 litColor = ParallelLight(surface, g_light, g_eyePosW);
	
	// Lerp the texture color towards the fog color based on the forLERP amount
	float3 foggedColor = lerp(litColor, g_fogColor.xyz, _inputPS.fogLERP);

	return float4(foggedColor, diffuse.a);
}

technique10 FogTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS_Fog()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS_Fog()));
	}
}
