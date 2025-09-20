/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLAppDelegate.h            +++     +++		**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 19/09/2025 13:13:11      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <AppKit/AppKit.hpp>

#include "RMDLGameViewController.h"
#include "RMDLMainRenderer.h"
class RMDLAppDelegate : public NS::ApplicationDelegate
{
public:
    ~RMDLAppDelegate();

    NS::Menu* createMenuBar();

    virtual void applicationWillFinishLaunching( NS::Notification* pNotification ) override;
    virtual void applicationDidFinishLaunching( NS::Notification* pNotification ) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed( NS::Application* pSender ) override;

private:
    NS::Window*             _pWindow;
    NS::Object*             _pSlider;
    MTK::View*              _pMtkView;
    MTL::Device*            _pDevice;
    RMDLMTKViewDelegate*    _pViewDelegate = nullptr;
};