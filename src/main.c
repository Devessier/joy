/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:00:19 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 11:50:11 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include "solve.h"
#include "print.h"

int		main(int argc, char **argv)
{
	int			fd;
	t_etrimino	*tetriminos;
	uint16_t	size;
	uint8_t		nb_tet;

	tetriminos = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		tetriminos = parse_fd(fd, &nb_tet);
	}
	if (!tetriminos)
	{
		write(1, "error\n", 6);
		return (1);
	}
	size = solve(tetriminos, nb_tet);
	print(tetriminos, size);
	close(fd);
}
