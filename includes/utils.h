/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 12:03:31 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/29 11:46:29 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>

uint8_t		ft_log2(uint16_t v);
void		place_bits(uint8_t *data, size_t pos, uint8_t to_place);
int			test_bits(uint8_t *data, size_t pos, uint8_t to_test);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_sqrt(int nb);

#endif
