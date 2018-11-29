/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:00:19 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 10:04:41 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>
#include "solve.h"
#include "errors.h"

int		main(int argc, char **argv)
{
	int			fd;
	t_etrimino	*tetriminos;

	if (argc != 2)
		print_error();
	fd = open(argv[1], O_RDONLY);
	tetriminos = parse_fd(fd);
	if (!tetriminos)
		print_error();
	solve(tetriminos);
	close(fd);
}
