/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:03:31 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/27 14:41:28 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>

void		print_error();
uint8_t		ft_log2(uint16_t v);
void		place_bits(uint8_t *data, size_t pos, uint8_t to_place);
int			test_bits(uint8_t *data, size_t pos, uint8_t to_test);

#endif
