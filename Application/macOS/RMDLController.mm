#include "RMDLController.h"

typedef NS_OPTIONS(uint8_t, Controls)
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
    controlsSlow        = 0x81, // - vite

    inventory           = 0x0f  // R Key
};

GameController::GameController()
: _haptics(nil)
, _motionManager(nil)
{
    [NSNotificationCenter.defaultCenter addObserverForName:GCControllerDidDisconnectNotification
                                                    object:nil
                                                     queue:nil
                                                usingBlock:^(NSNotification * _Nonnull notification) {
        
        
        GCController* controller = (GCController *)(notification.object);
        if (![controller.vendorName isEqualToString:@"Apple Touch Controller"])
        {
            CFRelease(this->_haptics);
            this->_haptics = nil;
        }
    }];
    
    __block GameController* pOwner = this; // capture as writable by the block
    
    [NSNotificationCenter.defaultCenter addObserverForName:GCControllerDidConnectNotification
                                                    object: nil
                                                     queue: nil
                                                usingBlock:^(NSNotification * _Nonnull notification) {
        
        GCController* controller = (GCController *)(notification.object);
        
        // Check if the controller supports haptic feedback and if so prepare to
        // play haptics on it:
        
        if (controller.haptics)
        {
            CHHapticEngine* hapticEngine =
            [controller.haptics createEngineWithLocality:GCHapticsLocalityHandles];
            
            if (pOwner->_haptics)
            {
                CFRelease(this->_haptics);
                this->_haptics = nil;
            }
            
            if (hapticEngine)
            {
                LongRunningHaptics* lrh = [[LongRunningHaptics alloc] initWithEngine:hapticEngine];
                pOwner->_haptics = CFBridgingRetain(lrh);
                NSLog(@"Created haptic engine: %@ and lrh: %@ storing in owner: %p", hapticEngine, lrh, pOwner);
            }
        }
    }];
    
    // Accelerometer
    
#if TARGET_OS_IOS
    CMMotionManager* cm = [[CMMotionManager alloc] init];
    if (cm.isAccelerometerAvailable)
    {
        cm.accelerometerUpdateInterval = 1/60.0f;
        [cm startAccelerometerUpdates];
        _motionManager = CFBridgingRetain(cm);
    }
#endif
}

GameController::~GameController()
{
    if (this->_haptics)
        CFRelease(this->_haptics);
    
    if (this->_motionManager)
        CFRelease(this->_motionManager);
}

simd::float3 GameController::accelerometerData() const
{
    if (this->_motionManager)
    {
#if TARGET_OS_IOS
        CMMotionManager* cm = (__bridge CMMotionManager *)this->_motionManager;
        CMAcceleration accel = cm.accelerometerData.acceleration;
        return simd::float3 { (float)accel.x, (float)accel.y, (float)accel.z };
#endif
    }
    return simd::float3{ 0, 0, 0 };
}

bool GameController::isLeftArrowDown() const
{
    return [GCKeyboard.coalescedKeyboard.keyboardInput buttonForKeyCode:GCKeyCodeLeftArrow].pressed;
}

bool GameController::isRightArrowDown() const
{
    return [GCKeyboard.coalescedKeyboard.keyboardInput buttonForKeyCode:GCKeyCodeRightArrow].pressed;
}

bool GameController::isSpacebarDown() const
{
    return [GCKeyboard.coalescedKeyboard.keyboardInput buttonForKeyCode:GCKeyCodeSpacebar].pressed;
}

bool GameController::isXMacDown() const
{
    return [GCKeyboard.coalescedKeyboard.keyboardInput buttonForKeyCode:GCKeyCodeKeyX].pressed;
}

float GameController::leftThumbstickX() const
{
    GCExtendedGamepad* gamepad = GCController.controllers.firstObject.extendedGamepad;
    return gamepad.leftThumbstick.xAxis.value;
}

float GameController::rightThumbstickX() const
{
    GCExtendedGamepad* gamepad = GCController.controllers.firstObject.extendedGamepad;
    return gamepad.rightThumbstick.xAxis.value;
}

bool GameController::isButtonADown() const
{
    GCExtendedGamepad* gamepad = GCController.controllers.firstObject.extendedGamepad;
    return gamepad.buttonA.pressed;
}

bool GameController::isButtonBDown() const
{
    GCExtendedGamepad* gamepad = GCController.controllers.firstObject.extendedGamepad;
    return (gamepad.buttonB.pressed);
}

bool GameController::isButtonXDown() const
{
    GCExtendedGamepad* gamepad = GCController.controllers.firstObject.extendedGamepad;
    return (gamepad.buttonX.pressed);
}

bool GameController::isButtonYDown() const
{
    GCExtendedGamepad* gamepad = GCController.controllers.firstObject.extendedGamepad;
    return (gamepad.buttonY.pressed);
}

void GameController::setHapticIntensity(float intensity) const
{
    if (_haptics)
    {
        LongRunningHaptics* lrh = (__bridge LongRunningHaptics *)_haptics;
        [lrh setIntensity:intensity];
    }
}

void GameController::renderOverlay( MTL::RenderCommandEncoder* pEnc )
{
    // Here you can customize how your touch (virtual) game controller looks
    // by directly issuing Metal commands and render it onscreen.

    // To accomplish this, in IOSViewController.m, customize the Virtual Game
    // Controller to hide its buttons, and render your custom UI from here.

    // Follow the guidance in the HIG to develop a great touch controls
    // experience for your players by surfacing actions relevant to your
    // game's context, and drawing semantically-meaningful glyphs.
}