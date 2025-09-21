/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLMainRenderer.h              +++     +++	**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 19/09/2025 15:30:22      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RMDLMAINRENDERER_H
# define RMDLMAINRENDERER_H

# include <cassert>

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

# include <simd/simd.h>
# include <chrono>
# include <time.h>
# include <iostream>
# include <vector>
# include <fstream>
# include <thread>

# include <Utils/hpp/RMDLCamera.hpp>
# import <Shared/RMDLMainRenderer_shared.h>
# import <Utils/hpp/RMDLMesh.hpp>

class RMDLMainRenderer
{
public:
    RMDLMainRenderer( MTL::Device* pDevice );
    ~RMDLMainRenderer();

    void draw( MTK::View* pView );
    void UpdateCpuUniforms();
private:
    MTK::View                   *_pMtkViewTwo;
    MTL::Device*                _pDevice;
    MTL::CommandQueue*          _pCommandQueue;
    float                       _angle;
    int                         _frame;
    dispatch_semaphore_t        _semaphore;
    static const int            kMaxFramesInFlight;
    uint                        _animationIndex;
    RMDLCamera*                 _camera;
    simd::float2                _position;
    float                       _brushSize;
    simd::float2                _cursorPosition;
    NSUInteger                  _mouseButtonMask;
    //NS::Date                    _startTime;
    //auto start = std::chrono::system_clock::now();
    dispatch_semaphore_t        _inFlightSemaphore;
    RMDLUniforms                _uniforms_cpu;
    MTL::Texture*               _shadowMap;
    MTL::Texture*               _perlinMap;
    NSUInteger                  _onFrame; // to count frames, and using frame-based times
    MTL::Texture*               _gBuffer0;
    MTL::Texture*               _gBuffer1;
    MTL::RenderPipelineState*   m_pSkyboxPipelineState;
    MTL::Texture*               m_pSkybox;
    Mesh                        m_skyboxMesh;
};

#endif /* RMDLMAINRENDERER_H */