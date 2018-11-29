/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 10:50:01 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 11:48:24 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdint.h>
# define MAX_TETRIMINOS 26
# define LINE_LEN 4
# define MAX_HEIGHT 4

typedef struct	s_tetrimino
{
	uint16_t	data;
	uint16_t	x;
	uint16_t	y;
	uint16_t	height;
	uint16_t	width;
}				t_etrimino;

t_etrimino		*parse_fd(const int fd, uint8_t *size);

#endif
