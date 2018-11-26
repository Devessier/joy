/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:15:11 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/26 15:09:49 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include <stdio.h>

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
