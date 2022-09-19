/*********************************/
/*   FT_PING          (  //      */
/*   main              ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include <stdlib.h>

#include "u_libft.h"

void
ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = s;
	if (n == 0)
		return ;
	while (n > 0)
	{
		*str = '\0';
		str++;
		n--;
	}
}

void
*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_ptr;
	unsigned char	*src_ptr;
	size_t			i;

	dst_ptr = (unsigned char*)dst;
	src_ptr = (unsigned char*)src;
	i = 0;
	if (src_ptr == NULL && dst_ptr == NULL && n != 0)
	{
		return (NULL);
	}
	while (i < n)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst_ptr);
}

void
*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	ft_bzero(ptr, count * size);
	return (ptr);
}

double
ft_sqrt(double x)
{
	double	i;

	i = 0.0000001;
	while (i * i < x && i * i < INT_MAX)
	{
		i += 0.0000001;
	}
	return (i);
}

int
ft_strcmp(char * s1, char * s2)
{
    while (*(s1++) == *(s2++))
        ;
    return (*s1 - *s2);
}
