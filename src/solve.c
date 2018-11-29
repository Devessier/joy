/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 10:01:20 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 12:12:05 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include "print.h"
#include <stdio.h>
#include <unistd.h>

void		normalize_tetrimino(t_etrimino *tetrimino)
{
	uint8_t	pow;
	uint8_t	col;

	pow = ft_log2(tetrimino->data);
	col = pow % 4;
	if (col < 3 && tetrimino->data & 0x8888)
		pow++;
	if (col < 2 && tetrimino->data & 0x4444)
		pow++;
	if (col < 1 && tetrimino->data & 0x2222)
		pow++;
	tetrimino->data <<= 15 - pow;
}

int			check_tetrimino(uint8_t *map, uint16_t s, t_etrimino *t)
{
	return (test_bits(map, t->y * s + t->x, ((t->data >> 12) & 0xF) << 4)
	|| test_bits(map, (t->y + 1) * s + t->x, ((t->data >> 8) & 0xF) << 4)
	|| test_bits(map, (t->y + 2) * s + t->x, ((t->data >> 4) & 0xF) << 4)
	|| test_bits(map, (t->y + 3) * s + t->x, (t->data & 0xF) << 4));
}

void		place_tetrimino(uint8_t *map, uint16_t size, t_etrimino *t)
{
	place_bits(map, t->y * size + t->x, ((t->data >> 12) & 0xF) << 4);
	place_bits(map, (t->y + 1) * size + t->x, ((t->data >> 8) & 0xF) << 4);
	place_bits(map, (t->y + 2) * size + t->x, ((t->data >> 4) & 0xF) << 4);
	place_bits(map, (t->y + 3) * size + t->x, (t->data & 0xF) << 4);
}

int			try_place(uint8_t *map, uint16_t size, t_etrimino *tetrimino)
{
	if (!tetrimino->data)
		return (1);
	if (size < tetrimino->width || size < tetrimino->height)
		return (0);
	while (tetrimino->y + tetrimino->height <= size)
	{
		if (!check_tetrimino(map, size, tetrimino))
		{
			place_tetrimino(map, size, tetrimino);
			if (try_place(map, size, tetrimino + 1))
				return (1);
			place_tetrimino(map, size, tetrimino);
		}
		tetrimino->x++;
		if (tetrimino->x + tetrimino->width > size)
		{
			tetrimino->x = 0;
			tetrimino->y++;
		}
	}
	tetrimino->x = 0;
	tetrimino->y = 0;
	return (0);
}

uint16_t	solve(t_etrimino *tetriminos, uint8_t nb_tet)
{
	uint8_t		map[4096];
	uint16_t	size;

	ft_memset(map, 0, 4096);
	size = 2;
	while (size * size < nb_tet * 4)
		size++;
	while (!try_place(map, size, tetriminos))
		size++;
	return (size);
}
