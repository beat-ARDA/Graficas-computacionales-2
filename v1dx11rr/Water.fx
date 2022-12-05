Texture2D colorMap : register(t0);
Texture2D bumpMap : register(t1);

SamplerState colorSampler : register(s0);

cbuffer cbChangerEveryFrame : register(b0)
{
    matrix worldMatrix;
};

cbuffer cbNeverChanges : register(b1)
{
    matrix viewMatrix;
};

cbuffer cbChangeOnResize : register(b2)
{
    matrix projMatrix;
};

cbuffer cbChangerEveryFrame : register(b0)
{
    float3 lightDirect;
};

cbuffer cbChangerEveryFrame : register(b1)
{
    float3 lightColor;
};

cbuffer cbChangerEveryFrame : register(b2)
{
    float2 texUV;
};

struct VS_Input
{
    float4 pos : POSITION;
    float2 tex0 : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 tangente : NORMAL1;
    float3 binormal : NORMAL2;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 tex0 : TEXCOORD0;
    float3 normal : TEXCOORD1;
    float3 tangent : TEXCOORD2;
    float3 binorm : TEXCOORD3;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut = (PS_Input) 0;
    vsOut.pos = mul(vertex.pos, worldMatrix);
    vsOut.pos = mul(vsOut.pos, viewMatrix);
    vsOut.pos = mul(vsOut.pos, projMatrix);

    vsOut.tex0 = vertex.tex0;
    vsOut.normal = normalize(mul(vertex.normal, worldMatrix));
    vsOut.tangent = normalize(mul(vertex.tangente, worldMatrix));
    vsOut.binorm = normalize(mul(vertex.binormal, worldMatrix));

    return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
    float3 reflection;
    float3 specular;
    float4 bumpmap = bumpMap.Sample(colorSampler, pix.tex0);
	
    float4 fColor = float4(1, 0, 0, 1);

    float3 ambient = float3(0.3f, 0.3f, 0.3f);

    float4 text = colorMap.Sample(colorSampler, pix.tex0);
    float4 textN = bumpMap.Sample(colorSampler, pix.tex0);

	//float3 DiffuseDirection = float3(0.5f, -1.0f, -10.0f);
    float3 DiffuseDirection = lightDirect;

    
    float4 DiffuseColor;
    float3 diffuse1;
	//float4 DiffuseColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
   

    textN = (textN * 2.0f) - 1.0f;
    textN.r = -1 * textN.r;
	
    float3 bumpNormal = normalize((textN.r * pix.binorm) + (textN.g * pix.tangent) + (textN.b * pix.normal));
	
    float norm = dot(saturate(textN), normalize(DiffuseDirection));
	
    float diffuse = dot(pix.normal, DiffuseDirection);
    if (diffuse > 0)
    {
        if (DiffuseDirection.g < -0.05f)
        {
            DiffuseDirection.g = -0.05f;
            diffuse = 0;
        }
        DiffuseColor = float4(lightColor, 1.0f);
        DiffuseColor = saturate(DiffuseColor);
        
        reflection = normalize(2 * diffuse * pix.normal - DiffuseDirection);

		// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
        specular = saturate(float4(pow(saturate(reflection), 15.0f), 1.0f));
    }
   
    //float 3 diffuse = saturate(DiffuseColor.rgb * norm * 1.4);
    //diffuse = saturate(diffuse + ambient);
    diffuse1 = saturate(DiffuseColor.rgb * norm * 1.4);
    diffuse1 = saturate(diffuse1 + ambient);

    fColor = saturate(float4(text.rgb * diffuse1, 1.0f));
    //float2 as = text.xy + (textN.xy * 4);

    //fColor = float4(diffuse, 1.0f);
    //fColor = saturate(text);
    return float4(fColor.r, fColor.g, fColor.b, 0.6);
    //return fColor * float4(as, 1.0f, 1.0f);
}
