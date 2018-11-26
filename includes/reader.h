/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 09:46:31 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/26 10:47:22 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_H
# define READER_H
# include <unistd.h>
# define BUFF_SIZE 4096

typedef struct	s_reader
{
	char	buffer[BUFF_SIZE];
	size_t	len;
	size_t	index;
}				t_reader;

void			rd_init(t_reader *self);
ssize_t			rd_get_chars(t_reader *self, int fd, char *tab, size_t size);

#endif
