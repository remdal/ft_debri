/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLGameViewController.mm         +++     +++	**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 19/09/2025 13:08:28      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "RMDLGameViewController.h"

RMDLMTKViewDelegate::RMDLMTKViewDelegate( MTL::Device* pDevice )
: MTK::ViewDelegate()
, _pRenderer( new RMDLMainRenderer( pDevice ) )
{
    std::cout << "RMDLMTKViewDelegate constuctor" << std::endl;
}

RMDLMTKViewDelegate::~RMDLMTKViewDelegate()
{
    std::cout << "RMDLMTKViewDelegate destuctor" << std::endl;
    delete _pRenderer;
}

void RMDLMTKViewDelegate::drawInMTKView( MTK::View* pView )
{
    _pRenderer->draw( pView );
}

bool RMDLMTKViewDelegate::acceptsFirstResponder()
{
    return (true);
}

bool RMDLMTKViewDelegate::acceptsFirstMouse( MTL::Event* event )
{
    return (true);
}