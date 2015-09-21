////=============================================================================
//// Filename: Fog.fx                                                                                                   
//// Author: Jc Fowles
//// Discription: Adds a Basic Fog Effect to the Scene 
////=============================================================================
//
//// Local Includes
//
//cbuffer cbPerFrame
//{
//	float4x4 g_matView;
//	float4x4 g_matProj;
//};
//
//cbuffer cbPerObject
//{
//	float4x4 g_matWorld;
//	float4x4 g_matTex;
//
//
//};
//
//// Nonnumeric values cannot be added to a cbuffer.
//Texture2D g_shaderTexture; // TO DO: Rename possibly
//
//// TO DO: move to the correct buffer
//float g_fogStart;
//float g_fogEnd;
//
//SamplerState g_triLinearSam
//{
//	Filter = MIN_MAG_MIP_LINEAR;
//	AddressU = WRAP;
//	AddressV = WRAP;
//};
//
//
//struct VS_IN
//{
//	float3 position		: POSITION;
//	float3 normal		: NORMAL;
//	float2 texCoord		: TEXCOORD;
//};
//
//struct VS_OUT
//{
//	float4 positionH    : SV_POSITION;
//	float3 position     : POSITION;
//	float3 normal		: NORMAL;
//    float2 texCoord     : TEXCOORD;
//	float fogFactor		: FOG;
//};
// 
//
//
//VS_OUT VS_Fog(VS_IN _inputVS)
//{
//	VS_OUT outputVS;
//	float4 cameraPosition;
//	
//	// Transform to world space space.
//	outputVS.position = mul(float4(_inputVS.position, 1.0f), g_matWorld).xyz;
//	outputVS.normal = mul(float4(_inputVS.normal, 0.0f), g_matWorld).xyz;
//		
//	// Transform to homogeneous clip space.
//	outputVS.positionH = mul(float4(_inputVS.position, 1.0f), g_matWorld);
//	outputVS.positionH = mul(outputVS.positionH, g_matView);
//	outputVS.positionH = mul(outputVS.positionH, g_matProj);
// 	
//	// Output vertex attributes for interpolation across triangle.
//	outputVS.texCoord = mul(float4(_inputVS.texCoord, 0.0f, 1.0f), g_matTex).xy;
//
//	// Calculate the camera position.
//	cameraPosition = mul(_inputVS.position, g_matWorld);
//	cameraPosition = mul(cameraPosition, g_matView);
//
//	// Calculate linear fog.    
//	outputVS.fogFactor = saturate((g_fogEnd - cameraPosition.z) / (g_fogEnd - g_fogStart));
//
//	return outputVS;
//}
//
//float4 PS_Fog(VS_OUT _inputPS) : SV_Target
//{
//	float4 textureColor;
//	float4 fogColor;
//	float4 finalColor;
//
//	// Sample the texture pixel at this location.
//	textureColor = g_shaderTexture.Sample(g_triLinearSam, _inputPS.texCoord);
//
//	// Set the color of the fog to grey.
//	// TO DO: Passed in possibly??
//	fogColor = float4(0.5f, 0.5f, 0.5f, 1.0f);
//
//	// Calculate the final color using the fog effect equation.
//	finalColor = _inputPS.fogFactor * textureColor + (1.0 - _inputPS.fogFactor) * fogColor;
//
//	return finalColor;
//}
//
//technique10 FogTech
//{
//    pass P0
//    {
//		SetVertexShader(CompileShader(vs_4_0, VS_Fog()));
//       	SetGeometryShader( NULL );
//		SetPixelShader(CompileShader(ps_4_0, PS_Fog()));
//    }
//}
