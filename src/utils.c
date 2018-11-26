/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:05:03 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/26 15:01:50 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

void		print_error(void)
{
	write(1, "error\n", 6);
	exit(1);
}

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
