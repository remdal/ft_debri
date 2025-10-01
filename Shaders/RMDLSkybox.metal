#include <metal_stdlib>

using namespace metal;

// Include header shared between this Metal shader code and C code executing Metal API commands
#include "RMDLShaderTypes.h"

// Per-vertex inputs fed by vertex buffer laid out with MTLVertexDescriptor in Metal API, Entrées par sommet alimentées par le tampon de sommet mis en place avec MTLVertexDescriptor dans l'API Metal
struct SkyboxVertex
{
    float4 position [[attribute(VertexAttributePosition)]];
    float3 normal   [[attribute(VertexAttributeNormal)]];
};

struct SkyboxInOut
{
    float4 position [[position]];
    float3 texcoord;
};