/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLMainRenderer.mm            +++     +++	**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 19/09/2025 15:30:20      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "RMDLMainRenderer.h"

inline float radians(float degrees)
{
    return (degrees * M_PI / 180.0f);
}

RMDLMainRenderer::RMDLMainRenderer( MTL::Device* pDevice ) : _pDevice( pDevice->retain() ), _angle ( 0.f ), _frame( 0 ), _animationIndex(0)
{
    std::cout << "RMDLMainRenderer constuctor" << std::endl;
    _pCommandQueue = _pDevice->newCommandQueue();

    //_semaphore = dispatch_semaphore_create( Renderer::kMaxFramesInFlight );
}

RMDLMainRenderer::~RMDLMainRenderer()
{
    std::cout << "RMDLMainRenderer destuctor" << std::endl;
    _pCommandQueue->release();
    _pDevice->release();
}

void RMDLMainRenderer::draw( MTK::View* pView )
{
    NS::AutoreleasePool* pPool = NS::AutoreleasePool::alloc()->init();

    RMDLCamera      camera;
    camera.initPerspectiveWithPosition(simd::float3{ 0.0f, 10.0f, 10.0f },
                                       simd::float3{ 0.0f, -0.5f, -1.0f },
                                       simd::float3{ 0.0f, 1.0f, 0.0f },
                                       radians(45.0f),
                                       16.0f / 9.0f,
                                       0.1f,
                                       100.0f
    );
    MTL::CommandBuffer* pCmd = _pCommandQueue->commandBuffer();
    MTL::RenderPassDescriptor* pRpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder( pRpd );
    pEnc->endEncoding();
    pCmd->presentDrawable( pView->currentDrawable() );
    pCmd->commit();

    pPool->release();
}