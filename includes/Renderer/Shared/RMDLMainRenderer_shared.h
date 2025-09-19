/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLMainRenderer_shared.h         +++     +++	**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 18/09/2025 12:51:12      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RMDLMAIN_RENDERER_SHARED_H
# define RMDLMAIN_RENDERER_SHARED_H

# import <simd/simd.h>

# define GAME_TIME 1.1f

struct RMDLCameraUniforms
{
    simd::float4x4      viewMatrix;
    simd::float4x4      projectionMatrix;
    simd::float4x4      viewProjectionMatrix;
    simd::float4x4      invOrientationProjectionMatrix;
    simd::float4x4      invViewProjectionMatrix;
    simd::float4x4      invProjectionMatrix;
    simd::float4x4      invViewMatrix;
    simd::float4        frustumPlanes[6];
};

#endif /* RMDLMAIN_RENDERER_SHARED_H */
