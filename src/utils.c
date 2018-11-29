/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:05:03 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 10:03:48 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

uint8_t		ft_log2(uint16_t v)
{
	const uint32_t	b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
	const uint8_t	s[] = {1, 2, 4, 8, 16};
	int8_t			i;
	uint8_t			r;

	r = 0;
	i = 4;
	while (i >= 0)
	{
		if (v & b[i])
		{
			v >>= s[i];
			r |= s[i];
		}
		i--;
	}
	return (r);
}

void		place_bits(uint8_t *data, size_t pos, uint8_t to_place)
{
	data[pos / 8] ^= to_place >> (pos % 8);
	data[pos / 8 + 1] ^= to_place << (8 - (pos % 8));
}

int			test_bits(uint8_t *data, size_t pos, uint8_t to_test)
{
	return (data[pos / 8] & (to_test >> (pos % 8))
		|| data[pos / 8 + 1] & (to_test << (8 - (pos % 8))));
}

void		*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = c;
	return (s);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*c_src = src;
	char		*c_dst;

	c_dst = dst;
	while (n--)
		*c_dst++ = *c_src++;
	return (dst);
}
