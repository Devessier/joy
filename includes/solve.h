/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:14:52 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 11:49:30 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H
# include "parser.h"

void		normalize_tetrimino(t_etrimino *tetrimino);
uint16_t	solve(t_etrimino *tetriminos, uint8_t nb_tet);

#endif
