#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*source;
	char	*dest;
	int		i;

	i = 0;
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (src == dst)
		return (dst);
	if (source < dest)
	{
		while (len--)
			(dest[i] + len) = (source[i] + len);
		return (dst);
	}
	while (len--)
		dest[i++] = source[i++];
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	lens_total;
	char	*ret;

	if (!s1 && !s2)
		return (0);
	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	lens_total = len_s1 + len_s2 + 1;
	ret = malloc(sizeof(char) * lens_total);
	if (!ret)
		return (0);
	ft_memmove(ret, s1, len_s1);
	ft_memmove(ret + len_s1, s2, len_s2);
	ret[lens_total - 1] = '\0';
	free((char *)s1);
	return (ret);
}
