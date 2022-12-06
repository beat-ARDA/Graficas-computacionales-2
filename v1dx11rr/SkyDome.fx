Texture2D textures;
SamplerState colorSampler : register(s0);

cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projMatrix;
    float4 valores;
};

struct VS_Input
{
    float4 pos : POSITION;
    float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 tex0 : TEXCOORD0;
    float fogFactor : FOG;
};

PS_Input VS_Main(VS_Input vertex)
{
    float4 vertexPos;
    PS_Input vsOut = (PS_Input) 0;
    vsOut.pos = mul(vertex.pos, worldMatrix);
    vsOut.pos = mul(vsOut.pos, viewMatrix);
    vertexPos = vsOut.pos;
    vsOut.pos = mul(vsOut.pos, projMatrix);

    vsOut.tex0 = vertex.tex0;
	
    float fogStart = -90.0f;
    float fogEnd = 90.0f;
    
    float fogFactor = saturate((fogEnd - vertexPos.z) / (fogEnd - fogStart));
    vsOut.fogFactor = fogFactor;

    return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
    float4 finalColor = textures.Sample(colorSampler, pix.tex0);

    float4 fogColor = float4(0.5, 0.5, 0.5, 1.0);
    finalColor = pix.fogFactor * finalColor + (1.0f - pix.fogFactor) * fogColor;
	
    return finalColor;
}