/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:15:11 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/28 12:09:36 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
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
#include <string.h>

void		print(t_etrimino *tetriminos, uint16_t size)
{
	uint8_t		map[4096];
	uint8_t		i;
	int8_t		j;
	int16_t		shift;
	uint8_t		line;

	size++;
	i = 0;
	memset(map, '.', sizeof(map));
	while (tetriminos[i].data)
	{
		shift = 4;
		while (--shift >= 0)
		{
			line = (tetriminos[i].data & (0xF << (4 * shift))) >> (4 * shift);
			j = 4;
			while (--j >= 0)
				if ((line & (1 << j)) >> j)
					map[(tetriminos[i].y + (3 - shift)) * size + tetriminos[i].x + 4 - j] = 'A' + i;
		}
		i++;
	}
	i = 0;
	while (i < size)
		map[i++ * size]= '\n';
	write(1, map + 1, size * (size - 1));
}

void		solve(t_etrimino *tetriminos)
{
	uint8_t map[4096] = { 0 };
	uint16_t size;
	size = 4;
	place_tetrimino(map, size, tetriminos);
	printf("%d|%d\n", *map, map[1]);
	printf("w : %d | h : %d\n", tetriminos->width, tetriminos->height);
	printf("%d\n", check_tetrimino(map, size, tetriminos));
	place_tetrimino(map, size, tetriminos);
	printf("%d\n", check_tetrimino(map, size, tetriminos));
	while (!try_place(map, size, tetriminos))
		size++;
	printf("Size: %d\n", size);
	print(tetriminos, size);
}
