Texture2D color : register(t0);
SamplerState colorSampler : register(s0);

cbuffer cbWorldMatrix : register(b0)
{
    matrix worldMatrix;
}

struct VS_Input
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input psOut;
    psOut.pos = mul(vertex.pos, worldMatrix);
    psOut.normal = mul(vertex.normal, (float3x4)worldMatrix);
    psOut.uv = vertex.uv;
    
    return psOut;
}

float4 PS_Main(PS_Input pixel) : SV_TARGET
{
    float4 textura = color.Sample(colorSampler, pixel.uv);
    clip(textura.a - 0.8f);
    
    return textura;
}