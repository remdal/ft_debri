/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLGameViewController.h          +++     +++	**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 19/09/2025 13:08:30      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef RMDLGAMEVIEWCONTROLLER_H
# define RMDLGAMEVIEWCONTROLLER_H

# include "RMDLMainRenderer.h"

# include <cstdint>
/*
// The enum value is the NSEvent key code
enum class Controls : uint8_t
{
    // Keycodes that control translation
    controlsForward     = 0x0d, // W key
    controlsBackward    = 0x01, // S key
    controlsStrafeUp    = 0x31, // Spacebar
    controlsStrafeDown  = 0x08, // C key
    controlsStrafeLeft  = 0x00, // A key
    controlsStrafeRight = 0x02, // D key

    // Keycodes that control rotation
    controlsRollLeft    = 0x0c, // Q key
    controlsRollRight   = 0x0e, // E key
    controlsTurnLeft    = 0x7b, // Left arrow
    controlsTurnRight   = 0x7c, // Right arrow
    controlsTurnUp      = 0x7e, // Up arrow
    controlsTurnDown    = 0x7d, // Down arrow

    // The brush size
    controlsIncBrush    = 0x1E, // Right bracket
    controlsDecBrush    = 0x21, // Left bracket

    // Additional virtual keys
    controlsFast        = 0x80, // + vite
    controlsSlow        = 0x81,  // - vite
    inventory           = 0x0f  // R
};*/
class   RMDLMTKViewDelegate : public MTK::ViewDelegate
{
public:
    RMDLMTKViewDelegate( MTL::Device* pDevice );
    virtual ~RMDLMTKViewDelegate() override;
    
    virtual void drawInMTKView( MTK::View* pView ) override;
    bool acceptsFirstResponder();
    bool acceptsFirstMouse( MTL::Event* event );

private:
    RMDLMainRenderer*   _pRenderer;
};

/*#ifndef CONTROLLER_H
#define CONTROLLER_H

// For CFIndex, CFTypeRef
#include <CoreFoundation/CFBase.h>
#include <unordered_map>

#include <simd/simd.h>

namespace MTL
{
    class RenderCommandEncoder;
}

class GameController : public NonCopyable
{
public:
    GameController();
    ~GameController();

    bool isLeftArrowDown() const;
    bool isRightArrowDown() const;
    bool isXMacDown() const;
    bool isSpacebarDown() const;

    float leftThumbstickX() const;
    float rightThumbstickX() const;
    bool isButtonADown() const;
    bool isButtonBDown() const;
    bool isButtonXDown() const;
    bool isButtonYDown() const;

    void setHapticIntensity(float intensity) const;
    
    void  renderOverlay(MTL::RenderCommandEncoder* pEnc);
    
    simd::float3 accelerometerData() const;
private:
    CFTypeRef                         _haptics;
    CFTypeRef                         _motionManager;
};

#endif // CONTROLLER_H */

#endif /* RMDLGAMEVIEWCONTROLLER_H */