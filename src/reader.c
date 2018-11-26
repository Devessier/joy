/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdevessi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 09:48:51 by bdevessi          #+#    #+#             */
/*   Updated: 2018/11/26 12:13:22 by bdevessi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include <string.h>

void	rd_init(t_reader *self)
{
	*self = (t_reader) {
		.len = 0,
		.index = 0
	};
}

ssize_t	rd_get_chars(t_reader *self, const int fd, char *tab, size_t size)
{
	size_t	remaining;
	size_t	to_copy;
	size_t	copied;

	remaining = self->len - self->index;
	if (remaining < size)
	{
		copied = remaining;
		//TODO: Replace
		memcpy(tab, self->buffer + self->index, remaining);
		size -= remaining;
		self->len = read(fd, self->buffer, BUFF_SIZE);
		self->index = 0;
		remaining = self->len;
	}
	else
		copied = 0;
	to_copy = remaining < size ? remaining : size;
	//TODO: Replace
	memcpy(tab, self->buffer + self->index, to_copy);
	self->index += to_copy;
	return (to_copy + copied);
}
