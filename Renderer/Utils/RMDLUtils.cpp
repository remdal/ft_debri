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

void *ft_memcpynok(void *dst, const void *src, size_t n)
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

void *ft_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char       *c_dst;
    const unsigned char *c_src;

    c_dst = (unsigned char *)dst;
    c_src = (const unsigned char *)src;
    if (dst == NULL && src == NULL)
        return (dst);
    while (n--)
        *c_dst++ = *c_src++;
    return (dst);
}

void    *ft_memset(void *s, int c, size_t n)
{
    unsigned char   *ptr;
    unsigned char   value;

    ptr = (unsigned char *)s;
    value = (unsigned char)c;
    while (n --)
        *ptr++ = value;
    return (s);
}