/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:18:18 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 12:07:08 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <unistd.h>

int			ft_sqrt(int nb)
{
	int		curr;
	float	tmp;
	int		last;

	if (nb <= 0)
		return (0);
	curr = nb / 2;
	last = -1;
	tmp = curr;
	while (curr != last)
	{
		last = curr;
		tmp = 0.5 * ((float)last + (float)nb / (float)last);
		curr = tmp;
	}
	return (curr);
}

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
			line = (tetriminos[i].data & (0xF << (4 * shift))) >> (4 * shift);
			j = 4;
			while (--j >= 0)
				if ((line & (1 << j)) >> j)
					map[(tetriminos[i].y + (3 - shift))
						* size + tetriminos[i].x + 4 - j] = 'A' + i;
		}
		i++;
	}
	fill_with_newlines(map, size);
	write(1, map + 1, size * (size - 1));
}
