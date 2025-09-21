/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLSkybox.metal            +++     +++		**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 21/09/2025 09:57:40      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <metal_stdlib>
using namespace metal;

#include "RMDLShaderTypes.h"

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

vertex SkyboxInOut skybox_vertex(SkyboxVertex        in        [[ stage_in ]],
                                 constant FrameData &frameData [[ buffer(BufferIndexFrameData) ]])
{
    SkyboxInOut out;
    out.position = frameData.projection_matrix * frameData.sky_modelview_matrix * in.position;
    out.texcoord = in.normal;

    return out;
}

fragment half4 skybox_fragment(SkyboxInOut        in             [[ stage_in ]],
                               texturecube<float> skybox_texture [[ texture(TextureIndexBaseColor) ]])
{
    constexpr sampler linearSampler(mip_filter::linear, mag_filter::linear, min_filter::linear);
    float4 color = skybox_texture.sample(linearSampler, in.texcoord);

    return half4(color);
}