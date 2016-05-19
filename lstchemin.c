/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstchemin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 11:03:41 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 15:19:16 by kvignau          ###   ########.fr       */
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
	ch->length_malloc = 32;
	ch->length = 0;
	ch->id = (int *)malloc(sizeof(int) * ch->length_malloc);
	if (ch->id == NULL)
		return (0);
	return (1);
}

void		ft_addch(t_linkedlst **lst, t_chemin *array)
{
	t_node	*new_elem;
	t_node	*tmp;

	new_elem = (t_node *)malloc(sizeof(t_node));
	ft_bzero(new_elem, sizeof(t_node));
	tmp = (*lst)->head;
	if (tmp == NULL)
		first_ch(lst, new_elem);
	else
	{
		while (tmp->next != NULL)
		{
			if (tmp->next->array.length > array->length)
				break ;
			tmp = tmp->next;
		}
		action_add(lst, tmp, new_elem, array);
	}
	new_elem->array.length = array->length;
	new_elem->array.length_malloc = array->length;
	new_elem->array.id = (int *)malloc(sizeof(int) *
			new_elem->array.length_malloc);
	ft_memcpy(new_elem->array.id, array->id, sizeof(int) * array->length);
	(*lst)->len += 1;
}

void		first_ch(t_linkedlst **lst, t_node *new_elem)
{
	(*lst)->head = new_elem;
	(*lst)->tail = new_elem;
}

void		action_add(t_linkedlst **lst, t_node *tmp, t_node *new_elem,
		t_chemin *array)
{
	if (tmp == (*lst)->head && tmp->array.length > array->length)
	{
		new_elem->prev = NULL;
		new_elem->next = tmp;
		tmp->prev = new_elem;
		(*lst)->head = new_elem;
	}
	else if (tmp == (*lst)->tail)
	{
		new_elem->prev = tmp;
		new_elem->next = NULL;
		tmp->next = new_elem;
		(*lst)->tail = new_elem;
	}
	else
	{
		new_elem->next = tmp->next;
		new_elem->prev = tmp;
		tmp->next->prev = new_elem;
		tmp->next = new_elem;
	}
}
