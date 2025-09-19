/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: NonCopyable.h            +++     +++			**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 19/09/2025 15:56:51      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef NONCOPYABLE_H
# define NONCOPYABLE_H

class NonCopyable
{
public:
    NonCopyable()                              = default;
    NonCopyable(const NonCopyable&)            = delete;
    NonCopyable(NonCopyable&&)                 = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable& operator=(NonCopyable&&)      = delete;
};

#endif // NONCOPYABLE_H