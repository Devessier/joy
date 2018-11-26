/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:15:11 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/26 17:01:11 by bdevessi         ###   ########.fr       */
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

int check_tetrimino(uint8_t *map, uint16_t size, t_etrimino *tetrimino)
{
	uint32_t	bits;
	uint8_t		*omap;

	bits = tetrimino->data;
	map += (tetrimino->y * size + tetrimino->x) / 8;
	omap = map;
	bits >>= tetrimino->x % 8;
	if(*(uint32_t *)map & (bits & 0xF000) >> 8)
		return (0);
	map = omap + size / 8;
	if(*(uint32_t *)map & (bits & 0xF00) >> (4 + size % 8))
		return (0);
	map = omap + (size * 2) / 8;
	if(*(uint32_t *)map & (bits & 0xF0) >> (size * 2 % 8))
		return (0);
	map = omap + (size * 3) / 8;
	if(*(uint32_t *)map & (bits & 0xF) >> (size * 3 % 8 - 4))
		return (0);
	return (1);
}

void place_tetrimino(uint8_t *map, uint16_t size, t_etrimino *tetrimino)
{
	uint32_t	bits;
	uint8_t		*omap;

	bits = tetrimino->data;
	map += (tetrimino->y * size + tetrimino->x) / 8;
	omap = map;
	bits >>= tetrimino->x % 8;
	*(uint32_t *)map ^= (bits & 0xF000) >> 8;
	map = omap + size / 8;
	*(uint32_t *)map ^= (bits & 0xF00) >> (4 + size % 8);
	map = omap + (size * 2) / 8;
	*(uint32_t *)map ^= (bits & 0xF0) >> (size * 2 % 8);
	map = omap + (size * 3) / 8;
	*(uint32_t *)map ^= (bits & 0xF) >> (size * 3 % 8 - 4);
}

int			try_place(uint8_t *map, uint16_t size, t_etrimino *tetrimino)
{
	if (!tetrimino->data)
		return (1);
	while (tetrimino->y < size)
	{
		if (check_tetrimino(map, size, tetrimino))
		{
			place_tetrimino(map, size, tetrimino);
			if (try_place(map, size, tetrimino + 1))
				return (1);
			place_tetrimino(map, size, tetrimino);
		}
		tetrimino->x++;
		if (tetrimino->x == size)
		{
			tetrimino->x = 0;
			tetrimino->y++;
		}
	}
	return (0);
}
#include <string.h>

void		print(t_etrimino *tetriminos, uint16_t size)
{
	uint8_t map[4096];
	uint8_t	y;
	uint8_t	x;
	uint8_t	i;
	uint8_t	line;

	size++;
	i = 0;
	memset(map, '.', sizeof(map));
	while (tetriminos[i].data)
	{
		y = MAX_HEIGHT;
		while (y)
		{
			map[y * size]= '\n';
			line = tetriminos[i].data >> (--y * 4) & 0xF;
			x = LINE_LEN;
			while (x)
				if (line & 1 << --x)
	 				map[(tetriminos[i].y + y) * size + tetriminos[i].x + 4 - x] = 'A' + i;
		}
		i++;
	}
	write(1, map + 1, size * (size - 1));
}

void		solve(t_etrimino *tetriminos)
{
	uint8_t map[4096] = { 0 };
	uint16_t size;

	size = 4;
	while (!try_place(map, size, tetriminos))
		size++;
	printf("Size: %d\n", size);
	print(tetriminos, size);
}
