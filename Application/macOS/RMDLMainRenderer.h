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

class RMDLMainRenderer
{
public:
    RMDLMainRenderer( MTL::Device* pDevice );
    ~RMDLMainRenderer();

    void draw( MTK::View* pView );
private:
    MTK::View                   *_pMtkViewTwo;
    MTL::Device*                _pDevice;
    MTL::CommandQueue*          _pCommandQueue;
    float                       _angle;
    int                         _frame;
    dispatch_semaphore_t        _semaphore;
    static const int            kMaxFramesInFlight;
    uint                        _animationIndex;
    RMDLCamera*                 camera;
    simd::float2                position;
    float                       brushsize;
    simd::float2                cursorPosition;
    NSUInteger                  mouseButtonMask;
};

#endif /* RMDLMAINRENDERER_H */