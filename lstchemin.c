/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstchemin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 11:03:41 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/02 11:03:57 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		initlstchemin(t_linkedlst **lstchemin)
{
	(*lstchemin) = (t_linkedlst *)malloc(sizeof(t_linkedlst));
	if ((*lstchemin) == NULL)
		return ;
	else
	{
		(*lstchemin)->len = 0;
		(*lstchemin)->tail = NULL;
		(*lstchemin)->head = NULL;
	}
}

int			ft_newchemin(t_chemin *ch)
{
	ch->length_malloc = 1;
	ch->length = 0;
	ch->id = (int *)malloc(sizeof(int) * ch->length_malloc);
	if (ch->id == NULL)
		return (0);
	return (1);
}

void		ft_addchfront(t_linkedlst **lst, t_chemin *array)
{
	t_node	*new_elem;

	new_elem = (t_node *)malloc(sizeof(t_node));
	// ft_bzero(new_elem, sizeof(*new_elem));
	ft_bzero(new_elem, sizeof(t_node));
	if ((*lst)->head == NULL)
	{
		(*lst)->tail = new_elem;
	}
	else
	{
		(*lst)->head->prev = new_elem;
		new_elem->prev = NULL;
		new_elem->next = (*lst)->head;
	}
	(*lst)->head = new_elem;
	(*lst)->head->array.length = array->length;
	(*lst)->head->array.length_malloc = array->length;
	(*lst)->head->array.id = (int *)malloc(sizeof(int) * (*lst)->head->array.length_malloc);
	ft_memcpy((*lst)->head->array.id, array->id, sizeof(int) * array->length);
	(*lst)->len += 1;
}
