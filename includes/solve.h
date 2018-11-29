/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:14:52 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 10:07:05 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVE_H
# define SOLVE_H
# include "parser.h"

void	normalize_tetrimino(t_etrimino *tetrimino);
void	solve(t_etrimino *tetriminos);

#endif
