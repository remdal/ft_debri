/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: RMDLUtils.cpp            +++     +++			**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 09/09/2025 14:50:38      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <Utils/hpp/RMDLUtils.hpp>

void *ft_memcpy(void *dst, const void *src, size_t n)
{
    char *c_src;
    char *c_dst;

    c_src = (char *)src;
    c_dst = (char *)dst;
    if (dst != 0 || src != 0)
    {
        while (n)
        {
            *(c_dst++) = *(c_src++);
            --n;
        }
    }
    return (dst);
}