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

struct RMDLUniforms
{
    RMDLCameraUniforms  cameraUniforms;
    RMDLCameraUniforms  shadowCameraUniforms[3];

    // Mouse state: x, y = position in pixels; z = buttons
    simd::float3        mouseState;
    simd::float2        invScreenSize;
    float               projectionYScale;
    float               brushSize;

    float               ambientOcclusionContrast;
    float               ambientOcclusionScale;
    float               ambientLightScale;
#if !USE_CONST_GAME_TIME
    float               gameTime;
#endif
    float               frameTime;  // TODO. this doesn't appear to be initialized until UpdateCpuUniforms. OK?
};

struct Plane
{
    simd::float3        normal = { 0.f, 1.f, 0.f };
    float               distance = 0.f;
};

struct Frustum
{
    Plane               topFace;
    Plane               bottomFace;
    Plane               rightFace;
    Plane               leftFace;
    Plane               farFace;
    Plane               nearFace;
};

struct RMDLObjVertex
{
    simd::float3        position;
    simd::float3        normal;
    simd::float3        color;
    bool operator == (const RMDLObjVertex& o) const
    {
        return (simd::all (o.position == position) &&
        simd::all (o.normal == normal) &&
        simd::all (o.color == color));
    }
};

#endif /* RMDLMAIN_RENDERER_SHARED_H */

/* v = sommet, vt = coordonnée de texture, vn = normale, f = face, o = nom de l'objet, g = nom du groupe, s = numéro du groupe?, l = ligne d'élément,
 https://en.wikipedia.org/wiki/Wavefront_.obj_file


mtllib cube.mtl
o Cube
v 1.000000 1.000000 -1.000000
v 1.000000 -1.000000 -1.000000
v 1.000000 1.000000 1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 1.000000 -1.000000
v -1.000000 -1.000000 -1.000000
v -1.000000 1.000000 1.000000
v -1.000000 -1.000000 1.000000
vn -0.0000 1.0000 -0.0000
vn -0.0000 -0.0000 1.0000
vn -1.0000 -0.0000 -0.0000
vn -0.0000 -1.0000 -0.0000
vn 1.0000 -0.0000 -0.0000
vn -0.0000 -0.0000 -1.0000
vt 0.625000 0.500000
vt 0.875000 0.500000
vt 0.875000 0.750000
vt 0.625000 0.750000
vt 0.375000 0.750000
vt 0.625000 1.000000
vt 0.375000 1.000000
vt 0.375000 0.000000
vt 0.625000 0.000000
vt 0.625000 0.250000
vt 0.375000 0.250000
vt 0.125000 0.500000
vt 0.375000 0.500000
vt 0.125000 0.750000
s 0
usemtl Material
f 1/1/1 5/2/1 7/3/1 3/4/1
f 4/5/2 3/4/2 7/6/2 8/7/2
f 8/8/3 7/9/3 5/10/3 6/11/3
f 6/12/4 2/13/4 4/5/4 8/14/4
f 2/13/5 1/1/5 3/4/5 4/5/5
f 6/11/6 5/10/6 1/1/6 2/13/6    */