/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:18:18 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/30 11:20:06 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <unistd.h>

static void	fill_with_newlines(uint8_t *map, uint16_t size)
{
	int	i;

	i = 0;
	while (i < size)
		map[i++ * size] = '\n';
}

void		print(t_etrimino *tetriminos, uint16_t size)
{
	uint8_t		map[4096];
	uint8_t		i;
	int8_t		j;
	int8_t		shift;
	uint8_t		line;

	i = (size++ & 0);
	ft_memset(map, '.', sizeof(map));
	while (tetriminos[i].data)
	{
		shift = 4;
		while (--shift >= 0)
		{
			line = (tetriminos[i].data >> (4 * shift)) & 0xF;
			j = 4;
			while (--j >= 0)
				if ((line >> j) & 1)
					map[(tetriminos[i].y + (3 - shift))
						* size + tetriminos[i].x + 4 - j] = 'A' + i;
		}
		i++;
	}
	fill_with_newlines(map, size);
	write(1, map + 1, size * (size - 1));
}
