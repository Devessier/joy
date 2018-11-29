/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 10:53:13 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 10:09:52 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "reader.h"
#include "utils.h"
#include "errors.h"
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
			return (1);
		while (x < LINE_LEN)
		{
			if (tab[x] == '#')
				tetrimino->data |= shift;
			else if (tab[x] != '.')
				return (1);
			shift >>= 1;
			x++;
		}
	}
	normalize_tetrimino(tetrimino);
	dimensions_tetrimino(tetrimino);
	return (0);
}

t_etrimino	*parse_fd(const int fd)
{
	static t_etrimino	tetriminos[MAX_TETRIMINOS];
	unsigned char		index;
	t_reader			reader;
	char				c;

	rd_init(&reader);
	index = 0;
	while (index < MAX_TETRIMINOS)
	{
		if (invoke_tetrimino(&tetriminos[index], &reader, fd))
			return (NULL);
		if (!rd_get_chars(&reader, fd, &c, 1))
			return (tetriminos);
		if (c != '\n')
			return (NULL);
		index++;
	}
	return (tetriminos);
}

void		print_parsed_bitmap(t_etrimino *tetriminos)
{
	unsigned char	i;
	char			line;
	char			shift;
	uint16_t		tetri;
	char			y;

	if (!tetriminos)
		print_error();
	i = 0;
	while (i < MAX_TETRIMINOS)
	{
		if (!(tetri = tetriminos[i].data))
			return ;
		y = MAX_HEIGHT;
		while (y)
		{
			line = tetriminos[i].data >> (--y * 4) & 0xF;
			shift = 1 << 3;
			while (shift)
				write(1, line & ((shift >>= 1) << 1) ? "#" : ".", 1);
			write(1, "\n", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}
