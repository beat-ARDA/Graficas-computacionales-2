Texture2D colorMap : register(t0);
Texture2D specMap : register(t1);
Texture2D normalMap : register(t2);

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

cbuffer cbChangesOccasionally : register(b3)
{
    float3 cameraPos;
};

cbuffer cbChangesOccasionally : register(b4)
{
    float specForce;
};

cbuffer cbColorDifuso : register(b5)
{
    float4 colorDifusoEntrante;
};

cbuffer cbLightPos : register(b6)
{
    float4 lightPos;
};

cbuffer cbMagnitudEspecular : register(b0)
{
    float4 magnitudEspecular;
};

cbuffer cbColorBala : register(b1)
{
    float4 colorBala;
};

struct VS_Input
{
    float4 pos : POSITION;
    float2 tex0 : TEXCOORD0;
    float3 norm : NORMAL;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 tex0 : TEXCOORD0;
    float3 norm : TEXCOORD1;
    float3 lightVec : TEXCOORD2;
    float3 cameraVec : TEXCOORD3;
    float3 tangent : TEXCOORD4;
    float3 binormal : TEXCOORD5;
    float fogFactor : FOG;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut = (PS_Input) 0;

    // Initial transformations
    float4 worldPos = mul(vertex.pos, worldMatrix);
    float4 vertexPos;
    vsOut.pos = mul(worldPos, viewMatrix);
    vertexPos = vsOut.pos;
    vsOut.pos = mul(vsOut.pos, projMatrix);
    vsOut.tex0 = vertex.tex0;
    
    //Colocar normal en matriz de mundo para que se mueva
    vsOut.norm = mul(vertex.norm, (float3x3) worldMatrix);
    vsOut.norm = normalize(vsOut.norm);
    
    //tangente
    float tangente;
    float c1 = cross(vsOut.norm, float3(0.0f, 0.0f, 1.0f));
    float c2 = cross(vsOut.norm, float3(0.0f, 1.0f, 0.0f));
    
    if (length(c1) > length(c2))
    {
        tangente = c1;
    }
    else
    {
        tangente = c2;
    }
    
    vsOut.tangent = normalize(tangente);
    
    //Binormal
    float3 binormal;
    
    binormal = cross(vsOut.norm, vsOut.tangent);
    vsOut.binormal = normalize(binormal);
    

    // Calcular el vector de la luz
    //vsOut.lightVec = normalize((float3) lightPos - (float3) worldPos);
    float3 lightDirection = float3(-0.2f, -1.0f, -0.3f);
    vsOut.lightVec = normalize(-lightDirection);
    // Calculate camera vector
    vsOut.cameraVec = normalize(cameraPos - (float3) worldPos);
    
    float fogStart = -90.0f;
    float fogEnd = 90.0f;
    
    float fogFactor = saturate((fogEnd - vertexPos.z) / (fogEnd - fogStart));
    vsOut.fogFactor = fogFactor;

    return vsOut;
}

float4 PS_Main(PS_Input frag) : SV_TARGET
{
        // Get parameters
    float3 normal = normalize(frag.norm);
    float3 lightVec = normalize(frag.lightVec);
    float3 cameraVec = normalize(frag.cameraVec);
    float4 textura = colorMap.Sample(colorSampler, frag.tex0);
    float4 textnorm = normalMap.Sample(colorSampler, frag.tex0);
    // Ambiental
    float3 ambiental = float3(0.2f, 0.2f, 0.2f);
    //float3 lightAmbiental = ambiental * textura.xyz;
    float3 lightAmbiental = ambiental;

    textnorm = normalize(2.0 * textnorm - 1.0);
    float3 bumpNormal = (textnorm.r * frag.tangent) + (textnorm.g * frag.binormal) + (textnorm.b * frag.norm);
    bumpNormal = normalize(bumpNormal);
    //Difusa
    
    float3 colorDifuso = float3(1.0f, 1.0f, 1.0f);
    float intensidadDifusa = saturate(dot(bumpNormal, lightVec));
    //float3 lightDifusa = colorDifuso * intensidadDifusa * textura.xyz;
    float3 lightDifusa = colorDifuso * intensidadDifusa;
    
    //Especular
    float3 colorEspecular = float3(0.8f, 0.8f, 0.8f);
    float3 reflecDir = reflect(-lightVec, bumpNormal);
    float spec = pow(saturate(dot(cameraVec, reflecDir)), 32.0f);
    //float3 lightEspecular = colorEspecular * (spec * textura.xyz);
    float3 lightEspecular = colorEspecular * spec;
    
    //Final
    float3 iluminacionFinal;
    if (colorBala.w < 1.0f)
    {
    
        iluminacionFinal = lightAmbiental + lightDifusa + lightEspecular;
    }
    else
    {
        iluminacionFinal = lightAmbiental + lightDifusa + lightEspecular + colorBala.rgb;
    }
    
    float4 colorFinal = float4(textura.r, textura.g, textura.b, 1.0f) * float4(iluminacionFinal, 1.0f);
    float4 fogColor = float4(0.5, 0.5, 0.5, 1.0);
    colorFinal = frag.fogFactor * colorFinal + (1.0f - frag.fogFactor) * fogColor;
    
    

    return colorFinal;
}