/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 10:53:13 by bdevessi          #+#    #+#             */
/*   Updated: 2018/12/03 09:50:09 by dde-jesu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "reader.h"
#include "utils.h"
#include "solve.h"

void		dimensions_tetrimino(t_etrimino *t)
{
	t->width = !!(t->data & 0x8888)
		+ !!(t->data & 0x4444)
		+ !!(t->data & 0x2222)
		+ !!(t->data & 0x1111);
	t->height = !!(t->data & 0xF000)
		+ !!(t->data & 0xF00)
		+ !!(t->data & 0xF0)
		+ !!(t->data & 0xF);
}

int			is_valid_tetrimino(t_etrimino *t)
{
	uint8_t		i;
	uint8_t		count;
	uint8_t		links;
	uint16_t	neighbors;

	i = 0;
	count = 0;
	links = 0;
	neighbors = 0;
	while (i < 16 && count <= 4)
	{
		if ((t->data >> i) & 1)
		{
			if (i >= 4)
				neighbors = (t->data & (0b100101001 << (i - 4))) >> (i - 4);
			else
				neighbors = (t->data & (0b100101001 >> (4 - i))) << (4 - i);
			links += !!(neighbors & 0b1) + !!(neighbors & 0b1000);
			links += !!(neighbors & 0b100000) + !!(neighbors & 0b100000000);
			count++;
		}
		i++;
	}
	return (count == 4 && links >= 6);
}

int			invoke_tetrimino(t_etrimino *tetrimino, t_reader *reader, int fd)
{
	char		tab[LINE_LEN + 1];
	ssize_t		read_bytes;
	uint32_t	shift;
	uint8_t		x;

	shift = 1 << 15;
	while (shift)
	{
		x = 0;
		read_bytes = rd_get_chars(reader, fd, tab, LINE_LEN + 1);
		if (read_bytes != LINE_LEN + 1 || tab[LINE_LEN] != '\n')
			return (0);
		while (x < LINE_LEN)
		{
			if (tab[x] == '#')
				tetrimino->data |= shift;
			else if (tab[x] != '.')
				return (0);
			shift >>= 1;
			x++;
		}
	}
	normalize_tetrimino(tetrimino);
	dimensions_tetrimino(tetrimino);
	return (is_valid_tetrimino(tetrimino));
}

t_etrimino	*parse_fd(const int fd, uint8_t *index)
{
	static t_etrimino	tetriminos[MAX_TETRIMINOS + 1];
	t_reader			reader;
	char				c;

	rd_init(&reader);
	*index = 0;
	while (*index < MAX_TETRIMINOS)
	{
		if (!invoke_tetrimino(&tetriminos[*index], &reader, fd))
			return (NULL);
		if (!rd_get_chars(&reader, fd, &c, 1))
			return (tetriminos);
		if (c != '\n')
			return (NULL);
		(*index)++;
	}
	if (rd_get_chars(&reader, fd, &c, 1) != 0)
		return (NULL);
	return (tetriminos);
}
