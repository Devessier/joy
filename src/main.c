/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:00:19 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/26 16:56:32 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "solve.h"

int		main(int argc, char **argv)
{
	int			fd;
	t_etrimino	*tetriminos;

	if (argc != 2)
		print_error();
	fd = open(argv[1], O_RDONLY);
	tetriminos = parse_fd(fd);
	solve(tetriminos);
//	print_parsed_bitmap(tetriminos);
	close(fd);
}
