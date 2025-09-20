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

    MTL::CommandBuffer* pCmd = _pCommandQueue->commandBuffer();
    MTL::RenderPassDescriptor* pRpd = pView->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder* pEnc = pCmd->renderCommandEncoder( pRpd );
    pEnc->endEncoding();
    pCmd->presentDrawable( pView->currentDrawable() );
    pCmd->commit();

    pPool->release();
}

void RMDLMainRenderer::UpdateCpuUniforms()
{
    _onFrame++;
    _uniforms_cpu.cameraUniforms                = _camera->uniforms();
    float gameTime = _onFrame * (1.0 / 60.f);
    _uniforms_cpu.frameTime                     = simd::max (0.001f, gameTime - 0);
    _uniforms_cpu.mouseState                    = (simd::float3)
    {
        _cursorPosition.x,
        _cursorPosition.y,
        float(_mouseButtonMask)
    };
    _uniforms_cpu.mouseState                    = (simd::float3)
    {
        _cursorPosition.x,
        _cursorPosition.y,
        float(_mouseButtonMask)
    };
    _uniforms_cpu.invScreenSize                 = (simd::float2)
    {
        1.f / 1080,
        1.f / 720
    };
    _uniforms_cpu.projectionYScale              = 1.73205066;
    // set above; // _uniforms_cpu.gameTime     = (float) -[_startTime timeIntervalSinceNow];
    _uniforms_cpu.brushSize                     = _brushSize;
    {
        // Hard code sun
        const simd::float3 sunDirection         = simd::normalize((simd::float3) {1, -0.7, 0.5});
        float tan_half_angle = tanf(_camera->viewAngle() * .5f) * sqrtf(2.0);

        float half_angle = atanf(tan_half_angle);
        float sine_half_angle = sinf(half_angle);

        float cascade_sizes[3] = {400.0f, 1600.0f, 6400.0f};

        float cascade_distances[3];
        cascade_distances[0] = 2 * cascade_sizes[0] * (1.0f - sine_half_angle * sine_half_angle);
        cascade_distances[1] = sqrtf(cascade_sizes[1] * cascade_sizes[1] - cascade_distances[0] * cascade_distances[0] * tan_half_angle * tan_half_angle) + cascade_distances[0];
        cascade_distances[2] = sqrtf(cascade_sizes[2] * cascade_sizes[2] - cascade_distances[1] * cascade_distances[1] * tan_half_angle * tan_half_angle) + cascade_distances[1];

        for (uint c = 0; c < 3; c++)
        {
            simd::float3 center = _camera->position() + _camera->direction() * cascade_distances[c];
            float size = cascade_sizes[c];

            float stepsize = size / 64.0f;
            RMDLCamera* shadow_cam  = new RMDLCamera;
            shadow_cam->initPerspectiveWithPosition(center - sunDirection * size, sunDirection,
                                       simd::float3{ 0.0f, 1.0f, 0.0f },
                                       size * 2.0f,
                                       size * 2.0f,
                                       0.0f,
                                       size * 5.0f );

            center -= simd::fract(simd::dot(center, shadow_cam->up()) / stepsize) * shadow_cam->up() * stepsize;
            shadow_cam->setPosition(center);
            center -= simd::fract(simd::dot(center, shadow_cam->right()) / stepsize) * shadow_cam->right() * stepsize;
            shadow_cam->setPosition(center); 
            _uniforms_cpu.shadowCameraUniforms[c] = shadow_cam->uniforms();
            delete shadow_cam;
        }
    }
}