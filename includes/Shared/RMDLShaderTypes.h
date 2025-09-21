/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLShaderTypes.h            +++     +++		**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 21/09/2025 10:11:04      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RMDLSHADERTYPES_H
# define RMDLSHADERTYPES_H

# include <simd/simd.h>

#include <TargetConditionals.h>

typedef enum VertexAttributes
{
    VertexAttributePosition  = 0,
    VertexAttributeTexcoord  = 1,
    VertexAttributeNormal    = 2,
    VertexAttributeTangent   = 3,
    VertexAttributeBitangent = 4
}   VertexAttributes;

struct FrameData
{
    simd::float4x4 projection_matrix;
    simd::float4x4 projection_matrix_inverse;
    simd::float4x4 view_matrix;
    uint framebuffer_width;
    uint framebuffer_height;

    simd::float4x4 sky_modelview_matrix;
    simd::float4x4 shadow_mvp_matrix;
    simd::float4x4 shadow_mvp_xform_matrix;

    simd::float4 sun_eye_direction;
    simd::float4 sun_color;
    float sun_specular_intensity;
};

#endif