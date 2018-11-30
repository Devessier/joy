/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:00:19 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/30 11:16:35 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include "solve.h"
#include "print.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int		main(int argc, char **argv)
{
	int			fd;
	t_etrimino	*tetriminos;
	uint16_t	size;
	uint8_t		nb_tet;

	if (argc != 2)
	{
		write(2, "usage: ", 7);
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, " map_file\n", 10);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	tetriminos = parse_fd(fd, &nb_tet);
	if (!tetriminos)
	{
		write(1, "error\n", 6);
		return (1);
	}
	size = solve(tetriminos, nb_tet);
	print(tetriminos, size);
	close(fd);
}
