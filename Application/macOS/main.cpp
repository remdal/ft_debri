/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: main.cpp            +++     +++				**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 19/09/2025 13:08:07      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#include <QuartzCore/QuartzCore.hpp>

#include "RMDLAppDelegate.h"

#include <stdio.h>

int main ( int argc, char* argv[] )
{;
    unsigned int numThreads = std::thread::hardware_concurrency();
    std::cout << "number of Threads = std::thread::hardware_concurrency : " << numThreads << std::endl;
    NS::AutoreleasePool* pAutoreleasePool = NS::AutoreleasePool::alloc()->init();
    RMDLAppDelegate del;
    NS::Application* pSharedApplication = NS::Application::sharedApplication();
    pSharedApplication->setDelegate( &del );
    pSharedApplication->run();
    pAutoreleasePool->release();
    return (0);
}
