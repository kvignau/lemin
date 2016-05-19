/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstchemin_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 14:42:17 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 14:42:32 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_delone(t_linkedlst **lst, t_node *delnode)
{
	t_node	*tmp;

	tmp = (*lst)->head;
	while (tmp != NULL && tmp != delnode)
		tmp = tmp->next;
	if (tmp == NULL)
		return ;
	if (tmp == (*lst)->head)
	{
		(*lst)->head = tmp->next;
		tmp->next->prev = NULL;
		tmp->next = NULL;
	}
	else if (tmp == (*lst)->tail)
	{
		(*lst)->tail = tmp->prev;
		tmp->prev->next = NULL;
		tmp->prev = NULL;
	}
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	delonech(tmp, lst);
}

void		delonech(t_node *tmp, t_linkedlst **lst)
{
	free(tmp->array.id);
	free(tmp->array.dispo);
	free(tmp);
	(*lst)->len -= 1;
}
